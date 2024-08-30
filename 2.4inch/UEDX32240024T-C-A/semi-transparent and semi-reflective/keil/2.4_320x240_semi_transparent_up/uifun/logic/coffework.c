#include "logic/coffework.h"

static uint8_t img_id = 49;

void ui_coffework_on_page_open(uint8_t page) {
	char buff[2];
	buff[0] = img_id;
	buff[1] = '\0';
	imagetext_set_text(UI_WIDGET_COFFEWORK_ArtText2, &buff[0]);
}

/**
 * @brief ��ʱ���ص��ӿ�
 * @param millisecond   ��ʱ�����ڣ���λ ms
 * @param count  �ۼƴ���
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
 * @brief ��ť����¼��ص��ӿ�
 * @param button   ��ť�ؼ�ָ��
 * @param type     �����¼�����
 */
void ui_coffework_on_button_touch_event(button_t *button, touch_type_e type) {
	if(type == E_TOUCH_DOWN) {
		if(button == UI_WIDGET_COFFEWORK_Button1) {
			printf("COFFEWORK_Button1 down\n");
		}
	}
}

/**
 * @brief �������ص��ӿ�
 * @param progress  �������ؼ�ָ��
 * @param val       ����ֵ
 */
void ui_coffework_on_progress_changed(progress_t *progress, uint16_t val) {

}

/**
 * @brief �������Ž����ص��ӿ�
 * @param animation  �����ؼ�ָ��
 */
void ui_coffework_on_animation_play_end(animation_t *animation) {
	if(animation == UI_WIDGET_COFFEWORK_Animation1) {
		//���ö���
		animation_reset(UI_WIDGET_COFFEWORK_Animation1);
	}
}
