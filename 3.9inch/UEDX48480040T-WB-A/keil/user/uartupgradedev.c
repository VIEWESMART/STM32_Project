
#include "main.h"
#include "stdio.h"
#include "string.h"
#include "common.h"
#include "devmodule.h"
#include "ring.h"
#include "SerialFlash.h"


extern UART_HandleTypeDef huart2;
#define DEBUG_UART &huart2

#define BUFFSIZE 	530
#define ONEFRAME	512
static u8 rxbuff[BUFFSIZE];
static RingQueue ring;
static u8 headtab[18] = {0};


//CRC16_CCITT校验
unsigned int Rx_CRC_CCITT(unsigned char *puchMsg, unsigned int usDataLen)
{
	unsigned char i = 0;
	unsigned short wCRCin = 0x0000;
	unsigned short wCPoly = 0x1021;
	unsigned char wChar = 0;
	while (usDataLen--)
	{
		wChar = *(puchMsg++);
		wCRCin ^= (wChar << 8);
		for(i = 0; i < 8; i++)
		{
			if (wCRCin & 0x8000)
				wCRCin = (wCRCin << 1) ^ wCPoly;
			else
				wCRCin = wCRCin << 1;
		}
	}return (wCRCin);
}

void I_UART_Transmit(UART_HandleTypeDef* uartid, uint8_t* data,uint8_t len, uint8_t timout){
	HAL_UART_Transmit(uartid,data,len,timout);
}
/* retarget the C library printf function to the USART */
int fputc(int ch, FILE *f)
{
	uint8_t c = ch;
	HAL_UART_Transmit(DEBUG_UART,&c,1,-1);
    return ch;
}

//判断文件是否超出Flash大小
static uint8_t _is_OverFlashSize(uint32_t filesize) {
#define X25QXX_KEEP_SIZE  	0//0x40000		/* X25qxx retains 256K size */
	//读取Flash型号,依据最低1字节判断Flash内存大小
	uint8_t flash_id = (uint8_t)readDeviceId();
	uint32_t flash_size = 0x1FF000; //2M
	switch(flash_id) {
		case 0x15: //25q16 //2M
			flash_size = 0x1FF000;
			break;
		case 0x16: //25q32 //4M
			flash_size = 0x3FF000;
			break;
		case 0x17: //25q64 //8M
			flash_size = 0x7FF000;
			break;
		case 0x18: //25q128 //16M
			flash_size = 0xFFF000;
			break;
		case 0x19: //25q256 //32M
			flash_size = 0x1FFF000;
			break;
		default : 
			break;
	}
	//判断文件是否超出Flash大小
	if(filesize > (flash_size-X25QXX_KEEP_SIZE)) {
		printf("file size over\n");
		return 1;
	}
	return 0;
}

static void processUpgrade(){
	u16 RxCRC16 = 0;
	u16 MyCRC16 = 0;
	u8 ErrorCount = 0;
	u16 datalen = 0;
	u8 readbuff[BUFFSIZE];
	u8 flash_succ[3] = {0xa2, 0x00, 0x00};
	u8 flash_rese[3] = {0xe0, 0x00, 0x00};
	u8 flash_erro[3] = {0xe1, 0x00, 0x00};

	DeQueue(&ring,readbuff,14);
	RxCRC16 = (readbuff[12]<<8)|readbuff[13];
	memcpy(&headtab[4],readbuff,12);
	//CRC校验
	MyCRC16 = Rx_CRC_CCITT(headtab,16);
	if(RxCRC16 != MyCRC16) {	//CRC校验失败
		I_UART_Transmit(DEBUG_UART, flash_erro, 3, 1);
		return;
	}
	uint32_t filesize = readbuff[8]<<24|readbuff[9]<<16|readbuff[10]<<8|readbuff[11];
	uint32_t startaddr = 0;
	uint16_t updatetimeout = 0;
	//printf("start update file ,please input file:%d!!!\n",filesize);
	
	//判断文件是否超出Flash大小
	if(_is_OverFlashSize(filesize) != 0) return;
	
	fy_flash_erase_block(startaddr,filesize);
	startaddr = 0;
	filesize +=startaddr;

	//printf("flash ready\n",filesize);
	int bytes = QueueCount(&ring);
	DeQueue(&ring,readbuff,bytes);
	memset(readbuff,0,530);
	I_UART_Transmit(DEBUG_UART, flash_succ, 3, 1);	//FLASH擦除成功开始传输文件
	while(1){
		updatetimeout++;
		if(updatetimeout > 3000){
			printf("update timeout\n");
			break;
		}
		int bytes = QueueCount(&ring);
		if(bytes > 0){
			if(((startaddr + bytes) < filesize+8)&& (bytes < 520)){
				HAL_Delay(1);
				continue;
			}
			updatetimeout = 0;
			//printf("[%d]",bytes);
			if(bytes > 520){
				DeQueue(&ring,readbuff,520);
				datalen = (readbuff[4]<<8)|readbuff[5];
				RxCRC16 = (readbuff[datalen+6]<<8)|readbuff[datalen+7];
				MyCRC16 = Rx_CRC_CCITT(&readbuff[2],datalen+4);
				if(RxCRC16 != MyCRC16) {	//CRC校验失败
					ErrorCount++;
					if(ErrorCount > 3) {
						flash_erro[1] = readbuff[2];
						flash_erro[2] = readbuff[3];
						I_UART_Transmit(DEBUG_UART, flash_erro, 3, 1);	//传输错误
						break;
					} else {
						flash_rese[1] = readbuff[2];
						flash_rese[2] = readbuff[3];
						I_UART_Transmit(DEBUG_UART, flash_rese, 3, 1);	//传输重传
					}
				} else {
					ErrorCount = 0;
					fy_flash_page_write(startaddr, &readbuff[6], 256);
					fy_flash_page_write(startaddr+256, &readbuff[6+256], 256);
					startaddr+=512;
					flash_succ[1] = readbuff[2];
					flash_succ[2] = readbuff[3];
					I_UART_Transmit(DEBUG_UART, flash_succ, 3, 1);	//传输成功
				}
				//printf("-%d\n",startaddr);
			}else{
				DeQueue(&ring,readbuff,bytes);
				datalen = (readbuff[4]<<8)|readbuff[5];
				RxCRC16 = (readbuff[datalen+6]<<8)|readbuff[datalen+7];
				MyCRC16 = Rx_CRC_CCITT(&readbuff[2],datalen+4);

				if(RxCRC16 != MyCRC16) {	//CRC校验失败
					ErrorCount++;
					if(ErrorCount > 3) {
						flash_erro[1] = readbuff[2];
						flash_erro[2] = readbuff[3];
						I_UART_Transmit(DEBUG_UART, flash_erro, 3, 1);	//传输错误
						break;
					} else {
						flash_rese[1] = readbuff[2];
						flash_rese[2] = readbuff[3];
						I_UART_Transmit(DEBUG_UART, flash_rese, 3, 1);	//传输重传
					}
				} else {
					ErrorCount = 0;
					if(datalen > 256) {
						fy_flash_page_write(startaddr, &readbuff[6], 256);
						fy_flash_page_write(startaddr+256, &readbuff[6+256], datalen-256);
					}else {
						fy_flash_page_write(startaddr, &readbuff[6], datalen);
					}
					startaddr+=datalen;
					flash_succ[1] = readbuff[2];
					flash_succ[2] = readbuff[3];
					I_UART_Transmit(DEBUG_UART, flash_succ, 3, 1);	//传输成功
				}
				//printf("%d\n",startaddr);
			}
			if(startaddr >= filesize){
				flash_succ[1] = 0xff;
				flash_succ[2] = 0xff;
				I_UART_Transmit(DEBUG_UART, flash_succ, 3, 1);	//传输成功
				//printf("update sucess!!!\n");
				break;
			}
		}else{
			HAL_Delay(1);
		}
	}
}

static void processUpgrade_simple(){
	uint32_t updatetimeout = 0;
	uint32_t startaddr = 0;
	uint8_t readbuff[256];
	
	DeQueue(&ring,readbuff,4);
	uint32_t filesize = readbuff[0]<<24|readbuff[1]<<16|readbuff[2]<<8|readbuff[3];
	printf("start simpleupdate:%d \n",filesize);

	fy_flash_erase_block(0,filesize);
	//SPI_Flash_ChipEaser();
	printf("format flash sucess\n");

	while(1){
		updatetimeout++;
		if(updatetimeout > 3000){
			printf("update timeout\n");
			break;
		}
		int bytes = QueueCount(&ring);
		if(bytes > 0){
			updatetimeout = 0;
			if(((startaddr + bytes) < filesize)&& (bytes < 256)){
				HAL_Delay(1);
				continue;
			}
			printf("[%d]",bytes);
			if(bytes >= 256){
				DeQueue(&ring,readbuff,256);
				fy_flash_page_write(startaddr, readbuff, 256);
				startaddr+=256;
				printf("-%d\n",startaddr);
			}else{
				//printf(".");
				DeQueue(&ring,readbuff,bytes);
				fy_flash_page_write(startaddr, readbuff, bytes);
				startaddr+=bytes;
			}
			if(startaddr >= filesize){
				printf("update sucess!!!\n");
				break;
			}
		}else{
			HAL_Delay(1);
		}
	}
}

void JumpToIAP(void) {
	RCC->APBENR1 |= RCC_APBENR1_RTCAPBEN;
	PWR->CR1 |= PWR_CR1_DBP;
	TAMP->BKP0R = 0xaa55aa55;

	NVIC_SystemReset();
}
//跳转到BOOTLOADER升级APP
static void BOOT_IAP(void) {
	extern void JumpToIAP(void);
	uint8_t readbuff[8];
	DeQueue(&ring,readbuff,4);
	if( (readbuff[0] == 0x00) && (readbuff[1] == 0x01) && \
		(readbuff[2] == 0x02) && (readbuff[3] == 0x03)) {
		JumpToIAP();
	}
}

static void processCmd(uint16_t cmd,uint16_t cmdlen){
	if(cmd == 0x00) {
		processUpgrade();
	} else if(cmd == 0x01) {
		processUpgrade_simple();
	} else if(cmd == 0x02) {
		BOOT_IAP();
	}
}
static void procUartUpdateReq(){
    uint8_t checksum = 0;
	uint8_t readbuff[8];
    while(1){
		int bytes = QueueCount(&ring);
		if(bytes < 4){
			return ;
		}
		checksum = 0;
		DeQueue(&ring,readbuff,1);
		if(readbuff[0] != 0xaa){
			printf("not head0:%x \n",readbuff[0]);
			continue;
		}
		checksum += 0xaa;
		DeQueue(&ring,readbuff,1);
		if(readbuff[0] != 0x55){
			printf("not head1:%x \n",readbuff[0]);
			continue;
		}
		DeQueue(&ring,readbuff,4);
		memcpy(headtab,readbuff,4);
		int cmd = (readbuff[0] << 8) | readbuff[1];
		int len = (readbuff[2] << 8) | readbuff[3];
		
		processCmd(cmd,len);
    }
}

void USART2_IRQHandler(){
    if(__HAL_UART_GET_IT_SOURCE(DEBUG_UART,UART_IT_RXNE)){
        u8  uhdata;
        uhdata = (u8) READ_REG(huart2.Instance->RDR);
        EnQueueSignal(&ring,uhdata);
        __HAL_UART_ENABLE_IT(DEBUG_UART,UART_IT_RXNE);
    }
    HAL_UART_IRQHandler(DEBUG_UART);
}


static void initdev(){
	InitQueue(&ring,rxbuff,BUFFSIZE);
    HAL_NVIC_EnableIRQ(USART2_IRQn);
    __HAL_UART_ENABLE_IT(DEBUG_UART,UART_IT_RXNE);
	
}
static void deinitdev(){

}

static void procMsg(int msgtype,int p1,int p2){
    switch(msgtype){
        case DEVMSG_TIMER10ms:
        	procUartUpdateReq();
			break;
		case DEVMSG_WRITE:
			break;
		case DEVMSG_TIMER50ms:
			break;
		case DEVMSG_TIMER100ms:
			//I_UART_Transmit(DEBUG_UART,"test uart",9,HAL_MAX_DELAY);
			break;
    }
}
const S_DEV dev_uartupgrade={
    initdev,
    deinitdev,
    NULL,
    NULL,
    procMsg
};
