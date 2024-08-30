/*
 * progress.h
 *
 *  Created on: Nov 17, 2020
 *      Author: ZKSWE Develop Team
 */

#ifndef _WIDGET_PROGRESS_H_
#define _WIDGET_PROGRESS_H_

#include "widget.h"

// 默认水平方向，设置该标记后为垂直方向
#define PROGRESS_FLAG_ORIENTATION_VERTICAL        0x1000

typedef struct {
	WIDGET_COMMON;

	graph_t valid;			// 有效图
	graph_t block_normal;	// 滑块正常显示图片或颜色
	graph_t block_pressed;	// 滑块按下显示图片或颜色
	uint8_t block_w;		// 滑块宽
	uint8_t block_h;		// 滑块高
	uint16_t max_val;		// 最大值
	uint16_t val;			// 当前值
} progress_t;

/**
 * @brief 设置进度值
 * @param progress 控件指针
 * @param val      进度值
 */
void progress_set_value(progress_t *progress, uint16_t val);

int progress_proc(widget_t *widget, const msg_t *m);

#endif /* _WIDGET_PROGRESS_H_ */
