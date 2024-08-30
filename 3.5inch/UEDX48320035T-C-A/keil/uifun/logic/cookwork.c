#include "logic/cookwork.h"

static uint8_t retime = 60;
static uint8_t sta_sign = 1;
void ui_cookwork_on_page_open(uint8_t page) {
	//�򿪽�������¸�ֵ
	retime = 60;
}

/**
 * @brief ��ʱ���ص��ӿ�
 * @param millisecond   ��ʱ�����ڣ���λ ms
 * @param count  �ۼƴ���
 */
void ui_cookwork_on_timer(uint32_t millisecond, uint32_t count) {
	uint16_t val;
	char buff[5];
	//ÿ500ms�仯��ֵ,500/10 = 50
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
 * @brief ��ť����¼��ص��ӿ�
 * @param button   ��ť�ؼ�ָ��
 * @param type     �����¼�����
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
 * @brief �������ص��ӿ�
 * @param progress  �������ؼ�ָ��
 * @param val       ����ֵ
 */
void ui_cookwork_on_progress_changed(progress_t *progress, uint16_t val) {
//	if(progress == UI_WIDGET_COOKWORK_ProgressBar1) {
//		printf("COOKWORK_ProgressBar1:%d\n",val);
//	}
}

/**
 * @brief �������Ž����ص��ӿ�
 * @param animation  �����ؼ�ָ��
 */
void ui_cookwork_on_animation_play_end(animation_t *animation) {
	
}
