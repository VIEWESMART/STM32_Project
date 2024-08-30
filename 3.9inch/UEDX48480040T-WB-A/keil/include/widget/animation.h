/*
 * animation.h
 *
 *  Created on: Dec 4, 2020
 *      Author: ZKSWE Develop Team
 */

#ifndef _WIDGET_ANIMATION_H_
#define _WIDGET_ANIMATION_H_

#include "widget.h"

#define ANIMATION_FLAG_PLAY      0x1000

typedef struct {
	WIDGET_COMMON;

	graph_t start;
	graph_t end;
	uint16_t play_index;
	uint16_t interval;		// 图片播放时间间隔，单位ms
	uint16_t loops;			// 轮播次数，0表示不断循环播放
	uint16_t loop_count;
} animation_t;


/**
 * @brief 启动动画
 * @param anim 控件指针
 */
void animation_start(animation_t *anim);

/**
 * @brief 停止动画
 * @param anim 控件指针
 */
void animation_stop(animation_t *anim);

/**
 * @brief 重置动画
 * @param anim 控件指针
 */
void animation_reset(animation_t *anim);

int animation_proc(widget_t *widget, const msg_t *m);

#endif /* _WIDGET_ANIMATION_H_ */
