#ifndef _LOGIC_MENU_H_
#define _LOGIC_MENU_H_

#include "context/guicontext.h"

#define UI_WIDGET_MENU_Animation1           ((animation_t*)gui_context_find_widget(2))

void ui_menu_on_page_open(uint8_t page);

/**
 * @brief ��ʱ���ص��ӿ�
 * @param time   ��ʱ�����ڣ���λ ms
 * @param count  �ۼƴ���
 */
void ui_menu_on_timer(uint32_t millisecond, uint32_t count);

/**
 * @brief ��ť����¼��ص��ӿ�
 * @param button   ��ť�ؼ�ָ��
 * @param type     �����¼�����
 */
void ui_menu_on_button_touch_event(button_t *button, touch_type_e type);

/**
 * @brief �������ص��ӿ�
 * @param progress  �������ؼ�ָ��
 * @param val       ����ֵ
 */
void ui_menu_on_progress_changed(progress_t *progress, uint16_t val);

/**
 * @brief �������Ž����ص��ӿ�
 * @param animation  �����ؼ�ָ��
 */
void ui_menu_on_animation_play_end(animation_t *animation);

#endif /*_LOGIC_MENU_H_*/
