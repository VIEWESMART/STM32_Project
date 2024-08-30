/*
 * numtext.h
 *
 *  Created on: Mar 1, 2021
 *      Author: ZKSWE Develop Team
 */

#ifndef _WIDGET_NUMTEXT_H_
#define _WIDGET_NUMTEXT_H_

#include "widget.h"

#define NUMTEXT_FLAG_WITH_COLORKEY      0x1000

#define NUMTEXT_FLAG_ALIGN_LEFT         0x0000
#define NUMTEXT_FLAG_ALIGN_HCENTER      0x0400
#define NUMTEXT_FLAG_ALIGN_RIGHT        0x0800
#define NUMTEXT_FLAG_ALIGN_HMASK        (NUMTEXT_FLAG_ALIGN_LEFT | NUMTEXT_FLAG_ALIGN_HCENTER | NUMTEXT_FLAG_ALIGN_RIGHT)

#define NUMTEXT_FLAG_ALIGN_TOP          0x0000
#define NUMTEXT_FLAG_ALIGN_VCENTER      0x4000
#define NUMTEXT_FLAG_ALIGN_BOTTOM       0x8000
#define NUMTEXT_FLAG_ALIGN_VMASK        (NUMTEXT_FLAG_ALIGN_TOP | NUMTEXT_FLAG_ALIGN_VCENTER | NUMTEXT_FLAG_ALIGN_BOTTOM)

typedef struct {
	WIDGET_COMMON;

	uint16_t res;
	uint16_t colorkey;
	int16_t val;
	uint8_t decimal_places;    // 小数位
	uint8_t reserve;
} numtext_t;

void numtext_set_val(numtext_t *numtext, int16_t val);

int numtext_proc(widget_t *widget, const msg_t *m);

#endif /* _WIDGET_NUMTEXT_H_ */
