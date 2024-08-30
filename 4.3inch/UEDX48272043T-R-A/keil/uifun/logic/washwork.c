#include "logic/washwork.h"
#include "ext_flythings/draw_point.h"

#if USE_DRAW_POINT
//#define DRAW_WAVE	//������
#endif

#ifdef DRAW_WAVE
const uint8_t wave_data[100] = {
	5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
	20,70,100,100,100,100,100,100,100,100,
	100,100,97,94,96,89,80,75,70,67,
	63,50,34,12,12,34,56,78,77,76,
	75,74,73,72,71,70,70,70,70,70,
	70,70,70,70,70,70,70,70,70,70,
	70,70,70,70,70,70,70,70,70,70,
	70,70,70,70,70,70,70,70,70,70,
	70,70,70,70,70,70,70,70,70,70,
	70,70,70,70,70,70,70,70,70,70
};
static uint16_t num = 0;
#endif


void ui_washwork_on_page_open(uint8_t page) {
#ifdef DRAW_WAVE
	num = 0;
#endif
}

/**
 * @brief ��ʱ���ص��ӿ�
 * @param millisecond   ��ʱ�����ڣ���λ ms
 * @param count  �ۼƴ���
 */
void ui_washwork_on_timer(uint32_t millisecond, uint32_t count) {
#ifdef DRAW_WAVE
	if(count%10 == 0) {
		if(num%100 == 0) {
			num = 0;
			LCD_Fill(240,110,470,260,0xFFFF);
			LCD_Fill(240,150,470,151,0x001F);
			LCD_Fill(240,200,470,201,0x001F);
			LCD_Fill(240,250,470,251,0x001F);
		}
		num++;
		wave_drawpoint(240, 260, (uint8_t*)wave_data, num);
	}
#endif	
	
}

/**
 * @brief ��ť����¼��ص��ӿ�
 * @param button   ��ť�ؼ�ָ��
 * @param type     �����¼�����
 */
void ui_washwork_on_button_touch_event(button_t *button, touch_type_e type) {
	if(type == E_TOUCH_DOWN) {
		if(button == UI_WIDGET_WASHWORK_Button1) {
			printf("WASHWORK_Button1 down\n");
		}	
	} 
}

/**
 * @brief �������ص��ӿ�
 * @param progress  �������ؼ�ָ��
 * @param val       ����ֵ
 */
void ui_washwork_on_progress_changed(progress_t *progress, uint16_t val) {

}

/**
 * @brief �������Ž����ص��ӿ�
 * @param animation  �����ؼ�ָ��
 */
void ui_washwork_on_animation_play_end(animation_t *animation) {
	if(animation == UI_WIDGET_WASHWORK_Animation1) {
		//���ö���
		animation_reset(UI_WIDGET_WASHWORK_Animation1);
	}
}
