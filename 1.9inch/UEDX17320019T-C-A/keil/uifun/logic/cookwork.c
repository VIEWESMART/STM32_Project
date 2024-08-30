#include "logic/cookwork.h"

static uint8_t retime = 60;
static uint8_t sta_sign = 1;
void ui_cookwork_on_page_open(uint8_t page) {
	//打开界面后重新赋值
	retime = 60;
}

/**
 * @brief 定时器回调接口
 * @param millisecond   定时器周期，单位 ms
 * @param count  累计次数
 */
void ui_cookwork_on_timer(uint32_t millisecond, uint32_t count) {
	uint16_t val;
	char buff[5];
	//每500ms变化数值,500/10 = 50
	if(count%50 == 0) {
		if(sta_sign){
				if(retime > 0) retime -= 2;
				else retime = 60;
				sprintf(buff,"%02d",retime);
				imagetext_set_text(UI_WIDGET_COOKWORK_ArtText1, (const char*)buff);
				val = ((60-retime)*10)/6;
				progress_set_value(UI_WIDGET_COOKWORK_ProgressBar1, val);
		}
	}
}

/**
 * @brief 按钮点击事件回调接口
 * @param button   按钮控件指针
 * @param type     触摸事件类型
 */
void ui_cookwork_on_button_touch_event(button_t *button, touch_type_e type) {
	if(type == E_TOUCH_DOWN) {
		if(button == UI_WIDGET_COOKWORK_Button1) {
			printf("COOKWORK_Button1 down\n");
		} else if(button == UI_WIDGET_COOKWORK_Button2) {
			sta_sign = 0;
			printf("COOKWORK_Button2 down\n");
		} else if(button == UI_WIDGET_COOKWORK_Button3) {
			sta_sign = 1;
			printf("COOKWORK_Button3 down\n");
		}	
	} 
}

/**
 * @brief 进度条回调接口
 * @param progress  进度条控件指针
 * @param val       进度值
 */
void ui_cookwork_on_progress_changed(progress_t *progress, uint16_t val) {
//	if(progress == UI_WIDGET_COOKWORK_ProgressBar1) {
//		printf("COOKWORK_ProgressBar1:%d\n",val);
//	}
}

/**
 * @brief 动画播放结束回调接口
 * @param animation  动画控件指针
 */
void ui_cookwork_on_animation_play_end(animation_t *animation) {
	
}
