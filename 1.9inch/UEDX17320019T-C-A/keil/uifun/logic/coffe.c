#include "logic/coffe.h"

static uint8_t tempe = 50;

void ui_coffe_on_page_open(uint8_t page) {
	//打开界面后重新赋值
	tempe = 50;
}

/**
 * @brief 定时器回调接口
 * @param millisecond   定时器周期，单位 ms
 * @param count  累计次数
 */
void ui_coffe_on_timer(uint32_t millisecond, uint32_t count) {
	char buff[5];
	//每1000ms变化数值, 1000/10 = 100
	if(count%100 == 0) {
		tempe++;
		if(tempe > 100) tempe = 50;
		if(tempe == 100)	sprintf(buff,"%3d",tempe);
		if(tempe < 100){
			buff[0] = ' ';
			sprintf(buff+1,"%2d",tempe);
		}
		imagetext_set_text(UI_WIDGET_COFFE_ArtText2, (const char*)buff);
		progress_set_value(UI_WIDGET_COFFE_ProgressBar2, tempe);
	}
}

/**
 * @brief 按钮点击事件回调接口
 * @param button   按钮控件指针
 * @param type     触摸事件类型
 */
void ui_coffe_on_button_touch_event(button_t *button, touch_type_e type) {
	if(type == E_TOUCH_DOWN) {
		if(button == UI_WIDGET_COFFE_Button1) {
			printf("COFFE_Button1 down\n");
		} else if(button == UI_WIDGET_COFFE_Button2) {
			printf("COFFE_Button2 down\n");
		} else if(button == UI_WIDGET_COFFE_Button3) {
			printf("COFFE_Button3 down\n");
		} else if(button == UI_WIDGET_COFFE_Button4) {
			printf("COFFE_Button4 down\n");
		}	
	} 
}

/**
 * @brief 进度条回调接口
 * @param progress  进度条控件指针
 * @param val       进度值
 */
void ui_coffe_on_progress_changed(progress_t *progress, uint16_t val) {
	char buff[5];
	if(progress == UI_WIDGET_COFFE_ProgressBar1) {
//		sprintf(buff,"%3d",val);
		
		if(tempe == 100)	sprintf(buff,"%3d",val);
		if(tempe < 100){
			buff[0] = ' ';
			sprintf(buff+1,"%2d",val);
		}
		imagetext_set_text(UI_WIDGET_COFFE_ArtText1, (const char*)buff);
	}
}

/**
 * @brief 动画播放结束回调接口
 * @param animation  动画控件指针
 */
void ui_coffe_on_animation_play_end(animation_t *animation) {

}

