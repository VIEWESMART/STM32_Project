#ifndef _LOGIC_OIL_H_
#define _LOGIC_OIL_H_

#include "context/guicontext.h"

#define UI_WIDGET_OIL_Button1              ((button_t*)gui_context_find_widget(2))
#define UI_WIDGET_OIL_Button2              ((button_t*)gui_context_find_widget(3))
#define UI_WIDGET_OIL_Button3              ((button_t*)gui_context_find_widget(4))
#define UI_WIDGET_OIL_Button4              ((button_t*)gui_context_find_widget(5))
#define UI_WIDGET_OIL_Button5              ((button_t*)gui_context_find_widget(6))
#define UI_WIDGET_OIL_Button6              ((button_t*)gui_context_find_widget(7))
#define UI_WIDGET_OIL_Button7              ((button_t*)gui_context_find_widget(8))
#define UI_WIDGET_OIL_Button8              ((button_t*)gui_context_find_widget(9))
#define UI_WIDGET_OIL_Button9              ((button_t*)gui_context_find_widget(10))
#define UI_WIDGET_OIL_ArtText1             ((imagetext_t*)gui_context_find_widget(11))
#define UI_WIDGET_OIL_ArtText2             ((imagetext_t*)gui_context_find_widget(12))
#define UI_WIDGET_OIL_ArtText4             ((imagetext_t*)gui_context_find_widget(13))

void ui_oil_on_page_open(uint8_t page);

/**
 * @brief 定时器回调接口
 * @param time   定时器周期，单位 ms
 * @param count  累计次数
 */
void ui_oil_on_timer(uint32_t millisecond, uint32_t count);

/**
 * @brief 按钮点击事件回调接口
 * @param button   按钮控件指针
 * @param type     触摸事件类型
 */
void ui_oil_on_button_touch_event(button_t *button, touch_type_e type);

/**
 * @brief 进度条回调接口
 * @param progress  进度条控件指针
 * @param val       进度值
 */
void ui_oil_on_progress_changed(progress_t *progress, uint16_t val);

/**
 * @brief 动画播放结束回调接口
 * @param animation  动画控件指针
 */
void ui_oil_on_animation_play_end(animation_t *animation);

#endif /*_LOGIC_OIL_H_*/
