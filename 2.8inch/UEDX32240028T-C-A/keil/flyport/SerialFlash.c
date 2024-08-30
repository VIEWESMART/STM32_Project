#include <SerialFlash.h>
#include <main.h>
#include "SerialFlash.h"
#include <stm32g0xx_hal.h>
#include "context/guicontext.h"

#define CMD_RDID 0x9F
#define CMD_READ 0x03
#define CMD_WREN 0x06
#define CMD_PP   0x02
#define CMD_RDSR 0x05
#define CMD_SE   0x20//0xD8
#define STATUS_WIP 0x01

#define W25X_ChipErase			            0xC7

extern SPI_HandleTypeDef hspi1;

//extern prototypes
void Error_Handler(void);

//private variables
//DMA handle for reading pixels from SPI peripheral
extern DMA_HandleTypeDef hdma_spi1_rx;
extern DMA_HandleTypeDef hdma_spi1_tx;

//Status flag. Non-zero when receiving data
static volatile uint8_t isReceivingData = 0;
uint8_t dummy_spi;

/* Chip Select macro definition */
#define FLASH_CS_PIN                       GPIO_PIN_4
#define FLASH_CS_GPIO_PORT                 GPIOA
#define FLASH_CS_LOW()                     {FLASH_CS_GPIO_PORT->BRR = FLASH_CS_PIN;}//HAL_GPIO_WritePin(FLASH_CS_GPIO_PORT, FLASH_CS_PIN, GPIO_PIN_RESET)
#define FLASH_CS_HIGH()                    {FLASH_CS_GPIO_PORT->BSRR = FLASH_CS_PIN;}//HAL_GPIO_WritePin(FLASH_CS_GPIO_PORT, FLASH_CS_PIN, GPIO_PIN_SET)

uint32_t readDeviceId(void)
{
    FLASH_CS_LOW();
    *((__IO uint8_t*)&hspi1.Instance->DR) = CMD_RDID;
    while(((hspi1.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
    *((__IO uint8_t*)&hspi1.Instance->DR) = 0;
    while(((hspi1.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
    *((__IO uint8_t*)&hspi1.Instance->DR) = 0;
    while(((hspi1.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
    *((__IO uint8_t*)&hspi1.Instance->DR) = 0;

    /* Wait until the bus is ready before releasing Chip select */
    while(((hspi1.Instance->SR) & SPI_FLAG_BSY) != RESET) { }
    FLASH_CS_HIGH();

    //combine bytes
    uint8_t data0 = *((__IO uint8_t*)&hspi1.Instance->DR);
    uint8_t data1 = *((__IO uint8_t*)&hspi1.Instance->DR);
    uint8_t data2 = *((__IO uint8_t*)&hspi1.Instance->DR);
    uint8_t data3 = *((__IO uint8_t*)&hspi1.Instance->DR);

    return data1<<16 | data2<<8 | data3;
}

static uint32_t readStatusRegister()
{
    FLASH_CS_LOW();
    *((__IO uint8_t*)&hspi1.Instance->DR) = CMD_RDSR; //0x05, 0x00
    while(((hspi1.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
    *((__IO uint8_t*)&hspi1.Instance->DR) = 0;

    /* Wait until the bus is ready before releasing Chip select */
    while(((hspi1.Instance->SR) & SPI_FLAG_BSY) != RESET) { }
    FLASH_CS_HIGH();

    //combine bytes
    uint8_t data0 = *((__IO uint8_t*)&hspi1.Instance->DR);
    uint8_t data1 = *((__IO uint8_t*)&hspi1.Instance->DR);

    return data1;
}

static void sendWriteEnable()
{
    FLASH_CS_LOW();
    *((__IO uint8_t*)&hspi1.Instance->DR) = CMD_WREN; //0x06

    /* Wait until the bus is ready before releasing Chip select */
    while(((hspi1.Instance->SR) & SPI_FLAG_BSY) != RESET) { }
    FLASH_CS_HIGH();

    //read dummy byte
    *((__IO uint8_t*)&hspi1.Instance->DR);
}

static void sendSectorErase(uint32_t address24)
{
    FLASH_CS_LOW();
    *((__IO uint8_t*)&hspi1.Instance->DR) = 0xD8; //0xD8, A2, A1, A0
    uint8_t data0 = *((__IO uint8_t*)&hspi1.Instance->DR);

    //clock out address
    while(((hspi1.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
    *((__IO uint8_t*)&hspi1.Instance->DR) = (address24 >> 16) & 0xFF;

    while(((hspi1.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
    *((__IO uint8_t*)&hspi1.Instance->DR) = (address24 >> 8) & 0xFF;

    while(((hspi1.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
    *((__IO uint8_t*)&hspi1.Instance->DR) = address24 & 0xFF;

    /* Wait until the bus is ready before releasing Chip select */
    while(((hspi1.Instance->SR) & SPI_FLAG_BSY) != RESET) { }
    FLASH_CS_HIGH();

    //read dummy bytes
    *((__IO uint8_t*)&hspi1.Instance->DR);
    *((__IO uint8_t*)&hspi1.Instance->DR);
    *((__IO uint8_t*)&hspi1.Instance->DR);
    *((__IO uint8_t*)&hspi1.Instance->DR);
}

static void cmd_Erase()
{
	 FLASH_CS_LOW();
	*((__IO uint8_t*)&hspi1.Instance->DR) = W25X_ChipErase; //0x06

	/* Wait until the bus is ready before releasing Chip select */
	while(((hspi1.Instance->SR) & SPI_FLAG_BSY) != RESET) { }
	FLASH_CS_HIGH();

	//read dummy byte
	*((__IO uint8_t*)&hspi1.Instance->DR);
}
static void sendPageProgram(uint32_t address24, const uint8_t* data, uint32_t length)
{
    FLASH_CS_LOW();
    *((__IO uint8_t*)&hspi1.Instance->DR) = CMD_PP;

    //clock out address
    while(((hspi1.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
    *((__IO uint8_t*)&hspi1.Instance->DR) = (address24 >> 16) & 0xFF;

    while(((hspi1.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
    *((__IO uint8_t*)&hspi1.Instance->DR) = (address24 >> 8) & 0xFF;

    while(((hspi1.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
    *((__IO uint8_t*)&hspi1.Instance->DR) = address24 & 0xFF;

    //now write data bytes
    while(length > 0)
    {
        while(((hspi1.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
        *((__IO uint8_t*)&hspi1.Instance->DR) = *data;
        data++;
        length--;
    }

    /* Wait until the bus is ready before releasing Chip select */
    while(((hspi1.Instance->SR) & SPI_FLAG_BSY) != RESET) { }

    FLASH_CS_HIGH();

    //read dummy bytes
    while(((hspi1.Instance->SR) & SPI_FLAG_RXNE) == SPI_FLAG_RXNE)
    {
        *((__IO uint8_t*)&hspi1.Instance->DR);
    }
}

void readData(uint32_t address24, uint8_t* buffer, uint32_t length)
{
    FLASH_CS_LOW();
    *((__IO uint8_t*)&SPI1->DR) = CMD_READ;

    //clock out address
    *((__IO uint8_t*)&hspi1.Instance->DR) = (address24 >> 16) & 0xFF;

    while(((hspi1.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
    *((__IO uint8_t*)&hspi1.Instance->DR) = (address24 >> 8) & 0xFF;

    while(((hspi1.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
    *((__IO uint8_t*)&hspi1.Instance->DR) = address24 & 0xFF;

    switch (length)
    {
        default:
            while(((hspi1.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
            dummy_spi = *((__IO uint8_t*)&hspi1.Instance->DR);
            *((__IO uint8_t*)&hspi1.Instance->DR) = 0 ;
        case 3:
            while(((hspi1.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
            dummy_spi = *((__IO uint8_t*)&hspi1.Instance->DR);
            *((__IO uint8_t*)&hspi1.Instance->DR) = 0;
        case 2:
            while(((hspi1.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
            dummy_spi = *((__IO uint8_t*)&hspi1.Instance->DR);
            *((__IO uint8_t*)&hspi1.Instance->DR) = 0;
        case 1:
            while(((hspi1.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
            dummy_spi = *((__IO uint8_t*)&hspi1.Instance->DR);
            *((__IO uint8_t*)&hspi1.Instance->DR) = 0;
        case 0:
            break;
    }
    switch (length)
    {
        case 1:
        dummy_spi = *((__IO uint8_t*)&hspi1.Instance->DR);
        case 2:
       dummy_spi =  *((__IO uint8_t*)&hspi1.Instance->DR);
        case 3:
        dummy_spi = *((__IO uint8_t*)&hspi1.Instance->DR);
        default:
            break;
    }

    uint8_t* const buf_end = buffer + length - 4;

    while ((buf_end - buffer) > 3)
    {
        while(((SPI1->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
        *buffer++ = *((__IO uint8_t*)&SPI1->DR);
	*((__IO uint8_t*)&SPI1->DR) = 0;
	while(((SPI1->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
        *buffer++ = *((__IO uint8_t*)&SPI1->DR);
	*((__IO uint8_t*)&SPI1->DR) = 0;
	while(((SPI1->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
        *buffer++ = *((__IO uint8_t*)&SPI1->DR);
	*((__IO uint8_t*)&SPI1->DR) = 0;
	while(((SPI1->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
        *buffer++ = *((__IO uint8_t*)&SPI1->DR);
	*((__IO uint8_t*)&SPI1->DR) = 0;
    }

    while (buffer < buf_end)
    {
        while(((SPI1->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
        *buffer++ = *((__IO uint8_t*)&SPI1->DR);
	*((__IO uint8_t*)&SPI1->DR) = 0;
    }

    /* Wait until the bus is ready before releasing Chip select */
    while(((hspi1.Instance->SR) & SPI_FLAG_BSY) != RESET) { }

    FLASH_CS_HIGH();
    const int rest = length < 4 ? length : 4;
    for (int i = 0; i<rest; i++)
    {
        *buffer++ = *((__IO uint8_t*)&SPI1->DR);
    }
	isReceivingData = 0;
}

void readDataDMA(uint32_t address24, uint8_t* buffer, uint32_t length)
{
     // Pull Flash CS pin low
    isReceivingData = 1;
    FLASH_CS_LOW();

    *((__IO uint8_t*)&hspi1.Instance->DR) = CMD_READ;

    //clock out address
    while(((hspi1.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
    *((__IO uint8_t*)&hspi1.Instance->DR) = (address24 >> 16) & 0xFF;

    while(((hspi1.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
    *((__IO uint8_t*)&hspi1.Instance->DR) = (address24 >> 8) & 0xFF;

    while(((hspi1.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE);
    *((__IO uint8_t*)&hspi1.Instance->DR) = address24 & 0xFF;

    /* Wait until the bus is ready before reading 4 dummy bytes */
    while(((hspi1.Instance->SR) & SPI_FLAG_BSY) != RESET) { }
    *((__IO uint8_t*)&hspi1.Instance->DR);
    *((__IO uint8_t*)&hspi1.Instance->DR);
    *((__IO uint8_t*)&hspi1.Instance->DR);
    *((__IO uint8_t*)&hspi1.Instance->DR);

    /* Reset the threshold bit */
    CLEAR_BIT(hspi1.Instance->CR2, SPI_CR2_LDMATX | SPI_CR2_LDMARX);

    /* Set RX Fifo threshold according the reception data length: 8bit */
    SET_BIT(hspi1.Instance->CR2, SPI_RXFIFO_THRESHOLD);

    /******** RX ****************/
    /* Disable the peripheral */
    __HAL_DMA_DISABLE(&hdma_spi1_rx);

    /* Clear all flags */
    __HAL_DMA_CLEAR_FLAG(&hdma_spi1_rx, (DMA_FLAG_GI1 << (hdma_spi1_rx.ChannelIndex & 0x1cU)));

    /* Configure DMA Channel data length */
    hdma_spi1_rx.Instance->CNDTR = length;

    /* Configure DMA Channel destination address */
    hdma_spi1_rx.Instance->CPAR = (uint32_t)&hspi1.Instance->DR;

    /* Configure DMA Channel source address */
    hdma_spi1_rx.Instance->CMAR = (uint32_t)buffer;

    __HAL_DMA_DISABLE_IT(&hdma_spi1_rx, DMA_IT_HT | DMA_IT_TE);
    __HAL_DMA_ENABLE_IT(&hdma_spi1_rx, (DMA_IT_TC));

    /* Enable the Peripheral */
    __HAL_DMA_ENABLE(&hdma_spi1_rx);

    /* Enable Rx DMA Request */
    SET_BIT(hspi1.Instance->CR2, SPI_CR2_RXDMAEN);

    /******** TX ****************/
    /* Disable the peripheral */
    __HAL_DMA_DISABLE(&hdma_spi1_tx);

    /* Clear all flags */
    __HAL_DMA_CLEAR_FLAG(&hdma_spi1_tx, (DMA_FLAG_GI1 << (hdma_spi1_tx.ChannelIndex & 0x1cU)));

    /* Configure DMA Channel data length */
    hdma_spi1_tx.Instance->CNDTR = length;

    /* Configure DMA Channel destination address */
    hdma_spi1_tx.Instance->CPAR = (uint32_t)&hspi1.Instance->DR;

    /* Configure DMA Channel source address */
    hdma_spi1_tx.Instance->CMAR = (uint32_t)buffer;

    /* Enable the Peripheral */
    __HAL_DMA_ENABLE(&hdma_spi1_tx);

    /* Enable SPI peripheral */
    __HAL_SPI_ENABLE(&hspi1);

    /* Enable Tx DMA Request */
    SET_BIT(hspi1.Instance->CR2, SPI_CR2_TXDMAEN);

}

void DataReader_DMACallback()
{
    /* Transfer Complete Interrupt management ***********************************/
    if ((0U != (DMA1->ISR & (DMA_FLAG_TC1 << (hdma_spi1_rx.ChannelIndex & 0x1cU)))) && (0U != (hdma_spi1_rx.Instance->CCR & DMA_IT_TC)))
    {
        /* Disable the transfer complete and error interrupt */
        __HAL_DMA_DISABLE_IT(&hdma_spi1_rx, DMA_IT_TE | DMA_IT_TC);
        /* Clear the transfer complete flag */
        __HAL_DMA_CLEAR_FLAG(&hdma_spi1_rx, (DMA_FLAG_TC1 << (hdma_spi1_rx.ChannelIndex & 0x1cU)));


        // Wait until the bus is not busy before changing configuration
        // SPI is busy in communication or Tx buffer is not empty
        while(((hspi1.Instance->SR) & SPI_FLAG_BSY) != RESET) { }

       //FLASH_CS_GPIO_Port->BSRR = FLASH_CS_Pin;
        FLASH_CS_HIGH();
        isReceivingData = 0;
    }
}

void SerialFlash_ReadData(uint32_t address24, uint8_t* buffer, uint32_t length)
{
    readData(address24, buffer, length);
}

void SerialFlash_StartDMAReadData(uint32_t address24, uint8_t* buffer, uint32_t length)
{
    readDataDMA(address24, buffer, length);
}

volatile uint32_t statusReg = 0;

void SerialFlash_ChipErase(){
	uint32_t address = 0x000000;
	sendWriteEnable();
	cmd_Erase();
	uint32_t status;
	do
	{
		status = readStatusRegister();
	} while (status & STATUS_WIP);
}
void SerialFlash_EraseSize(uint32_t startaddr,uint32_t size){
	uint32_t address = startaddr;
	uint32_t sizeOfBitmaps = address+size;
	do
	{
		sendWriteEnable();
		sendSectorErase(address);

		//wait until WIP is cleared
		uint32_t status;
		do
		{
			status = readStatusRegister();
		} while (status & STATUS_WIP);

		address += 0x8000;
	} while (address < sizeOfBitmaps);
}
void SerialFlash_ProgramInfo(uint32_t addr,uint8_t* data,uint32_t size){
	sendWriteEnable();
	sendPageProgram(addr, data, size);
	//wait until WIP is cleared
	uint32_t status;
	do
	{
		status = readStatusRegister();
	} while (status & STATUS_WIP);
}


uint32_t SerialFlash_IsReceivingData(void)
{
  return isReceivingData;
}

void SerialFlash_WaitForReceiveDone(void)
{
    while (isReceivingData);
}

void SerialFlash_DMAInit(void)
{
    /* DMA controller clock enable */
    //__HAL_RCC_DMA1_CLK_ENABLE();
    /* DMA interrupt init */

    /* DMA1_Channel1_IRQn interrupt configuration */
    //HAL_NVIC_SetPriority(DMA1_Channel2_3_IRQn, 0, 0);
    //HAL_NVIC_EnableIRQ(DMA1_Channel2_3_IRQn);

    /* SPI1 DMA Init */
    /* SPI1_RX Init */
    hdma_spi1_rx.Instance = DMA1_Channel2;
    hdma_spi1_rx.Init.Request = DMA_REQUEST_SPI1_RX;
    hdma_spi1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
    hdma_spi1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi1_rx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi1_rx.Init.MemDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi1_rx.Init.Mode = DMA_NORMAL;
    hdma_spi1_rx.Init.Priority = DMA_PRIORITY_HIGH;
    if (HAL_DMA_Init(&hdma_spi1_rx) != HAL_OK)
    {
        Error_Handler();
    }

    __HAL_LINKDMA(&hspi1, hdmarx, hdma_spi1_rx);

    /* SPI1_TX Init */
    hdma_spi1_tx.Instance = DMA1_Channel3;
    hdma_spi1_tx.Init.Request = DMA_REQUEST_SPI1_TX;
    hdma_spi1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
    hdma_spi1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
    hdma_spi1_tx.Init.MemInc = DMA_MINC_ENABLE;
    hdma_spi1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi1_tx.Init.MemDataAlignment = DMA_PDATAALIGN_BYTE;
    hdma_spi1_tx.Init.Mode = DMA_NORMAL;
    hdma_spi1_tx.Init.Priority = DMA_PRIORITY_LOW;
    if (HAL_DMA_Init(&hdma_spi1_tx) != HAL_OK)
    {
        Error_Handler();
    }

    __HAL_LINKDMA(&hspi1, hdmatx, hdma_spi1_tx);

    /* SPI1 interrupt Init */
    //HAL_NVIC_SetPriority(SPI1_IRQn, 0, 0);
    //HAL_NVIC_EnableIRQ(SPI1_IRQn);
}



void fly_flash_init(void){
	FLASH_CS_HIGH();
	__HAL_SPI_ENABLE(&hspi1);
//	SerialFlash_DMAInit();
}
uint32_t fy_flash_readid(void)
{
	return readDeviceId();
}
void fy_flash_read(uint32_t address24, uint8_t* buffer, uint32_t length)
{
	readData(address24,buffer,length);
}

void fy_flash_readdma(uint32_t address24, uint8_t* buffer, uint32_t length)
{
    readData(address24,buffer,length);
	//readDataDMA(address24,buffer,length);
}

void fy_flash_erase(void){
	SerialFlash_ChipErase();
	//spi_flash_bulk_erase();
}
void fy_flash_erase_block(uint32_t start,uint32_t sizeOfBitmaps){
  // spi_flash_sector_erase_size(start,sizeOfBitmaps);
	SerialFlash_EraseSize(start,sizeOfBitmaps);
}
void fy_flash_page_write(uint32_t addr,uint8_t* data,uint32_t size){
	//spi_flash_page_write(data,addr,size);
	SerialFlash_ProgramInfo(addr,data,size);
}

uint32_t fy_flash_isreceiveing(void)
{
//  return isReceivingData;
	return SerialFlash_IsReceivingData();
}

void fy_flash_waitreceive_done(void)
{
	SerialFlash_WaitForReceiveDone();
}

void fy_flash_dmainit(void)
{
  
}

const flythings_flash	m_flash ={
  .flash_init = fly_flash_init,
  .flash_deinit = fy_flash_dmainit,
  .flash_readdata = readData,
  .flash_readdata_dma = readDataDMA,
  .flash_wait_dma_end = fy_flash_waitreceive_done, 
  .flash_isreading = fy_flash_isreceiveing
};