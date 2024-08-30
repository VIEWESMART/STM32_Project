#include "logic/menu.h"
#include "ext_flythings/switch_image.h"
#include "ui_res_image.h"

#include "other_app.h"

static uint8_t key_times = 0;
static uint8_t sign = 0;

static void UserProcKey(S_INPUT_KEY *skey);
void ui_menu_on_page_open(uint8_t page) {
	//加载按键处理函数
	LoadKeyCallbackFunc(UserProcKey);
}

/**
 * @brief 定时器回调接口
 * @param millisecond   定时器周期，单位 ms
 * @param count  累计次数
 */
void ui_menu_on_timer(uint32_t millisecond, uint32_t count) {
	static uint8_t buf = 0;
	//替换图片控件的图片
	if(count%100 == 0) {
		buf++;
		if(buf%2) {
			image_set_img(UI_WIDGET_MENU_Image2, UI_RES_IMAGE_YOUYANJI_IMAGES_YOUYAN22_22);
			image_set_img(UI_WIDGET_MENU_Image1, UI_RES_IMAGE_YOUYANJI_IMAGES_YOUYAN22_23);
			printf("UI_RES_IMAGE_YOUYANJI_IMAGES_YOUYAN22_22\n");
		} else {
			image_set_img(UI_WIDGET_MENU_Image2, UI_RES_IMAGE_YOUYANJI_IMAGES_YOUYAN22_23);
			image_set_img(UI_WIDGET_MENU_Image1, UI_RES_IMAGE_YOUYANJI_IMAGES_YOUYAN22_22);
			printf("UI_RES_IMAGE_YOUYANJI_IMAGES_YOUYAN22_23\n");
		}
	}
	if(key_times > 0){
		key_times--;
//		printf("==========key_times:%d============\n",key_times);
	}else
		sign = 0;
}

/**
 * @brief 按钮点击事件回调接口
 * @param button   按钮控件指针
 * @param type     触摸事件类型
 */
void ui_menu_on_button_touch_event(button_t *button, touch_type_e type) {

}

/**
 * @brief 进度条回调接口
 * @param progress  进度条控件指针
 * @param val       进度值
 */
void ui_menu_on_progress_changed(progress_t *progress, uint16_t val) {

}

/**
 * @brief 动画播放结束回调接口
 * @param animation  动画控件指针
 */
void ui_menu_on_animation_play_end(animation_t *animation) {

}


static void UserProcKey(S_INPUT_KEY *skey) {
	static uint8_t last_state = KEYST_DOWN;
	
	//确认按键（屏幕按下）
	if(skey->keyvalue == KEY_SWKEY) {
		if(skey->keystatus == KEYST_DOWN) {
			last_state = KEYST_DOWN;
			return;
		}
		else if(skey->keystatus == KEYST_UP) {
			if(last_state == KEYST_KEEP_2S) return;
			last_state = KEYST_UP;
			
			if(sign == 0){
				sign = 1; 
				key_times = 50;
			}else
				sign = 0;
			
			if(sign == 0 && key_times > 0){
				gui_context_open_page(UI_PAGE_TEST2);
			}
			return;
		}
		else if(skey->keystatus == KEYST_KEEP_2S) {
			last_state = KEYST_KEEP_2S;
			gui_context_open_page(UI_PAGE_TEST);
			return;
		} 
	}
}

