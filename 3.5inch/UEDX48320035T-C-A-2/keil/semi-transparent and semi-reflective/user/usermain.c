/*
 * usermain.c
 *
 *  Created on: Jun 12, 2020
 *      Author: 钟
 */

#include "main.h"
#include "devmodule.h"
#include "context/guicontext.h"
#include "event/event.h"
#include "timer/timer.h"
#include "graphics/video.h"
#include "context/resource.h"
#include "input.h"
#include "other_app.h"
#include "dev_time17.h"
#include "dev_rgbLed.h"

#include "IM_Controls.h"

const S_DEV* uartdev;

void on_increment_change (increment_t *increment,uint16_t val,uint16_t regid) {	}
void print_null(const char *arg, ...){ }

static uint32_t tick2ms = 0;
static uint32_t tick5ms = 0;
static uint32_t tick10ms = 0;
static uint32_t tick50ms = 0;
static uint32_t tick100ms = 0;
static uint32_t tick500ms = 0;
static uint32_t tick1s = 0;
static uint32_t tick60s = 0;
extern const flythings_flash	m_flash;
const flythings_callback_t cbs={
	.init_event = event_init,
	.init_timer = timer_init,
	.init_video = video_init,
	.deinit_event = event_deinit,
	.deinit_timer = timer_deinit,
	.deinit_video = video_deinit,
	.cb_on_pageopen = on_page_open,
	.cb_on_animation_play_end = on_animation_play_end,
	.cb_on_button_touch_event = on_button_touch_event,
	.cb_on_progress_changed = on_progress_changed,
	.cb_on_timer = on_timer,
	.poll_timer = timer_check,
	.poll_event = event_poll,
	.flip_video = video_flip,
	.cb_on_increment_change = on_increment_change,
	.fly_debug = printf//print_null
};


/*
 * 变量类型必须要uint32_t
 */
uint32_t meminfo[1024/4];
#define REGISTERSIZE	1 //不使用，设置为最小1即可
uint16_t regsize[REGISTERSIZE]; 
typedef enum{
	E_SETARG_XINDEX = 0,
	E_SETARG_YINDEX,  
	E_SETARG_WIDGETINVALUD_ALL, // 重叠部分再次刷新,默认打开
}E_SETARG;
extern void* gui_context_setarg(E_SETARG arg, void* argp);


void user_init(void){
#if LCD_BL_USE_PWM	
	DEV_TIM3_1_Init();
	
#endif
	MX_TIM17_Init();
	
	IM_Init();
	
	//dev_rgbLed_init();
	uartdev = loadDev(&dev_uartupgrade);
		
 	printf("load uart \r\n");
	printf("led on\n");
	tick10ms = get_time_num();
	tick50ms = get_time_num();
	tick100ms = get_time_num();
	tick500ms = get_time_num();
	tick1s = get_time_num();
	tick60s = get_time_num();
	tick5ms = get_time_num();
	tick2ms = get_time_num();
	
	m_flash.flash_init();
	video_info_t vi = { 240, 240, 16, 0 };
	for(int i = 0; i < REGISTERSIZE; i++) {
		regsize[i] = 0;
	}
	if(gui_context_init(&vi,&cbs,&m_flash,(uint8_t*)meminfo,1024,regsize,REGISTERSIZE)){
		gui_context_setarg(E_SETARG_XINDEX, (void*)0);
		gui_context_setarg(E_SETARG_YINDEX, (void*)0);
		gui_context_setarg(E_SETARG_WIDGETINVALUD_ALL, (void*)1);
		
		gui_context_open_page(0);
		printf("open page 0\n");
	}
	gui_context_run();
	
	HAL_Delay(20);
	LCD_BL_ON();	
}

uint8_t ui_page = 0; //test
void user_loop(void){
	static uint32_t systick = 0;
	gui_context_run();	
	systick = get_time_num();
	if((systick-tick10ms) > 10){
	  tick10ms = systick;
 	  uartdev->procMsg(DEVMSG_TIMER10ms,0,0);
		otherapp.procMsg(DEVMSG_TIMER10ms,0,0);
	}
	if((systick-tick5ms) > 2){
	  tick5ms = systick;
	}
	if((systick-tick50ms) > 50){
	  tick50ms = systick;
	  uartdev->procMsg(DEVMSG_TIMER50ms,0,0);

	}
	if((systick - tick100ms) >= 100){
	  tick100ms = systick;
	  uartdev->procMsg(DEVMSG_TIMER100ms,0,0);

	}
	if((systick - tick500ms) >= 500){
	  tick500ms = systick;
		
	}
	if((systick - tick1s) >= 1000){
		tick1s = systick;
		printf("tick1s\n");
	}
	if((systick - tick60s) >= 60000){
		tick60s = systick;
	}
}