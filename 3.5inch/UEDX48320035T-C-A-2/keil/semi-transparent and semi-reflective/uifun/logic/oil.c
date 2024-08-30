#include "logic/oil.h"

typedef struct {
	uint8_t hour;
	uint8_t min;
	uint8_t second;
	uint8_t set_hour;
	uint8_t set_min;
}TIME_STRUCT;
static TIME_STRUCT time_struct = {
	.hour = 12,
	.min = 0,
	.second = 0,
	.set_hour = 12,
	.set_min = 12,
};


void ui_oil_on_page_open(uint8_t page) {
	//打开界面后重新赋值
	time_struct.hour = 12;
	time_struct.min = 0;
	time_struct.second = 0;
	time_struct.set_hour = 12;
	time_struct.set_min = 12;
}

/**
 * @brief 定时器回调接口
 * @param millisecond   定时器周期，单位 ms
 * @param count  累计次数
 */
void ui_oil_on_timer(uint32_t millisecond, uint32_t count) {	
	static uint8_t last_hour = 12;
	static uint8_t last_min = 0;
	
	char buff[6];
	//每1000ms second加1, 1000/10 = 100
	if(count%100 == 0) {
		time_struct.second++;
		if(time_struct.second >= 60) {
			time_struct.second = 0;
			time_struct.min++;
		}
		if(time_struct.min >= 60) {
			time_struct.min = 0;
			time_struct.hour++;
		}
		if(time_struct.hour >= 24) {
			time_struct.hour = 0;
		}
		if((last_hour != time_struct.hour) || (last_min != time_struct.min)) {
			last_hour = time_struct.hour;
			last_min = time_struct.min;
			sprintf(buff,"%02d:%02d", time_struct.hour,time_struct.min);
			imagetext_set_text(UI_WIDGET_OIL_ArtText1, (const char*)buff);
		}
	}
}

/**
 * @brief 按钮点击事件回调接口
 * @param button   按钮控件指针
 * @param type     触摸事件类型
 */
void ui_oil_on_button_touch_event(button_t *button, touch_type_e type) {
	char buff[5];
	if(type == E_TOUCH_DOWN) {
		printf("button->id:%d\n",button->id);
		//button->id可在对应头文件中查看
		switch(button->id) {
			//UI_WIDGET_OIL_Button1
			case 8: 
				printf("OIL_Button1 down\n");
				break;
			//UI_WIDGET_OIL_Button2 UI_WIDGET_OIL_Button3 UI_WIDGET_OIL_Button4 UI_WIDGET_OIL_Button5
			case 2: case 3:case 4: case 5:  
				printf("OIL_Button2-5 down\n");
				if(button->id == 4) { //UI_WIDGET_OIL_Button2
					if(time_struct.set_hour > 0) {
						time_struct.set_hour--;
						sprintf(buff,"%02d",time_struct.set_hour);
						imagetext_set_text(UI_WIDGET_OIL_ArtText2, (const char*)buff);
					}
				} else if(button->id == 3) { //UI_WIDGET_OIL_Button3
					if(time_struct.set_hour < 23) {
						time_struct.set_hour++;
						sprintf(buff,"%02d",time_struct.set_hour);
						imagetext_set_text(UI_WIDGET_OIL_ArtText2, (const char*)buff);
					}
				}
				if(button->id == 5) { //UI_WIDGET_OIL_Button4
					if(time_struct.set_min > 0) {
						time_struct.set_min--;
						sprintf(buff,"%02d",time_struct.set_min);
						imagetext_set_text(UI_WIDGET_OIL_ArtText4, (const char*)buff);
					}
				} else if(button->id == 2) { //UI_WIDGET_OIL_Button5
					if(time_struct.set_min < 59) {
						time_struct.set_min++;
						sprintf(buff,"%02d",time_struct.set_min);
						imagetext_set_text(UI_WIDGET_OIL_ArtText4, (const char*)buff);
					}
				}
				
//				time_struct.hour = time_struct.set_hour;
//				time_struct.min = time_struct.set_min;
				
				break;
			//UI_WIDGET_OIL_Button6 UI_WIDGET_OIL_Button7 UI_WIDGET_OIL_Button8 UI_WIDGET_OIL_Button9
			case 6: case 7: case 9: case 10: 
				printf("OIL_Button6-9 down\n");
				break;
			default :
				break;
		}
	}		
}

/**
 * @brief 进度条回调接口
 * @param progress  进度条控件指针
 * @param val       进度值
 */
void ui_oil_on_progress_changed(progress_t *progress, uint16_t val) {

}

/**
 * @brief 动画播放结束回调接口
 * @param animation  动画控件指针
 */
void ui_oil_on_animation_play_end(animation_t *animation) {

}
