#include "logic/wash.h"

void ui_wash_on_page_open(uint8_t page) {

}

/**
 * @brief 定时器回调接口
 * @param millisecond   定时器周期，单位 ms
 * @param count  累计次数
 */
void ui_wash_on_timer(uint32_t millisecond, uint32_t count) {

}

/**
 * @brief 按钮点击事件回调接口
 * @param button   按钮控件指针
 * @param type     触摸事件类型
 */
void ui_wash_on_button_touch_event(button_t *button, touch_type_e type) {
	if(type == E_TOUCH_DOWN) {
		if(button == UI_WIDGET_WASH_Button1) {
			printf("WASH_Button1 down\n");
		} else if(button == UI_WIDGET_WASH_Button2) {
			printf("WASH_Button2 down\n");
		}	
	} 
}

/**
 * @brief 进度条回调接口
 * @param progress  进度条控件指针
 * @param val       进度值
 */
void ui_wash_on_progress_changed(progress_t *progress, uint16_t val) {

}

/**
 * @brief 动画播放结束回调接口
 * @param animation  动画控件指针
 */
void ui_wash_on_animation_play_end(animation_t *animation) {

}
