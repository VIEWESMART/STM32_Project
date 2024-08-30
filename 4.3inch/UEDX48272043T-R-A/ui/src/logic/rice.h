#ifndef _LOGIC_RICE_H_
#define _LOGIC_RICE_H_

#include "context/guicontext.h"

#define UI_WIDGET_RICE_Button1              ((button_t*)gui_context_find_widget(2))
#define UI_WIDGET_RICE_Button2              ((button_t*)gui_context_find_widget(3))

void ui_rice_on_page_open(uint8_t page);

/**
 * @brief ��ʱ���ص��ӿ�
 * @param time   ��ʱ�����ڣ���λ ms
 * @param count  �ۼƴ���
 */
void ui_rice_on_timer(uint32_t millisecond, uint32_t count);

/**
 * @brief ��ť����¼��ص��ӿ�
 * @param button   ��ť�ؼ�ָ��
 * @param type     �����¼�����
 */
void ui_rice_on_button_touch_event(button_t *button, touch_type_e type);

/**
 * @brief �������ص��ӿ�
 * @param progress  �������ؼ�ָ��
 * @param val       ����ֵ
 */
void ui_rice_on_progress_changed(progress_t *progress, uint16_t val);

/**
 * @brief �������Ž����ص��ӿ�
 * @param animation  �����ؼ�ָ��
 */
void ui_rice_on_animation_play_end(animation_t *animation);

#endif /*_LOGIC_RICE_H_*/
