/*
 * label.h
 *
 *  Created on: Nov 25, 2020
 *      Author: ZKSWE Develop Team
 */

#ifndef _WIDGET_LABEL_H_
#define _WIDGET_LABEL_H_

#include "widget.h"

#define TEXT_ALIGN_LEFT          0x00
#define TEXT_ALIGN_HCENTER       0x01
#define TEXT_ALIGN_RIGHT         0x02
#define TEXT_ALIGN_HMASK         (TEXT_ALIGN_LEFT | TEXT_ALIGN_HCENTER | TEXT_ALIGN_RIGHT)

#define TEXT_ALIGN_TOP           0x00
#define TEXT_ALIGN_VCENTER	     0x04
#define TEXT_ALIGN_BOTTOM        0x08
#define TEXT_ALIGN_VMASK         (TEXT_ALIGN_TOP | TEXT_ALIGN_VCENTER | TEXT_ALIGN_BOTTOM)

typedef enum {
	E_CHAR_CODE_ASCII,
	E_CHAR_CODE_GB2312,
	E_CHAR_CODE_GBK,
} char_code_e;

typedef struct {
	WIDGET_COMMON;

	uint8_t align : 4;
	uint8_t static_txt : 1;
	uint8_t code : 3;
	uint8_t font_size;
	uint16_t text_color;
	uint16_t res;
	uint8_t h_space;
	uint8_t v_space;
	char *text;
} label_t;

/**
 * @brief 设置文本，内部将申请内存存储文本数据
 * @param label  控件指针
 * @param text   文本指针
 */
void label_set_text(label_t *label, const char *text);

/**
 * @brief 设置静态文本
 * @param label  控件指针
 * @param text   文本指针，需保证该变量的有效性，如：全局指针，常量指针
 */
void label_set_static_text(label_t *label, const char *text);

/**
 * @brief 设置文本颜色
 * @param label  控件指针
 * @param color  文本颜色
 */
void label_set_text_color(label_t *label, uint16_t color);

int label_proc(widget_t *widget, const msg_t *m);

#endif /* _WIDGET_LABEL_H_ */
