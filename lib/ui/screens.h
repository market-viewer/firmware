#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Screens

enum ScreensEnum {
    _SCREEN_ID_FIRST = 1,
    SCREEN_ID_MARKET_DATA_SETTING_SCREEN = 1,
    SCREEN_ID_TIMER_SCREEN = 2,
    SCREEN_ID_HOME_SCREEN = 3,
    SCREEN_ID_BRIGHTNESS_SCREEN = 4,
    SCREEN_ID_VOLUME_SCREEN = 5,
    SCREEN_ID_WIFI_SCREEN = 6,
    SCREEN_ID_SCREENS_SCREEN = 7,
    SCREEN_ID_CLOCK_SCREEN = 8,
    SCREEN_ID_DIGITAL_CLOCK_SCREEN = 9,
    SCREEN_ID_CRYPTO_SCREEN = 10,
    SCREEN_ID_STOCK_SCREEN = 11,
    _SCREEN_ID_LAST = 11
};

typedef struct _objects_t {
    lv_obj_t *market_data_setting_screen;
    lv_obj_t *timer_screen;
    lv_obj_t *home_screen;
    lv_obj_t *brightness_screen;
    lv_obj_t *volume_screen;
    lv_obj_t *wifi_screen;
    lv_obj_t *screens_screen;
    lv_obj_t *clock_screen;
    lv_obj_t *digital_clock_screen;
    lv_obj_t *crypto_screen;
    lv_obj_t *stock_screen;
    lv_obj_t *market_data_setting_main_panel;
    lv_obj_t *simple_dispaly_cont;
    lv_obj_t *simple_display_label;
    lv_obj_t *simple_display_switch;
    lv_obj_t *display_graph_cont;
    lv_obj_t *display_chart_label;
    lv_obj_t *display_graph_switch;
    lv_obj_t *candle_chart_cont;
    lv_obj_t *candle_chart_label;
    lv_obj_t *candle_chart_switch;
    lv_obj_t *timer_description_selector_label;
    lv_obj_t *timer_rollers_panel;
    lv_obj_t *hour_roller;
    lv_obj_t *minute_roller;
    lv_obj_t *second_roller;
    lv_obj_t *timer_buttons_panel;
    lv_obj_t *timer_reset_button;
    lv_obj_t *timer_play_pause_button;
    lv_obj_t *timer_icon;
    lv_obj_t *timer_name_label;
    lv_obj_t *timer_arc;
    lv_obj_t *timer_time_label;
    lv_obj_t *obj0;
    lv_obj_t *home_container_main;
    lv_obj_t *power_icons_cont;
    lv_obj_t *trun_off_button;
    lv_obj_t *restart_button;
    lv_obj_t *home_row_one;
    lv_obj_t *brightness_button;
    lv_obj_t *volume_button;
    lv_obj_t *backlight_button;
    lv_obj_t *home_row_two;
    lv_obj_t *screens_button;
    lv_obj_t *rotate_button;
    lv_obj_t *wifi_button;
    lv_obj_t *brightness_arc;
    lv_obj_t *birghtness_label;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *obj2__back_button;
    lv_obj_t *brightness_value_label;
    lv_obj_t *volume_arc;
    lv_obj_t *volume_label;
    lv_obj_t *obj3;
    lv_obj_t *volume_value_label;
    lv_obj_t *obj4;
    lv_obj_t *obj4__back_button;
    lv_obj_t *wifi_label;
    lv_obj_t *obj5;
    lv_obj_t *obj5__back_button;
    lv_obj_t *main_container_wifi;
    lv_obj_t *connection_info_container;
    lv_obj_t *wifi_connection_round_indicator;
    lv_obj_t *connection_label;
    lv_obj_t *connected_wifi_container;
    lv_obj_t *wifi_name_container;
    lv_obj_t *connected_wifi_ssid_label;
    lv_obj_t *obj6;
    lv_obj_t *backend_url_label;
    lv_obj_t *wifi_containers_buttons;
    lv_obj_t *wifi_config_button;
    lv_obj_t *wifi_reset_button;
    lv_obj_t *overlay_wifi_container;
    lv_obj_t *overlay_wifi_label;
    lv_obj_t *overlay_wifi_ssid_label;
    lv_obj_t *overlay_wifi_ssid_label_value;
    lv_obj_t *overlay_wifi_ssid_label_3;
    lv_obj_t *overlay_wifi_pwd_label_value;
    lv_obj_t *screens_label;
    lv_obj_t *obj7;
    lv_obj_t *obj7__back_button;
    lv_obj_t *screens_refetch_button;
    lv_obj_t *screen_not_fetched_label;
    lv_obj_t *screens_list_panel;
    lv_obj_t *screen_list_item_label_example;
    lv_obj_t *clock_gauge_image;
    lv_obj_t *time_label;
    lv_obj_t *timezone_label;
    lv_obj_t *clock_needle_second;
    lv_obj_t *clock_needle_minute;
    lv_obj_t *digital_time_label;
    lv_obj_t *digital_date_label;
    lv_obj_t *digital_date_label_1;
    lv_obj_t *crypto_graph_panel;
    lv_obj_t *crypto_ath_arc;
    lv_obj_t *crypto_price_label;
    lv_obj_t *crypto_price_change_label;
    lv_obj_t *crypto_ath_label;
    lv_obj_t *crypto_ath_change_label;
    lv_obj_t *crypto_zero_label;
    lv_obj_t *crypto_icon;
    lv_obj_t *crypto_asset_currency_label;
    lv_obj_t *crypto_time_frame_label;
    lv_obj_t *stock_graph_panel;
    lv_obj_t *stock_price_label;
    lv_obj_t *stock_price_change_label;
    lv_obj_t *stock_icon;
    lv_obj_t *stock_symbol_currency_label;
    lv_obj_t *stock_time_frame_label;
    lv_obj_t *stock_name_label;
    lv_obj_t *stock_market_open_cont;
    lv_obj_t *stock_market_open_icon;
    lv_obj_t *stock_market_open_label;
} objects_t;

extern objects_t objects;

void create_screen_market_data_setting_screen();
void tick_screen_market_data_setting_screen();

void create_screen_timer_screen();
void tick_screen_timer_screen();

void create_screen_home_screen();
void tick_screen_home_screen();

void create_screen_brightness_screen();
void tick_screen_brightness_screen();

void create_screen_volume_screen();
void tick_screen_volume_screen();

void create_screen_wifi_screen();
void tick_screen_wifi_screen();

void create_screen_screens_screen();
void tick_screen_screens_screen();

void create_screen_clock_screen();
void tick_screen_clock_screen();

void create_screen_digital_clock_screen();
void tick_screen_digital_clock_screen();

void create_screen_crypto_screen();
void tick_screen_crypto_screen();

void create_screen_stock_screen();
void tick_screen_stock_screen();

void create_user_widget_back_button(lv_obj_t *parent_obj, int startWidgetIndex);
void tick_user_widget_back_button(int startWidgetIndex);

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();

// Color themes

enum Themes {
    THEME_ID_DARK,
};
enum Colors {
    COLOR_ID_BLACK,
    COLOR_ID_GRAY_DARK,
    COLOR_ID_RED_DARK,
    COLOR_ID_GRAY_BRIGHT,
    COLOR_ID_YELLOW_DARK,
    COLOR_ID_YELLOW_BRIGHT,
    COLOR_ID_BLUE_DARK,
    COLOR_ID_GREEN,
    COLOR_ID_GRAY_LIGHTEST,
    COLOR_ID_RED_DARKEST,
    COLOR_ID_RED_PRICE,
    COLOR_ID_WHITE_DARK,
};
void change_color_theme(uint32_t themeIndex);
extern uint32_t theme_colors[1][12];
extern uint32_t active_theme_index;

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/