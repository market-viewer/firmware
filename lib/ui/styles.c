#include "styles.h"
#include "images.h"
#include "fonts.h"

#include "ui.h"
#include "screens.h"

//
// Style: base_button
//

void init_style_base_button_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][3]));
    lv_style_set_radius(style, 50);
};

lv_style_t *get_style_base_button_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_base_button_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_base_button(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_base_button_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_base_button(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_base_button_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: bigArc
//

void init_style_big_arc_INDICATOR_DEFAULT(lv_style_t *style) {
    lv_style_set_arc_width(style, 20);
    lv_style_set_arc_color(style, lv_color_hex(theme_colors[active_theme_index][4]));
};

lv_style_t *get_style_big_arc_INDICATOR_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_big_arc_INDICATOR_DEFAULT(style);
    }
    return style;
};

void init_style_big_arc_KNOB_DEFAULT(lv_style_t *style) {
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][5]));
    lv_style_set_shadow_width(style, 30);
    lv_style_set_shadow_color(style, lv_color_hex(0xe2d036));
    lv_style_set_shadow_opa(style, 180);
    lv_style_set_shadow_spread(style, 2);
};

lv_style_t *get_style_big_arc_KNOB_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_big_arc_KNOB_DEFAULT(style);
    }
    return style;
};

void init_style_big_arc_MAIN_DEFAULT(lv_style_t *style) {
    lv_style_set_arc_width(style, 20);
    lv_style_set_bg_color(style, lv_color_hex(theme_colors[active_theme_index][1]));
};

lv_style_t *get_style_big_arc_MAIN_DEFAULT() {
    static lv_style_t *style;
    if (!style) {
        style = (lv_style_t *)lv_mem_alloc(sizeof(lv_style_t));
        lv_style_init(style);
        init_style_big_arc_MAIN_DEFAULT(style);
    }
    return style;
};

void add_style_big_arc(lv_obj_t *obj) {
    (void)obj;
    lv_obj_add_style(obj, get_style_big_arc_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_big_arc_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_add_style(obj, get_style_big_arc_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

void remove_style_big_arc(lv_obj_t *obj) {
    (void)obj;
    lv_obj_remove_style(obj, get_style_big_arc_INDICATOR_DEFAULT(), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_big_arc_KNOB_DEFAULT(), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_remove_style(obj, get_style_big_arc_MAIN_DEFAULT(), LV_PART_MAIN | LV_STATE_DEFAULT);
};

//
// Style: screenLabel
//

void add_style_screen_label(lv_obj_t *obj) {
    (void)obj;
};

void remove_style_screen_label(lv_obj_t *obj) {
    (void)obj;
};

//
//
//

void add_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*AddStyleFunc)(lv_obj_t *obj);
    static const AddStyleFunc add_style_funcs[] = {
        add_style_base_button,
        add_style_big_arc,
        add_style_screen_label,
    };
    add_style_funcs[styleIndex](obj);
}

void remove_style(lv_obj_t *obj, int32_t styleIndex) {
    typedef void (*RemoveStyleFunc)(lv_obj_t *obj);
    static const RemoveStyleFunc remove_style_funcs[] = {
        remove_style_base_button,
        remove_style_big_arc,
        remove_style_screen_label,
    };
    remove_style_funcs[styleIndex](obj);
}