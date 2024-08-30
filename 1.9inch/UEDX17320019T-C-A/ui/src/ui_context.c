#include "context/guicontext.h"

#include "logic/menu.h"
#include "logic/air.h"
#include "logic/coffe.h"
#include "logic/coffework.h"
#include "logic/cook.h"
#include "logic/cookwork.h"
#include "logic/oil.h"
#include "logic/rice.h"
#include "logic/ricework.h"
#include "logic/test.h"
#include "logic/wash.h"
#include "logic/wash2.h"
#include "logic/washwork.h"

/**
 * @brief 定时器回调接口
 * @param millisecond   定时器周期，单位 ms
 * @param count  累计次数
 */
void on_timer(uint32_t millisecond, uint32_t count) {
  typedef void (*Callback)(uint32_t millisecond, uint32_t count);
  const Callback callbacks[] = {
    ui_menu_on_timer,
    ui_air_on_timer,
    ui_coffe_on_timer,
    ui_coffework_on_timer,
    ui_cook_on_timer,
    ui_cookwork_on_timer,
    ui_oil_on_timer,
    ui_rice_on_timer,
    ui_ricework_on_timer,
    ui_test_on_timer,
    ui_wash_on_timer,
    ui_wash2_on_timer,
    ui_washwork_on_timer
  };
  if(gui_context_get_current_page() < sizeof(callbacks)/sizeof(Callback)) {
    (callbacks[gui_context_get_current_page()])(millisecond, count);
  }
}

/**
 * @brief 页面打开回调接口
 * @param page   页面ID
 */
void on_page_open(uint8_t page) {
  typedef void (*Callback)(uint8_t page);
  const Callback callbacks[] = {
    ui_menu_on_page_open,
    ui_air_on_page_open,
    ui_coffe_on_page_open,
    ui_coffework_on_page_open,
    ui_cook_on_page_open,
    ui_cookwork_on_page_open,
    ui_oil_on_page_open,
    ui_rice_on_page_open,
    ui_ricework_on_page_open,
    ui_test_on_page_open,
    ui_wash_on_page_open,
    ui_wash2_on_page_open,
    ui_washwork_on_page_open
  };
  if(gui_context_get_current_page() < sizeof(callbacks)/sizeof(Callback)) {
    (callbacks[page])(page);
  }
}

/**
 * @brief 按钮点击事件回调接口
 * @param button   按钮控件指针
 * @param type     触摸事件类型
 */
void on_button_touch_event(button_t *button, touch_type_e type) {
  typedef void (*Callback)(button_t *button, touch_type_e type);
  const Callback callbacks[] = {
    ui_menu_on_button_touch_event,
    ui_air_on_button_touch_event,
    ui_coffe_on_button_touch_event,
    ui_coffework_on_button_touch_event,
    ui_cook_on_button_touch_event,
    ui_cookwork_on_button_touch_event,
    ui_oil_on_button_touch_event,
    ui_rice_on_button_touch_event,
    ui_ricework_on_button_touch_event,
    ui_test_on_button_touch_event,
    ui_wash_on_button_touch_event,
    ui_wash2_on_button_touch_event,
    ui_washwork_on_button_touch_event
  };
  if(gui_context_get_current_page() < sizeof(callbacks)/sizeof(Callback)) {
    (callbacks[gui_context_get_current_page()])(button, type);
  }
}

/**
 * @brief 进度条回调接口
 * @param progress  进度条控件指针
 * @param val       进度值
 */
void on_progress_changed(progress_t *progress, uint16_t val) {
  typedef void (*Callback)(progress_t *progress, uint16_t val);
  const Callback callbacks[] = {
    ui_menu_on_progress_changed,
    ui_air_on_progress_changed,
    ui_coffe_on_progress_changed,
    ui_coffework_on_progress_changed,
    ui_cook_on_progress_changed,
    ui_cookwork_on_progress_changed,
    ui_oil_on_progress_changed,
    ui_rice_on_progress_changed,
    ui_ricework_on_progress_changed,
    ui_test_on_progress_changed,
    ui_wash_on_progress_changed,
    ui_wash2_on_progress_changed,
    ui_washwork_on_progress_changed
  };
  if(gui_context_get_current_page() < sizeof(callbacks)/sizeof(Callback)) {
    (callbacks[gui_context_get_current_page()])(progress, val);
  }
}

/**
 * @brief 动画播放结束回调接口
 * @param animation  动画控件指针
 */
void on_animation_play_end(animation_t *animation) {
  typedef void (*Callback)(animation_t *animation);
  const Callback callbacks[] = {
    ui_menu_on_animation_play_end,
    ui_air_on_animation_play_end,
    ui_coffe_on_animation_play_end,
    ui_coffework_on_animation_play_end,
    ui_cook_on_animation_play_end,
    ui_cookwork_on_animation_play_end,
    ui_oil_on_animation_play_end,
    ui_rice_on_animation_play_end,
    ui_ricework_on_animation_play_end,
    ui_test_on_animation_play_end,
    ui_wash_on_animation_play_end,
    ui_wash2_on_animation_play_end,
    ui_washwork_on_animation_play_end
  };
  if(gui_context_get_current_page() < sizeof(callbacks)/sizeof(Callback)) {
    (callbacks[gui_context_get_current_page()])(animation);
  }
}
