/*
 * DEV_PWM.h
 *
 *  Created on: Jul 15, 2021
 *      Author: laiyj
 */
 
#ifndef __DEV_TIM3_PWM_H_
#define __DEV_TIM3_PWM_H_

//��Ļ����ʹ��PWM���� 0:��ʹ�� 1:ʹ��
#define LCD_BL_USE_PWM		0


//void DEV_TIM3_Init(void);	//PWM��ʼ��
//���⿪-ȫ��
void setBackLightOn(void);
//���ñ�������
void setBackLightPWM(unsigned short pwm);
//�����
void setBackLightOff(void);

void DEV_TIM3_1_Init(void);

#endif
