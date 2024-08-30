/*
 * qrcode.h
 *
 *  Created on: Dec 28, 2020
 *      Author: ZKSWE Develop Team
 */

#ifndef _WIDGET_QRCODE_H_
#define _WIDGET_QRCODE_H_

#include "widget.h"

typedef struct {
	WIDGET_COMMON;

	uint16_t fore_color;  // 前景色
	uint16_t res;
	char *str;
} qrcode_t;

/**
 * @brief 加载二维码数据
 * @param qrcode 控件指针
 * @param str    二维码数据
 */
void qrcode_load(qrcode_t *qrcode, const char *str);

int qrcode_proc(widget_t *widget, const msg_t *m);

#endif /* _WIDGET_QRCODE_H_ */
