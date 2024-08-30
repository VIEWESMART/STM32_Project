#include "logic/ricework.h"

static uint8_t star_flag = 0;
static uint8_t time = 60;

void ui_ricework_on_page_open(uint8_t page) {
	//�򿪽�������¸�ֵ
	star_flag = 0;
	time = 60;
}

/**
 * @brief ��ʱ���ص��ӿ�
 * @param millisecond   ��ʱ�����ڣ���λ ms
 * @param count  �ۼƴ���
 */
void ui_ricework_on_timer(uint32_t millisecond, uint32_t count) {
	char buff[5];
	//ÿ1000ms�仯��ֵ, 1000/10 = 100
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
 * @brief ��ť����¼��ص��ӿ�
 * @param button   ��ť�ؼ�ָ��
 * @param type     �����¼�����
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
 * @brief �������ص��ӿ�
 * @param progress  �������ؼ�ָ��
 * @param val       ����ֵ
 */
void ui_ricework_on_progress_changed(progress_t *progress, uint16_t val) {

}

/**
 * @brief �������Ž����ص��ӿ�
 * @param animation  �����ؼ�ָ��
 */
void ui_ricework_on_animation_play_end(animation_t *animation) {

}
