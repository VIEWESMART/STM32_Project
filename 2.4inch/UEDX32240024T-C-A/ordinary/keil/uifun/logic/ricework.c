#include "logic/ricework.h"

static uint8_t star_flag = 0;
static uint8_t time = 60;

void ui_ricework_on_page_open(uint8_t page) {
	//打开界面后重新赋值
	star_flag = 0;
	time = 60;
}

/**
 * @brief 定时器回调接口
 * @param millisecond   定时器周期，单位 ms
 * @param count  累计次数
 */
void ui_ricework_on_timer(uint32_t millisecond, uint32_t count) {
	char buff[5];
	//每1000ms变化数值, 1000/10 = 100
	if(count%100 == 0) {
		if(star_flag == 1) {
			if(time > 0) { 
				time--;
				sprintf(buff,"%02d",time);
				imagetext_set_text(UI_WIDGET_RICEWORK_ArtText1, (const char*)buff);
			}
		}
	}
}

/**
 * @brief 按钮点击事件回调接口
 * @param button   按钮控件指针
 * @param type     触摸事件类型
 */
void ui_ricework_on_button_touch_event(button_t *button, touch_type_e type) {
	if(type == E_TOUCH_DOWN) {
		if(button == UI_WIDGET_RICEWORK_Button1) {
			printf("RICEWORK_Button1 down\n");
		} else if(button == UI_WIDGET_RICEWORK_Button2) {
			printf("RICEWORK_Button2 down\n");
			time = 60;
		} else if(button == UI_WIDGET_RICEWORK_Button3) {
			printf("RICEWORK_Button3 down\n");
			if(star_flag == 0) star_flag = 1;
			else star_flag = 0;
		}	
	} 
}

/**
 * @brief 进度条回调接口
 * @param progress  进度条控件指针
 * @param val       进度值
 */
void ui_ricework_on_progress_changed(progress_t *progress, uint16_t val) {

}

/**
 * @brief 动画播放结束回调接口
 * @param animation  动画控件指针
 */
void ui_ricework_on_animation_play_end(animation_t *animation) {

}
