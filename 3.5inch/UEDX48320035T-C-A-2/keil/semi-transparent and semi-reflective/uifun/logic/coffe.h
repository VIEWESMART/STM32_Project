#ifndef _LOGIC_COFFE_H_
#define _LOGIC_COFFE_H_

#include "context/guicontext.h"

#define UI_WIDGET_COFFE_Button1              ((button_t*)gui_context_find_widget(2))
#define UI_WIDGET_COFFE_Button2              ((button_t*)gui_context_find_widget(3))
#define UI_WIDGET_COFFE_Button3              ((button_t*)gui_context_find_widget(6))
#define UI_WIDGET_COFFE_Button4              ((button_t*)gui_context_find_widget(7))
#define UI_WIDGET_COFFE_ArtText1             ((imagetext_t*)gui_context_find_widget(8))
#define UI_WIDGET_COFFE_ArtText2             ((imagetext_t*)gui_context_find_widget(9))
#define UI_WIDGET_COFFE_ProgressBar1         ((progress_t*)gui_context_find_widget(4))
#define UI_WIDGET_COFFE_ProgressBar2         ((progress_t*)gui_context_find_widget(5))

void ui_coffe_on_page_open(uint8_t page);

/**
 * @brief ��ʱ���ص��ӿ�
 * @param time   ��ʱ�����ڣ���λ ms
 * @param count  �ۼƴ���
 */
void ui_coffe_on_timer(uint32_t millisecond, uint32_t count);

/**
 * @brief ��ť����¼��ص��ӿ�
 * @param button   ��ť�ؼ�ָ��
 * @param type     �����¼�����
 */
void ui_coffe_on_button_touch_event(button_t *button, touch_type_e type);

/**
 * @brief �������ص��ӿ�
 * @param progress  �������ؼ�ָ��
 * @param val       ����ֵ
 */
void ui_coffe_on_progress_changed(progress_t *progress, uint16_t val);

/**
 * @brief �������Ž����ص��ӿ�
 * @param animation  �����ؼ�ָ��
 */
void ui_coffe_on_animation_play_end(animation_t *animation);

#endif /*_LOGIC_COFFE_H_*/
