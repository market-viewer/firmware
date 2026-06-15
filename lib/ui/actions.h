#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_restart_device(lv_event_t * e);
extern void action_nav_to_brightness_scr(lv_event_t * e);
extern void action_nav_to_volume_scr(lv_event_t * e);
extern void action_turn_off_backlight(lv_event_t * e);
extern void action_nav_to_screens_scr(lv_event_t * e);
extern void action_toggle_rotation_settings(lv_event_t * e);
extern void action_nav_to_wifi_scr(lv_event_t * e);
extern void action_nav_to_home_scr(lv_event_t * e);
extern void action_set_brightness_from_arc(lv_event_t * e);
extern void action_open_wifi_portal(lv_event_t * e);
extern void action_reset_wifi_config(lv_event_t * e);
extern void action_timer_reset_pressed(lv_event_t * e);
extern void action_timer_start_pressed(lv_event_t * e);
extern void action_simple_display_switch_toggle(lv_event_t * e);
extern void action_display_graph_switch_toggle(lv_event_t * e);
extern void action_candle_chart_switch_toggle(lv_event_t * e);
extern void action_save_volume(lv_event_t * e);
extern void action_save_brightness(lv_event_t * e);
extern void action_update_wifi_screen_status_on_load(lv_event_t * e);
extern void action_handle_screens_screen_load(lv_event_t * e);
extern void action_set_buttons_status_home_screen(lv_event_t * e);
extern void action_screen_change_swipe(lv_event_t * e);
extern void action_finance_screen_gesture(lv_event_t * e);
extern void action_market_data_setting_screen_load(lv_event_t * e);
extern void action_exit_market_data_setting(lv_event_t * e);
extern void action_turn_off_device(lv_event_t * e);
extern void action_toggle_rotation_settings(lv_event_t * e);
extern void action_set_volume_from_arc(lv_event_t * e);
extern void action_home_next_screen(lv_event_t * e);
extern void action_toggle_market_screen_setting(lv_event_t * e);
extern void action_refetch_screens(lv_event_t * e);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/