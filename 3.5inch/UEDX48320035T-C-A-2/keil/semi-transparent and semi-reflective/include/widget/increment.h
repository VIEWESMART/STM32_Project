/*
 * increment.h
 *
 *  Created on: Feb 27, 2021
 *      Author: ZKSWE Develop Team
 */

#ifndef _WIDGET_INCREMENT_H_
#define _WIDGET_INCREMENT_H_

#include "widget.h"

#define INCREMENT_FLAG_LOOP      0x1000    // 循环调节

typedef struct {
	WIDGET_COMMON;

	int16_t stride;         // 步进值
	int16_t lower_limit;    // 下限值
	int16_t upper_limit;    // 上限值
	uint16_t interval;      // 长按持续调节的时间间隔
} increment_t;

int increment_proc(widget_t *widget, const msg_t *m);

#endif /* _WIDGET_INCREMENT_H_ */
