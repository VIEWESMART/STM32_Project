/*
 * button.h
 *
 *  Created on: Nov 12, 2020
 *      Author: ZKSWE Develop Team
 */

#ifndef _WIDGET_BUTTON_H_
#define _WIDGET_BUTTON_H_

#include "widget.h"

#define BUTTON_FLAG_OPEN_PAGE      0x1000
#define BUTTON_FLAG_SWITCH         0x2000
#define BUTTON_FLAG_RADIOITEM      0x4000

typedef struct {
	WIDGET_COMMON;

	graph_t press;
	uint8_t keycode;
	uint8_t pageid;
	int16_t page_pos_x;
	int16_t page_pos_y;
	uint16_t keyid;
	uint8_t reserved[2];
} button_t;

/**
 * @brief 按钮开关切换
 * @param button 控件指针
 * @param on     true 按下状态，false 弹起状态
 */
void button_switch(button_t *button, bool on);

int button_proc(widget_t *widget, const msg_t *m);

#endif /* _WIDGET_BUTTON_H_ */
