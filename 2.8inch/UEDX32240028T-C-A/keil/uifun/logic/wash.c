#include "logic/wash.h"

void ui_wash_on_page_open(uint8_t page) {

}

/**
 * @brief ��ʱ���ص��ӿ�
 * @param millisecond   ��ʱ�����ڣ���λ ms
 * @param count  �ۼƴ���
 */
void ui_wash_on_timer(uint32_t millisecond, uint32_t count) {

}

/**
 * @brief ��ť����¼��ص��ӿ�
 * @param button   ��ť�ؼ�ָ��
 * @param type     �����¼�����
 */
void ui_wash_on_button_touch_event(button_t *button, touch_type_e type) {
	if(type == E_TOUCH_DOWN) {
		if(button == UI_WIDGET_WASH_Button1) {
			printf("WASH_Button1 down\n");
		} else if(button == UI_WIDGET_WASH_Button2) {
			printf("WASH_Button2 down\n");
		}	
	} 
}

/**
 * @brief �������ص��ӿ�
 * @param progress  �������ؼ�ָ��
 * @param val       ����ֵ
 */
void ui_wash_on_progress_changed(progress_t *progress, uint16_t val) {

}

/**
 * @brief �������Ž����ص��ӿ�
 * @param animation  �����ؼ�ָ��
 */
void ui_wash_on_animation_play_end(animation_t *animation) {

}
