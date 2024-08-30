/*
 * imagetext.h
 *
 *  Created on: Dec 11, 2020
 *      Author: ZKSWE Develop Team
 */

#ifndef _WIDGET_IMAGETEXT_H_
#define _WIDGET_IMAGETEXT_H_

#include "widget.h"

#define IMAGETEXT_FLAG_WITH_COLORKEY      0x1000
#define IMAGETEXT_FLAG_DIGITAL            0x2000

#define IMAGETEXT_FLAG_ALIGN_LEFT         0x0000
#define IMAGETEXT_FLAG_ALIGN_HCENTER      0x0400
#define IMAGETEXT_FLAG_ALIGN_RIGHT        0x0800
#define IMAGETEXT_FLAG_ALIGN_HMASK        (IMAGETEXT_FLAG_ALIGN_LEFT | IMAGETEXT_FLAG_ALIGN_HCENTER | IMAGETEXT_FLAG_ALIGN_RIGHT)

#define IMAGETEXT_FLAG_ALIGN_TOP          0x0000
#define IMAGETEXT_FLAG_ALIGN_VCENTER      0x4000
#define IMAGETEXT_FLAG_ALIGN_BOTTOM       0x8000
#define IMAGETEXT_FLAG_ALIGN_VMASK        (IMAGETEXT_FLAG_ALIGN_TOP | IMAGETEXT_FLAG_ALIGN_VCENTER | IMAGETEXT_FLAG_ALIGN_BOTTOM)

typedef struct {
	WIDGET_COMMON;

	uint16_t res;
	uint16_t colorkey;
	char text[16];
} imagetext_t;

/**
 * @brief 设置艺术字文本内容
 * @param imagetext 控件指针
 * @param text      文本内容，最长16字节
 */
void imagetext_set_text(imagetext_t *imagetext, const char *text);

int imagetext_proc(widget_t *widget, const msg_t *m);

#endif /* _WIDGET_IMAGETEXT_H_ */
