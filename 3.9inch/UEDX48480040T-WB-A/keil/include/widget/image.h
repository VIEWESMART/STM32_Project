/*
 * image.h
 *
 *  Created on: Dec 4, 2020
 *      Author: ZKSWE Develop Team
 */

#ifndef _WIDGET_IMAGE_H_
#define _WIDGET_IMAGE_H_

#include "widget.h"

#define IMAGE_FLAG_WITH_COLORKEY      0x1000

typedef struct {
	WIDGET_COMMON;

	uint16_t colorkey;
	uint8_t reserve[2];
} image_t;

int image_proc(widget_t *widget, const msg_t *m);

#endif /* _WIDGET_IMAGE_H_ */
