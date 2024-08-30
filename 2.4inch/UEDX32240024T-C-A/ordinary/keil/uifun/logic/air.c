#include "logic/air.h"
#include "widget/imagetext.h"

static uint8_t num[5] = {12,16,20,22,24};

void ui_air_on_page_open(uint8_t page) {	
	//�򿪽�������¸�ֵ
	 num[0] = 12;
	 num[1] = 16;
	 num[2] = 20;
	 num[3] = 22;
	 num[4] = 24;
}

/**
 * @brief ��ʱ���ص��ӿ�
 * @param millisecond   ��ʱ�����ڣ���λ ms
 * @param count  �ۼƴ���
 */
void ui_air_on_timer(uint32_t millisecond, uint32_t count) {
	char buff[5];
	//ÿ500ms�仯��ֵ, 500/10 = 50
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
 * @brief ��ť����¼��ص��ӿ�
 * @param button   ��ť�ؼ�ָ��
 * @param type     �����¼�����
 */
void ui_air_on_button_touch_event(button_t *button, touch_type_e type) {
	if(type == E_TOUCH_DOWN) {
		if(button == UI_WIDGET_AIR_Button1) {
			printf("AIR_Button1 down\n");
		} 
	} 
}

/**
 * @brief �������ص��ӿ�
 * @param progress  �������ؼ�ָ��
 * @param val       ����ֵ
 */
void ui_air_on_progress_changed(progress_t *progress, uint16_t val) {
	if(progress == UI_WIDGET_AIR_ProgressBar1) {
		printf("AIR_ProgressBar1:%d\n",val);
	}
}

/**
 * @brief �������Ž����ص��ӿ�
 * @param animation  �����ؼ�ָ��
 */
void ui_air_on_animation_play_end(animation_t *animation) {

}

