#include "logic/air.h"
#include "widget/imagetext.h"

static uint8_t num[5] = {12,16,20,22,24};

void ui_air_on_page_open(uint8_t page) {	
	//打开界面后重新赋值
	 num[0] = 12;
	 num[1] = 16;
	 num[2] = 20;
	 num[3] = 22;
	 num[4] = 24;
}

/**
 * @brief 定时器回调接口
 * @param millisecond   定时器周期，单位 ms
 * @param count  累计次数
 */
void ui_air_on_timer(uint32_t millisecond, uint32_t count) {
	char buff[5];
	//每500ms变化数值, 500/10 = 50
	if(count%50 == 0) {
		num[0] += 1;
		num[1] += 1;
		num[2] += 2;
		num[3] += 3;
		num[4] += 3;

		sprintf(buff,"%02d",(num[0]%30));
		imagetext_set_text(UI_WIDGET_AIR_ArtText1, (const char*)buff);

		sprintf(buff,"%02d",(num[1]%40));
		imagetext_set_text(UI_WIDGET_AIR_ArtText2, (const char*)buff);

		sprintf(buff,"%02d",(num[2]%60));
		imagetext_set_text(UI_WIDGET_AIR_ArtText3, (const char*)buff);

		sprintf(buff,"%02d",(num[3]%60));
		imagetext_set_text(UI_WIDGET_AIR_ArtText4, (const char*)buff);

		sprintf(buff,"%02d",(num[4]%90));
		imagetext_set_text(UI_WIDGET_AIR_ArtText5, (const char*)buff);
	}
}

/**
 * @brief 按钮点击事件回调接口
 * @param button   按钮控件指针
 * @param type     触摸事件类型
 */
void ui_air_on_button_touch_event(button_t *button, touch_type_e type) {
	if(type == E_TOUCH_DOWN) {
		if(button == UI_WIDGET_AIR_Button1) {
			printf("AIR_Button1 down\n");
		} 
	} 
}

/**
 * @brief 进度条回调接口
 * @param progress  进度条控件指针
 * @param val       进度值
 */
void ui_air_on_progress_changed(progress_t *progress, uint16_t val) {
	if(progress == UI_WIDGET_AIR_ProgressBar1) {
		printf("AIR_ProgressBar1:%d\n",val);
	}
}

/**
 * @brief 动画播放结束回调接口
 * @param animation  动画控件指针
 */
void ui_air_on_animation_play_end(animation_t *animation) {

}

