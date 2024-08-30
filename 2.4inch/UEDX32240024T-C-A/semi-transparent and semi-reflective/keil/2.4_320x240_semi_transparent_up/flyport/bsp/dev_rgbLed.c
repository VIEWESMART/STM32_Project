/*
 * dev_rgbLed.c
 *
 *  Created on: Mar 03, 2022
 *      Author: laiyj
 */

/*
 * 说明：
 * LED的PWM频率100HZ，占空比:0-100，在定时器100us中处理；
 * 注意，如果只是想作为设置灯亮度使用，需在定时器中断中屏蔽掉LED_Breatheproc();函数
*/
#include "dev_rgbLed.h"

static void DEV_RGBLED_GPIO_Init(void);
static void MX_TIM16_Init(void);


//PWM周期 (灯亮度设置)
#define PWM_PERIOD	RGBLED_LUMIMAX  // 10k/100 = 100 Hz , 与定时器配置紧密相关
//呼吸灯每单位变化间隔时间
#define BREATHE_INERVAL_TIME	50//150  //uint:0.1ms , 与定时器配置紧密相关
//LED-R
#define LED_R_H()		(GPIOA->BSRR = GPIO_PIN_0) //亮
#define LED_R_L()		(GPIOA->BRR = GPIO_PIN_0) //灭
//LED-G
#define LED_G_H()		(GPIOA->BSRR = GPIO_PIN_5)
#define LED_G_L()		(GPIOA->BRR = GPIO_PIN_5)
//LED-B
#define LED_B_H()		(GPIOC->BSRR = GPIO_PIN_7)
#define LED_B_L()		(GPIOC->BRR = GPIO_PIN_7)


//RGB LED信息
volatile RGBLED_PWM_STRUCT rgbled_pwm_str = { 
	RGBLED_LUMI0, RGBLED_LUMI0, RGBLED_LUMI0, 
	0, 0, PWM_PERIOD 
};

//呼吸灯信息
volatile LED_BREATH_STRUCT led_breath = {
	.led_id = LED_G,
	.ITV_time = BREATHE_INERVAL_TIME,
	.PRD_time = RGBLED_LUMIMAX,
	.loop_num = 0
};


//RGB LED初始化
void dev_rgbLed_init(void) {
	DEV_RGBLED_GPIO_Init();
	MX_TIM16_Init(); 
	//turn_on_rgbled(); //打开rgb led
}
//关闭rgb led
void turn_off_rgbled(void) {
	rgbled_pwm_str.flag = 0;
}

//打开rgb led
void turn_on_rgbled(void) {
	rgbled_pwm_str.flag = 1;
}

//设置rgb led
void set_rgbled(uint8_t r, uint8_t g, uint8_t b) {
	HAL_NVIC_DisableIRQ(TIM16_IRQn);
	if(r > RGBLED_LUMIMAX) r = RGBLED_LUMIMAX;
	if(g > RGBLED_LUMIMAX) g = RGBLED_LUMIMAX;
	if(b > RGBLED_LUMIMAX) b = RGBLED_LUMIMAX;
	rgbled_pwm_str.R_tar = r;
	rgbled_pwm_str.G_tar = g;
	rgbled_pwm_str.B_tar = b;
	HAL_NVIC_EnableIRQ(TIM16_IRQn);
}

//RBG LED显示处理
void RGBLED_Proc(void) {
	static uint8_t f = 1; //标志
	if(rgbled_pwm_str.flag == 0) {
		if(f) {
			f = 0;
			LED_R_L(); LED_G_L(); LED_B_L();
		}
		return;
	}
	f = 1;
	//R
	if(rgbled_pwm_str.current < rgbled_pwm_str.R_tar) 
		LED_R_H();
	else 
		LED_R_L();
	//G
	if(rgbled_pwm_str.current < rgbled_pwm_str.G_tar) 
		LED_G_H();
	else 
		LED_G_L();
	//B
	if(rgbled_pwm_str.current < rgbled_pwm_str.B_tar) 
		LED_B_H();
	else 
		LED_B_L();
	
	if(rgbled_pwm_str.current < rgbled_pwm_str.period) 
		rgbled_pwm_str.current++;
	else 
		rgbled_pwm_str.current = 0;
}


/*
* 设置呼吸灯
* id: LED的id
* loop_num: 呼吸循环次数，设置为0则无限呼吸
**/
void set_breathe_led(uint8_t id, uint16_t loop_num) {
	HAL_NVIC_DisableIRQ(TIM16_IRQn);
	turn_on_rgbled(); //打开rgb led
	led_breath.led_id = id;
	led_breath.loop_num = loop_num;
	HAL_NVIC_EnableIRQ(TIM16_IRQn);
}

//呼吸灯处理
void LED_Breatheproc(void) {
	static uint16_t itv_cur = 0, prd_cur = 0;
	
	//灯关闭直接返回
	if(rgbled_pwm_str.flag == 0) return;
	
	itv_cur++;
	if(itv_cur > led_breath.ITV_time) {
		itv_cur = 0;
		prd_cur++;
		if(prd_cur >= (led_breath.PRD_time << 1)) {
			prd_cur = 0;
			if(led_breath.loop_num > 0){
				led_breath.loop_num--;
				if(led_breath.loop_num == 0) {
					turn_off_rgbled(); //灯关rgb led
					return;
				}
			}
		}
		if(prd_cur < led_breath.PRD_time) {
			if(led_breath.led_id == LED_R)
				set_rgbled(prd_cur%led_breath.PRD_time, 0, 0);
			else if(led_breath.led_id == LED_G)
				set_rgbled(0, prd_cur%led_breath.PRD_time, 0);
			else
				set_rgbled(0, 0, prd_cur%led_breath.PRD_time);
		}
		else {
			if(led_breath.led_id == LED_R)
				set_rgbled(led_breath.PRD_time-(prd_cur%led_breath.PRD_time), 0, 0);
			else if(led_breath.led_id == LED_G)
				set_rgbled(0, led_breath.PRD_time-(prd_cur%led_breath.PRD_time), 0);
			else
				set_rgbled(0, 0, led_breath.PRD_time-(prd_cur%led_breath.PRD_time));
		}
	}
}


//RGB LED管脚初始化
static void DEV_RGBLED_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_5, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);

  /*Configure GPIO pins : PA0 PA5 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PC7 */
  GPIO_InitStruct.Pin = GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}

//定时器句柄
TIM_HandleTypeDef htim16;
//定时100us中断
static void MX_TIM16_Init(void)
{
	__HAL_RCC_TIM16_CLK_ENABLE();
	
	htim16.Instance = TIM16;
	htim16.Init.Prescaler = 64-1;
	htim16.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim16.Init.Period = 100-1;
	htim16.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim16.Init.RepetitionCounter = 0;
	htim16.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	if (HAL_TIM_Base_Init(&htim16) != HAL_OK)
	{
		Error_Handler();
	}
	
	HAL_NVIC_SetPriority(TIM16_IRQn, 0, 2);
	HAL_NVIC_EnableIRQ(TIM16_IRQn);
	HAL_TIM_Base_Start_IT(&htim16);	//中断定时器开启
}
//定时器中断处理
void TIM16_IRQHandler(void)
{
	//printf("TIM16 1ms \r\n");
	LED_Breatheproc();
	RGBLED_Proc();
	
	__HAL_TIM_CLEAR_IT(&htim16,TIM_IT_UPDATE);	//清除中断标志位
}
