#ifndef EEZ_LVGL_UI_STYLES_H
#define EEZ_LVGL_UI_STYLES_H

#include <lvgl/lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

// Style: base_button
lv_style_t *get_style_base_button_MAIN_DEFAULT();
void add_style_base_button(lv_obj_t *obj);
void remove_style_base_button(lv_obj_t *obj);

// Style: bigArc
lv_style_t *get_style_big_arc_INDICATOR_DEFAULT();
lv_style_t *get_style_big_arc_KNOB_DEFAULT();
lv_style_t *get_style_big_arc_MAIN_DEFAULT();
void add_style_big_arc(lv_obj_t *obj);
void remove_style_big_arc(lv_obj_t *obj);

// Style: screenLabel
void add_style_screen_label(lv_obj_t *obj);
void remove_style_screen_label(lv_obj_t *obj);

#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_STYLES_H*/