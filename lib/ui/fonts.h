#ifndef EEZ_LVGL_UI_FONTS_H
#define EEZ_LVGL_UI_FONTS_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern const lv_font_t ui_font_mono40;
extern const lv_font_t ui_font_mono100;
extern const lv_font_t ui_font_mono30;
extern const lv_font_t ui_font_mono_bold80;
extern const lv_font_t ui_font_digits_font_small;
extern const lv_font_t ui_font_mono_bold100;
extern const lv_font_t ui_font_mono_bold20;
extern const lv_font_t ui_font_mono_light30;

#ifndef EXT_FONT_DESC_T
#define EXT_FONT_DESC_T
typedef struct _ext_font_desc_t {
    const char *name;
    const void *font_ptr;
} ext_font_desc_t;
#endif

extern ext_font_desc_t fonts[];

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_FONTS_H*/