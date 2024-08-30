#include "stdio.h"
#include "delay.h"

#include "all_iic.h"
#include "IM_Controls.h"

extern I2C_HandleTypeDef hi2c2;

#if UE019QV_AB40_A001A		//170x320
#define LCD_width 	320
#define LCD_height	170
#endif
#if UE035HV_RB40_A118_ST7796S		//480x320
#define LCD_width 	480
#define LCD_height	320
#endif
#if UE039HV_RB40_A009A_4SPI_3041A			//480x272
#define LCD_width 	480
#define LCD_height	272
#endif
#if	UE024QV_RB40_A038A_9307					//320x240
#define LCD_width 	320
#define LCD_height	240
#endif
//

#define TP_LEVEL	1		//��������,0:��ֱ 1:ˮƽ
#if TP_LEVEL
#define TP_MAX_X	LCD_width			//X�������ֵ
#define TP_MAX_Y	LCD_height		//Y�������ֵ
#else 
#define TP_MAX_X	LCD_height		//X�������ֵ
#define TP_MAX_Y	LCD_width			//Y�������ֵ
#endif

#define X_MIRRORING	0		//X�᾵��,0:�� 1:��
#define Y_MIRRORING	1		//Y�᾵��,0:�� 1:��

#define DEV_WD_ADDR 0x5C	//д��ַ	   IIC��ַ
#define DEV_RD_ADDR 0x5D	//����ַ

#if UE019QV_AB40_A001A
#define DEV_READ_COOR_ADDR 0xE0	//��ʼָ��
#else 
#define DEV_READ_COOR_ADDR 0x00	//��ʼָ��
#endif

#if UE019QV_AB40_A001A
#define CNT_FOR_POINT 		3   	//һ�ζ�ȡ����
#define CT_MAX_TOUCH    	1	  	//������֧�ֵĵ���,���Ϊ2����
#else 
#define CNT_FOR_POINT 		7   	//һ�ζ�ȡ����
#define CT_MAX_TOUCH    	2    	//������֧�ֵĵ���,���Ϊ2����
#endif
//������������
typedef struct
{
    uint16_t x[CT_MAX_TOUCH]; //x����
    uint16_t y[CT_MAX_TOUCH]; //y����
    uint16_t size[CT_MAX_TOUCH];                              
} _m_tp_dev;
_m_tp_dev tp_dev;				//����������
	

//��ʱ����	
void delay(void)
{
    uint32_t i;
    for (i = 0; i < 10000; i++)
        ;	
}

/******************************************************************************************************************************************
* ��������:	CHSC6540_WrReg()
* ����˵��:	дCHSC6540�Ĵ���
* ��    ��: uint16_t reg		Ҫд�ļĴ���
*			uint8_t *buf		Ҫд��Ĵ���������
*			uint8_t len			Ҫд�����ݸ���
* ��    ��: uint8_t				1 д��ɹ�   0 д��ʧ��
* ע������: ��
******************************************************************************************************************************************/
static uint8_t CHSC6540_WrReg(uint8_t *buf, uint8_t len)
{
//IICд����							I2Cָ�� �豸��ַ д������� ���ݵĴ�С ������ʱʱ��
	if( HAL_I2C_Master_Transmit(&hi2c2, DEV_WD_ADDR, buf, len, 300) == HAL_OK ) {
      //delay();
	   return 1;
   }
   else {
	   //delay();
       return 0;
   }
}
/******************************************************************************************************************************************
* ��������:	CHSC6540_RdReg()
* ����˵��:	��CHSC6540�Ĵ���
* ��    ��: uint16_t reg		Ҫ���ļĴ���
*			uint8_t *buf		�����ļĴ���ֵд������
*			uint8_t len			Ҫ�������ݸ���
* ��    ��: uint8_t				1 ��ȡ�ɹ�   0 ��ȡʧ��
* ע������: ��
******************************************************************************************************************************************/
static uint8_t CHSC6540_RdReg(uint8_t *buf, uint8_t len)
{
//IIC������	 					I2Cָ�� �豸��ַ Ҫ��ȡ�ļĴ�����ַ �ڴ��ַ���� ��ȡ������ ���ݵĴ�С ������ʱʱ��
	if( HAL_I2C_Master_Receive(&hi2c2, DEV_RD_ADDR, buf, len, 300) == HAL_OK ) {
	   //delay();
	   return 1;
	}
	else {
	   //delay();
	   return 0;
	}

}

/*
��ȡ����ķ�ʽ�ǣ���ȥ���Ĵ�����ַ0x5Cд��E0��Ȼ����ȥ��ȡ0X5D�ĵ�ַ��������ȡ8�����ݳ���
*/
/*  ����ļ��㷽ʽ */
uint8_t CHSC6540_Scan(uint16_t* x,uint16_t* y)
{
		uint8_t touch_info, touch_num, touchSize;
    uint8_t buf[CNT_FOR_POINT * CT_MAX_TOUCH] = {0};
		uint8_t touch_status = DEV_READ_COOR_ADDR;				
    uint8_t ret = 0;
		uint8_t sign;
		uint8_t *coor_data = NULL;
		
		uint8_t x_h=0,y_h=0;
		uint16_t x2=0,y2=0;
		uint16_t tp_dev_x=0,tp_dev_y=0;
	
#if UE019QV_AB40_A001A
		if(!CHSC6540_WrReg(&touch_status, 1)) {
//        printf("I2C write error.\n ");
        return 0;
    }else if(!CHSC6540_RdReg(buf, (CNT_FOR_POINT*CT_MAX_TOUCH) )){
//				printf("I2C read error.\n ");
        return 0;
		}
		int i;
		printf("IIC read :");
		for (i=0; i<(CNT_FOR_POINT*CT_MAX_TOUCH); i++) {
				printf("%d ",buf[i]);
		}printf("\n");
		
		x_h = buf[0]>>8;
		y_h = (buf[0]>>7);
//		printf("y_h:%d, x_h:%d \n",y_h,x_h);
		if(y_h == 1)
			y2 = 255 + buf[2];
		else
			y2 = buf[2];
		
		if(x_h == 1)
			x2 = 255 + buf[1];
		else
			x2 = buf[1];
//		printf("===========y_h:%d, x_h:%d	( %d,%d )===========\n",y_h,x_h, x2, y2);
		if(TP_LEVEL) {
				tp_dev_x = y2;
				tp_dev_y = x2;				
		}else {					
				tp_dev_x = x2;
				tp_dev_y = y2;
		}				
		if(tp_dev_x > TP_MAX_X)
				tp_dev_x = TP_MAX_X;				
		if(tp_dev_y > TP_MAX_Y)
				tp_dev_y = TP_MAX_Y;				

		if (X_MIRRORING) 
				tp_dev_x = TP_MAX_X - 1 - tp_dev_x;
		if (Y_MIRRORING) 
				tp_dev_y = TP_MAX_Y - 1 - tp_dev_y;	
		
		*x = tp_dev_x;
		*y = tp_dev_y + 35;	// + 35
		ret = 1;
#else 
		if (!(CHSC6540_WrReg(&touch_status, 1) && CHSC6540_RdReg(buf, (CNT_FOR_POINT * CT_MAX_TOUCH  + 1)))) {
        printf("I2C write or read error.\n ");
        return 0;
    }
		if(0x10 != buf[8]){return 0;}
		
    //touch_info = buf[0];
		touch_info = (buf[2] & 0x0f);
    if(touch_info<1 || touch_info>2) return 0;
		
    if (touch_info) {			
			printf("IIC read :");
			int i;
			for (i = 0; i < (CNT_FOR_POINT * CT_MAX_TOUCH  + 1); i++) {
					printf("%x ",buf[i]);
			}printf("\n");
			
        touch_num = touch_info;

				if (touch_num > CT_MAX_TOUCH) {   
						touch_num = CT_MAX_TOUCH;
				}						
				sign = 6;
				for (i = 0; i < touch_num; i++) {					
					coor_data = &buf[i * CNT_FOR_POINT + 1];
					touch_status = coor_data[0] >> 6;
					
					x2 = buf[sign*(i+1)-2]; //x�ĵ�8bit						Byte4		10
					x2 = x2 | ((buf[sign*(i+1)-3] & 0x0f)<<8);	//Byte3		9
					 
					y2 = buf[sign*(i+1)]; //y�ĵ�8bit						  Byte6		12
					y2 = y2 | ((buf[sign*(i+1)-1] & 0x0f)<<8);	//Byte5		11				

					touchSize = buf[sign*(i+1)+2] ;//touchSize = coor_data[4];

					if (i > CT_MAX_TOUCH - 1) {
							break;
					}					
					printf("touch id:%d,\n",i);
					
					if((y2 == tp_dev.x[i])&&(x2 == tp_dev.y[i]))
						ret = 2;
					else
						ret = 1;
				
					tp_dev.size[i] = touchSize;

					if (TP_LEVEL) {
							tp_dev.x[i] = y2;
							tp_dev.y[i] = x2;				
					} else {					
							tp_dev.x[i] = x2;
							tp_dev.y[i] = y2;
					}
					if (X_MIRRORING) {
							tp_dev.x[i] = TP_MAX_X - 1 - tp_dev.x[i];
					}
					if (Y_MIRRORING) {
							tp_dev.y[i] = TP_MAX_Y - 1 - tp_dev.y[i];
					}					
					*x = tp_dev.x[i];
					*y = tp_dev.y[i];
				} 
		}
		else {
				touch_num = 0;
		}

#endif		
		return ret;
}

/******************************************************************************************************************************************
* ��������:	CHSC6540_Init()
* ����˵��:	CHSC6540��ʼ��
* ��    ��: ��
* ��    ��: uint8_t				1 ��ʼ���ɹ�   0 ��ʼ��ʧ��
* ע������: ��
******************************************************************************************************************************************/
uint8_t CHSC6540_Init(void)
{	
//I2C��ʼ��
	MX_I2C2_Init();
// CTP INT Ĭ�ϸߵ�ƽ  ����ģʽ  ���ش���
// CTP RST Ĭ�ϵ͵�ƽ  ���ģʽ  �޴���
//TP_INT��TP_RST�ܽų�ʼ��
	{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    __HAL_RCC_GPIOA_CLK_ENABLE();
		__HAL_RCC_GPIOD_CLK_ENABLE();

	/*Configure GPIO pin : TP_INT_Pin -> PA0  */
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);	

	/*Configure GPIO pin : TP_RST_Pin -> PD0 */
	GPIO_InitStruct.Pin = GPIO_PIN_0;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);


	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_RESET); //0 rst
	HAL_Delay(10);
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_0, GPIO_PIN_SET); //1 rst
	HAL_Delay(10);
	}
  return 0;
}


