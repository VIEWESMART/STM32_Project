/*
 * guicontext.h
 *
 *  Created on: Nov 13, 2020
 *      Author: ZKSWE Develop Team
 */

#ifndef _CONTEXT_GUICONTEXT_H_
#define _CONTEXT_GUICONTEXT_H_

#include "widget/image.h"
#include "widget/label.h"
#include "widget/animation.h"
#include "widget/button.h"
#include "widget/progress.h"
#include "widget/imagetext.h"
#include "widget/radio.h"
#include "widget/window.h"

typedef struct {

	bool (*init_video)();
	bool (*init_timer)();
	bool (*init_event)();

	void (*deinit_video)();
	void (*deinit_timer)();
	void (*deinit_event)();

	void (*poll_event)();
	void (*poll_timer)();
	void (*flip_video)();

	void (*cb_on_timer)(uint32_t time, uint32_t ticks);
	void (*cb_on_pageopen)(uint8_t page);
	void (*cb_on_button_touch_event)(button_t *button, touch_type_e type);
	void (*cb_on_progress_changed)(progress_t *progress, uint16_t val);
    void (*cb_on_animation_play_end)(animation_t *animation);
    void (*cb_on_increment_change)(increment_t *increment,uint16_t val,uint16_t regid);
	void (*fly_debug)(const char* arg,...);
} flythings_callback;

extern flythings_callback m_user_cb;
#define FLY_DEBUG m_user_cb.fly_debug
//���ڲ��԰汾
#define FLYUI_OPENTEST	

//#define  USE_800x480    0

bool gui_context_setcbs(flythings_callback* cbs);

bool gui_context_init(const flythings_callback* cbs,uint16_t screen_w,uint16_t screen_h,uint8_t bpp,uint32_t* frambuff);
void gui_context_run(void);
void gui_context_deinit(void);


/**
 * @brief 打开页面
 * @param page 页面ID
 */
bool gui_context_open_page(uint8_t page);

/**
 * @brief 获取当前页面ID
 * @return 页面ID
 */
uint8_t gui_context_get_current_page();

/**
 * @brief 通过ID值找控件
 * @param id   控件ID
 * @return 控件指针，找不到则返回NULL
 */
widget_t* gui_context_find_widget(uint8_t id);


/********************* callback fun *********************/

/**
 * @brief 定时器回调接�?
 * @param time   定时器周期，单位 ms
 * @param ticks  累计次数
 */
extern void on_timer(uint32_t time, uint32_t ticks);

/**
 * @brief 页面打开回调接口
 * @param page   页面ID
 */
extern void on_page_open(uint8_t page);

/**
 * @brief 按钮点击事件回调接口
 * @param button   按钮控件指针
 * @param type     触摸事件类型
 */
extern void on_button_touch_event(button_t *button, touch_type_e type);

/**
 * @brief 进度条回调接�?
 * @param progress  进度条控件指�?
 * @param val       进度�?
 */
extern void on_progress_changed(progress_t *progress, uint16_t val);

/**
 * @brief 动画播放结束回调接口
 * @param animation  动画控件指针
 */
extern void on_animation_play_end(animation_t *animation);

/********************************************************/

#endif /* _CONTEXT_GUICONTEXT_H_ */
