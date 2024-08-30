#include "logic/test2.h"
#include "other_app.h"
#include "ui_res_image.h"

PAGE_ROTARY_INFO test_mode2 = {
	.ValRan = {
		.Min = 1,
		.Max = UI_RES_IMAGE_TEST_15 - UI_RES_IMAGE_TEST_01 + 1
	},
	.CurVal = 1
};

static uint8_t ControlsSign = 0;

static void UserProcKey(S_INPUT_KEY *skey);
void ui_test2_on_page_open(uint8_t page) {
	//���ذ���������
	LoadKeyCallbackFunc(UserProcKey);
}

/**
 * @brief ��ʱ���ص��ӿ�
 * @param millisecond   ��ʱ�����ڣ���λ ms
 * @param count  �ۼƴ���
 */
void ui_test2_on_timer(uint32_t millisecond, uint32_t count) {
	if(count % 100 == 0){
		if(ControlsSign == 0){
			test_mode2.CurVal++;
			if(test_mode2.CurVal > (test_mode2.ValRan.Max)) {
				test_mode2.CurVal = test_mode2.ValRan.Min;
			}
			user_draw_imagetext_value(UI_WIDGET_TEST2_ArtText1, test_mode2.CurVal);
		}
	}
}

/**
 * @brief ��ť����¼��ص��ӿ�
 * @param button   ��ť�ؼ�ָ��
 * @param type     �����¼�����
 */
void ui_test2_on_button_touch_event(button_t *button, touch_type_e type) {

}

/**
 * @brief �������ص��ӿ�
 * @param progress  �������ؼ�ָ��
 * @param val       ����ֵ
 */
void ui_test2_on_progress_changed(progress_t *progress, uint16_t val) {

}

/**
 * @brief �������Ž����ص��ӿ�
 * @param animation  �����ؼ�ָ��
 */
void ui_test2_on_animation_play_end(animation_t *animation) {

}


static void UserProcKey(S_INPUT_KEY *skey) {
	static uint8_t last_state = KEYST_DOWN;
	
	//ȷ�ϰ�������Ļ���£�
	if(skey->keyvalue == KEY_SWKEY) {
		if(skey->keystatus == KEYST_DOWN) {
			last_state = KEYST_DOWN;	
			ControlsSign = 1;
			return;
		}
		else if(skey->keystatus == KEYST_UP) {
			if(last_state == KEYST_KEEP_2S) return;
			last_state = KEYST_UP;
			test_mode2.CurVal++;
			if(test_mode2.CurVal > (test_mode2.ValRan.Max)) {
				test_mode2.CurVal = test_mode2.ValRan.Min;
			}
			user_draw_imagetext_value(UI_WIDGET_TEST2_ArtText1, test_mode2.CurVal);

			return;
		}
		else if(skey->keystatus == KEYST_KEEP_2S) {
			last_state = KEYST_KEEP_2S;
			gui_context_open_page(UI_PAGE_MENU );
			return;
		} 
	}
}


