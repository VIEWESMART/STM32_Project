/*
 * video.h
 *
 *  Created on: Nov 29, 2020
 *      Author: ZKSWE Develop Team
 */

#ifndef _GRAPHICS_VIDEO_H_
#define _GRAPHICS_VIDEO_H_

#include "context/common.h"
#include "dev_pwm.h"

#include "IM_Controls.h"

typedef struct {
	uint16_t width;
	uint16_t height;
	uint8_t bpp;
	uint32_t *disp_buff;
} video_info_t;

bool video_init();
void video_deinit();
void video_flip();

#define ED_3_5	 0


#if LCD_BL_USE_PWM
#if UE019QV_AB40_A001A		//170x320
#define LCD_BL_OFF() 	setBackLightOn()
#define LCD_BL_ON() 	setBackLightOff()
#endif
#if UE035HV_RB40_A118_ST7796S		//480x320
#define LCD_BL_OFF() 	setBackLightOn()
#define LCD_BL_ON() 	setBackLightOff()
#endif
#if UE039HV_RB40_A009A_4SPI_3041A			//480x272
#define LCD_BL_OFF() 	setBackLightOff()
#define LCD_BL_ON() 	setBackLightOn()
#endif
#if UE024QV_RB40_A038A_9307		//170x320
#define LCD_BL_OFF() 	setBackLightOn()
#define LCD_BL_ON() 	setBackLightOff()
#endif

#else
#if UE019QV_AB40_A001A		//170x320
#define LCD_BL_OFF() 	setBackLightOn()
#define LCD_BL_ON() 	setBackLightOff()
#endif
#if UE035HV_RB40_A118_ST7796S		//480x320
#define LCD_BL_OFF() 	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_RESET)
#define LCD_BL_ON() 	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_SET)
#endif
#if UE039HV_RB40_A009A_4SPI_3041A			//480x272
#define LCD_BL_OFF() 	setBackLightOff()
#define LCD_BL_ON() 	setBackLightOn()
#endif
#if UE024QV_RB40_A038A_9307		//170x320
#define LCD_BL_OFF() 	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_RESET)
#define LCD_BL_ON() 	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_SET)

#endif


#endif

#endif /* _GRAPHICS_VIDEO_H_ */
