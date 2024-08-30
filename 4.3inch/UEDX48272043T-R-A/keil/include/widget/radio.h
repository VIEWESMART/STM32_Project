/*
 * radio.h
 *
 *  Created on: Dec 14, 2020
 *      Author: ZKSWE Develop Team
 */

#ifndef _WIDGET_RADIO_H_
#define _WIDGET_RADIO_H_

#include "widget.h"

typedef struct {
	WIDGET_COMMON;
} radio_t;

int radio_proc(widget_t *widget, const msg_t *m);

#endif /* _WIDGET_RADIO_H_ */
