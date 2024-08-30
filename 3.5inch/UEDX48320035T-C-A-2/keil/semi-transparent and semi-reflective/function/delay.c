#include "delay.h"
 
//延时nms
void delay_ms(int32_t ms) 
{
  int32_t temp; 
  SysTick->LOAD = (SystemCoreClock/8000)*ms; 
  SysTick->VAL = 0x00;//清空计数器 
  SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk ;	//开始倒数  
  do
	{ 
      temp = SysTick->CTRL;//读取当前倒计数值 
  }while((temp&0x01)&&(!(temp&(1<<16))));//等待时间到达 
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL = 0x00; //清空计数器 
//	HAL_Delay(ms);
}

 
//延时nus
void delay_us(int32_t us)
{		
	int32_t temp;	    	 
	SysTick->LOAD = (SystemCoreClock/8000000)*us; 					//时间加载	  		 
	SysTick->VAL = 0x00;        					//清空计数器
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk ;	//开始倒数	  
	do
	{
			temp = SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));		//等待时间到达   
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	//关闭计数器
	SysTick->VAL = 0x00;      					 //清空计数器	 
	
}
 
