/*
 * NEC_IR.c
 *
 *  Created on: Jul 15, 2021
 *      Author: Admin
 */
#include "main.h"
#include <stdio.h>
#include "dev_time17.h"
#include "other_app.h"


TIM_HandleTypeDef htim17;

uint32_t time_num = 0;

//定时1s中断
void MX_TIM17_Init(void)
{
	__HAL_RCC_TIM17_CLK_ENABLE();

	htim17.Instance = TIM17;
	htim17.Init.Prescaler = 64-1;
	htim17.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim17.Init.Period = 1000-1;

	htim17.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim17.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim17) != HAL_OK)
	{
		Error_Handler();
	}

	HAL_NVIC_SetPriority(TIM17_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM17_IRQn);
	HAL_TIM_Base_Start_IT(&htim17);	//中断定时器开启
}


void TIM17_IRQHandler(void)
{
	if(time_num > 65536)
			time_num = 0;
	
	time_num++;
	
	__HAL_TIM_CLEAR_IT(&htim17,TIM_IT_UPDATE);	//清除中断标志位
}


uint32_t get_time_num(void)
{
//	HAL_GetTick();
	return time_num;
}

