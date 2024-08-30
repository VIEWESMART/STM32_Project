/*
 * SDL_timer.c
 *
 *  Created on: Dec 4, 2020
 *      Author: ZKSWE Develop Team
 */
#include "timer/timer.h"
#include "context/message.h"

#define TIMER_INTERVAL_10MS		10

static uint32_t s_last_ticks_10ms;
static uint32_t s_ticks_count_10ms;

bool timer_init() {
	 printf("timer_init \n");
	s_last_ticks_10ms = HAL_GetTick();
	 printf("timer_init 2222\n");
	s_ticks_count_10ms = 0;
	
	return true;
}

void timer_deinit() {

}

void timer_check() {
	uint32_t tick = HAL_GetTick();
	if (tick - s_last_ticks_10ms > TIMER_INTERVAL_10MS) {
		// printf("tick %d\n", tick);
		s_last_ticks_10ms = tick;
		s_ticks_count_10ms++;

		msg_t m = { E_MSG_TYPE_TIMER, TIMER_INTERVAL_10MS, s_ticks_count_10ms };
		message_enqueue(&m);
	}
}
