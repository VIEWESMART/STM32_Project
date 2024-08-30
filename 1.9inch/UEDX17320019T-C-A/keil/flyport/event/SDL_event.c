/*
 * SDL_event.c
 *
 *  Created on: Nov 29, 2020
 *      Author: ZKSWE Develop Team
 */

#include <stdlib.h>
#include "event.h"
#include "context/message.h"

#include "all_iic.h"

#define Whether_to_enable_touch			1

bool event_init() {
#if Whether_to_enable_touch
	CHSC6540_Init();
#endif
	printf("init event:CTP\n");
	return true;
}

void event_deinit() {
	
}

bool event_poll() {
#if Whether_to_enable_touch
	uint16_t x,y;
	static uint32_t tick30ms = 0;
	uint8_t ret = 0;
	if(HAL_GetTick() - tick30ms > 30) {
		tick30ms = HAL_GetTick();
		ret = CHSC6540_Scan(&x,&y);
	} 
	if(ret == 0) return 0;
	
	msg_t m = { E_MSG_TYPE_TOUCHEVENT, E_TOUCH_DOWN, MAKEDWORD(x, y) };
	if (ret == 1) {
		m.param1 = E_TOUCH_DOWN;
		printf("touchd down:%d,%d\n",x,y);
	} else if (ret == 2) {
		m.param1 = E_TOUCH_MOVE;
		printf("touchm move:%d,%d\n",x,y);
	} else if (ret == 3) {
		m.param1 = E_TOUCH_UP;
		//printf("touchu:%d,%d\n",x,y);
	}
	message_enqueue(&m);
#endif
	
	return false;
}


