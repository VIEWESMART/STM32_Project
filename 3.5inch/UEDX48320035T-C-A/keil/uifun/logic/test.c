#include "logic/test.h"
#include "other_app.h"
#include "ui_res_image.h"

PAGE_ROTARY_INFO test_mode = {
	.ValRan = {
		.Min = 1,
		.Max = UI_RES_IMAGE_TEST_15 - UI_RES_IMAGE_TEST_01 + 1
	},
	.CurVal = 1
};

static void UserProcKey(S_INPUT_KEY *skey);
void ui_test_on_page_open(uint8_t page) {
	//加载按键处理函数
	LoadKeyCallbackFunc(UserProcKey);
	user_draw_imagetext_value(UI_WIDGET_TEST_ArtText1, test_mode.CurVal);
}

/**
 * @brief 定时器回调接口
 * @param millisecond   定时器周期，单位 ms
 * @param count  累计次数
 */
void ui_test_on_timer(uint32_t millisecond, uint32_t count) {

}

/**
 * @brief 按钮点击事件回调接口
 * @param button   按钮控件指针
 * @param type     触摸事件类型
 */
void ui_test_on_button_touch_event(button_t *button, touch_type_e type) {

}

/**
 * @brief 进度条回调接口
 * @param progress  进度条控件指针
 * @param val       进度值
 */
void ui_test_on_progress_changed(progress_t *progress, uint16_t val) {

}

/**
 * @brief 动画播放结束回调接口
 * @param animation  动画控件指针
 */
void ui_test_on_animation_play_end(animation_t *animation) {

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
			test_mode.CurVal++;
			if(test_mode.CurVal > (test_mode.ValRan.Max)) {
				test_mode.CurVal = test_mode.ValRan.Min;
			}
			user_draw_imagetext_value(UI_WIDGET_TEST_ArtText1, test_mode.CurVal);

			return;
		}
		else if(skey->keystatus == KEYST_KEEP_2S) {
			last_state = KEYST_KEEP_2S;
			return;
		} 
	}
}

