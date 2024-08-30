#ifndef _LOGIC_RICE_H_
#define _LOGIC_RICE_H_

#include "context/guicontext.h"

#define UI_WIDGET_RICE_Button1              ((button_t*)gui_context_find_widget(2))
#define UI_WIDGET_RICE_Button2              ((button_t*)gui_context_find_widget(3))

void ui_rice_on_page_open(uint8_t page);

/**
 * @brief 定时器回调接口
 * @param time   定时器周期，单位 ms
 * @param count  累计次数
 */
void ui_rice_on_timer(uint32_t millisecond, uint32_t count);

/**
 * @brief 按钮点击事件回调接口
 * @param button   按钮控件指针
 * @param type     触摸事件类型
 */
void ui_rice_on_button_touch_event(button_t *button, touch_type_e type);

/**
 * @brief 进度条回调接口
 * @param progress  进度条控件指针
 * @param val       进度值
 */
void ui_rice_on_progress_changed(progress_t *progress, uint16_t val);

/**
 * @brief 动画播放结束回调接口
 * @param animation  动画控件指针
 */
void ui_rice_on_animation_play_end(animation_t *animation);

#endif /*_LOGIC_RICE_H_*/
