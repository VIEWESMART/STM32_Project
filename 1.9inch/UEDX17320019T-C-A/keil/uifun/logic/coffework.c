#include "logic/coffework.h"

static uint8_t img_id = 49;

void ui_coffework_on_page_open(uint8_t page) {
	char buff[2];
	buff[0] = img_id;
	buff[1] = '\0';
	imagetext_set_text(UI_WIDGET_COFFEWORK_ArtText2, &buff[0]);
}

/**
 * @brief 定时器回调接口
 * @param millisecond   定时器周期，单位 ms
 * @param count  累计次数
 */
void ui_coffework_on_timer(uint32_t millisecond, uint32_t count) {
	char buff[2];
	if(count %100 == 0) {	
		if(img_id >= 49) img_id++;
		if(img_id > 50) img_id = 49;
		buff[0] = img_id;
		buff[1] = '\0';
		imagetext_set_text(UI_WIDGET_COFFEWORK_ArtText2, &buff[0]);
	}
}

/**
 * @brief 按钮点击事件回调接口
 * @param button   按钮控件指针
 * @param type     触摸事件类型
 */
void ui_coffework_on_button_touch_event(button_t *button, touch_type_e type) {
	if(type == E_TOUCH_DOWN) {
		if(button == UI_WIDGET_COFFEWORK_Button1) {
			printf("COFFEWORK_Button1 down\n");
		}
	}
}

/**
 * @brief 进度条回调接口
 * @param progress  进度条控件指针
 * @param val       进度值
 */
void ui_coffework_on_progress_changed(progress_t *progress, uint16_t val) {

}

/**
 * @brief 动画播放结束回调接口
 * @param animation  动画控件指针
 */
void ui_coffework_on_animation_play_end(animation_t *animation) {
	if(animation == UI_WIDGET_COFFEWORK_Animation1) {
		//重置动画
		animation_reset(UI_WIDGET_COFFEWORK_Animation1);
	}
}
