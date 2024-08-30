#include "context/guicontext.h"

#include "logic/menu.h"

/**
 * @brief ��ʱ���ص��ӿ�
 * @param millisecond   ��ʱ�����ڣ���λ ms
 * @param count  �ۼƴ���
 */
void on_timer(uint32_t millisecond, uint32_t count) {
  typedef void (*Callback)(uint32_t millisecond, uint32_t count);
  const Callback callbacks[] = {
    ui_menu_on_timer
  };
  if(gui_context_get_current_page() < sizeof(callbacks)/sizeof(Callback)) {
    (callbacks[gui_context_get_current_page()])(millisecond, count);
  }
}

/**
 * @brief ҳ��򿪻ص��ӿ�
 * @param page   ҳ��ID
 */
void on_page_open(uint8_t page) {
  typedef void (*Callback)(uint8_t page);
  const Callback callbacks[] = {
    ui_menu_on_page_open
  };
  if(gui_context_get_current_page() < sizeof(callbacks)/sizeof(Callback)) {
    (callbacks[page])(page);
  }
}

/**
 * @brief ��ť����¼��ص��ӿ�
 * @param button   ��ť�ؼ�ָ��
 * @param type     �����¼�����
 */
void on_button_touch_event(button_t *button, touch_type_e type) {
  typedef void (*Callback)(button_t *button, touch_type_e type);
  const Callback callbacks[] = {
    ui_menu_on_button_touch_event
  };
  if(gui_context_get_current_page() < sizeof(callbacks)/sizeof(Callback)) {
    (callbacks[gui_context_get_current_page()])(button, type);
  }
}

/**
 * @brief �������ص��ӿ�
 * @param progress  �������ؼ�ָ��
 * @param val       ����ֵ
 */
void on_progress_changed(progress_t *progress, uint16_t val) {
  typedef void (*Callback)(progress_t *progress, uint16_t val);
  const Callback callbacks[] = {
    ui_menu_on_progress_changed
  };
  if(gui_context_get_current_page() < sizeof(callbacks)/sizeof(Callback)) {
    (callbacks[gui_context_get_current_page()])(progress, val);
  }
}

/**
 * @brief �������Ž����ص��ӿ�
 * @param animation  �����ؼ�ָ��
 */
void on_animation_play_end(animation_t *animation) {
  typedef void (*Callback)(animation_t *animation);
  const Callback callbacks[] = {
    ui_menu_on_animation_play_end
  };
  if(gui_context_get_current_page() < sizeof(callbacks)/sizeof(Callback)) {
    (callbacks[gui_context_get_current_page()])(animation);
  }
}
