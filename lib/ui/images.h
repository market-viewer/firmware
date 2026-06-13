#ifndef EEZ_LVGL_UI_IMAGES_H
#define EEZ_LVGL_UI_IMAGES_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_img_dsc_t img_power_icon;
extern const lv_img_dsc_t img_reboot_icon;
extern const lv_img_dsc_t img_brightness_icon;
extern const lv_img_dsc_t img_volume_icon;
extern const lv_img_dsc_t img_backlight_icon;
extern const lv_img_dsc_t img_screen_icon;
extern const lv_img_dsc_t img_rotate_icon;
extern const lv_img_dsc_t img_wifi_icon;
extern const lv_img_dsc_t img_return_icon;
extern const lv_img_dsc_t img_config_icon;
extern const lv_img_dsc_t img_reset_icon;
extern const lv_img_dsc_t img_check_icon;
extern const lv_img_dsc_t img_refresh_icon;
extern const lv_img_dsc_t img_play_icon;
extern const lv_img_dsc_t img_pause_icon;
extern const lv_img_dsc_t img_timer_icon;
extern const lv_img_dsc_t img_clock_gauge;
extern const lv_img_dsc_t img_clock_needle_big;
extern const lv_img_dsc_t img_clock_needle_small;
extern const lv_img_dsc_t img_blue_gradient;
extern const lv_img_dsc_t img_background_red;
extern const lv_img_dsc_t img_crypto_icon;
extern const lv_img_dsc_t img_stock_icon;
extern const lv_img_dsc_t img_background_green;
extern const lv_img_dsc_t img_logo_big;

#ifndef EXT_IMG_DESC_T
#define EXT_IMG_DESC_T
typedef struct _ext_img_desc_t {
    const char *name;
    const lv_img_dsc_t *img_dsc;
} ext_img_desc_t;
#endif

extern const ext_img_desc_t images[25];

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_IMAGES_H*/