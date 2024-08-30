/*
 * dev_rgbLed.h
 *
 *  Created on: Mar 03, 2022
 *      Author: laiyj
 */

#ifndef _DEV_RGBLED_H_
#define _DEV_RGBLED_H_

#include "main.h"
#include <stdio.h>


//���ȷ�Χ
#define RGBLED_LUMI0 	0		//�������
#define RGBLED_LUMIMAX	100		//�������


//LED IDö��
typedef enum {
	LED_R = 0,
	LED_G,
	LED_B,
}LED_ID_NUM;

//RGB LED�ṹ��
typedef struct {
	uint8_t R_tar;		//Ŀ��ֵ
	uint8_t G_tar;
	uint8_t B_tar;
	uint8_t flag;		//turn on/off
	uint8_t current;	//��ǰֵ
	uint8_t period;		//����ֵ
}RGBLED_PWM_STRUCT;

//�����ƽṹ��
typedef struct {
	uint8_t led_id;		//LED��ID
	uint16_t ITV_time;	//���ʱ��
	uint16_t PRD_time;	//����ʱ��
	uint16_t loop_num;	//��������
}LED_BREATH_STRUCT;



void dev_rgbLed_init(void);
void turn_off_rgbled(void);
void turn_on_rgbled(void);
void set_rgbled(uint8_t r, uint8_t g, uint8_t b);
void RGBLED_Proc(void);

void set_breathe_led(uint8_t id, uint16_t loop_num);
void LED_Breatheproc(void);

#endif 
