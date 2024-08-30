#include "delay.h"
 
//��ʱnms
void delay_ms(int32_t ms) 
{
  int32_t temp; 
  SysTick->LOAD = (SystemCoreClock/8000)*ms; 
  SysTick->VAL = 0x00;//��ռ����� 
  SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//��ʼ����  
  do
	{ 
      temp = SysTick->CTRL;//��ȡ��ǰ������ֵ 
  }while((temp&0x01)&&(!(temp&(1<<16))));//�ȴ�ʱ�䵽�� 
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL = 0x00; //��ռ����� 
//	HAL_Delay(ms);
}

 
//��ʱnus
void delay_us(int32_t us)
{		
	int32_t temp;	    	 
	SysTick->LOAD = (SystemCoreClock/8000000)*us; 					//ʱ�����	  		 
	SysTick->VAL = 0x00;        					//��ռ�����
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;	//��ʼ����	  
	do
	{
			temp = SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//�ȴ�ʱ�䵽��   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	//�رռ�����
	SysTick->VAL = 0x00;      					 //��ռ�����	 
	
}
 
