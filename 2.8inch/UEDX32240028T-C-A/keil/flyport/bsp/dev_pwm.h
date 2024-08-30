/*
 * DEV_PWM.h
 *
 *  Created on: Jul 15, 2021
 *      Author: laiyj
 */
 
#ifndef __DEV_TIM3_PWM_H_
#define __DEV_TIM3_PWM_H_

//屏幕背光使用PWM调节 0:不使用 1:使用
#define LCD_BL_USE_PWM		0


//void DEV_TIM3_Init(void);	//PWM初始化
//背光开-全亮
void setBackLightOn(void);
//设置背光亮度
void setBackLightPWM(unsigned short pwm);
//背光关
void setBackLightOff(void);

void DEV_TIM3_1_Init(void);

#endif
