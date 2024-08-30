/*
 * window.h
 *
 *  Created on: Nov 12, 2020
 *      Author: ZKSWE Develop Team
 */

#ifndef _WIDGET_WINDOW_H_
#define _WIDGET_WINDOW_H_

#include "widget.h"

typedef struct {
	WIDGET_COMMON;
	uint8_t reserved[3];
	uint8_t children_size;
	widget_t *children[1];
} window_t;

void window_set_position(window_t *window, const rect_t *pos);

#endif /* _WIDGET_WINDOW_H_ */
