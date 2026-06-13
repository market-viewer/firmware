#include "bootScreen.h"
#include "ui.h"
#include "images.h"

static lv_obj_t* loading_scr = NULL;

void showBootScreen() {
  loading_scr = lv_obj_create(NULL);
  lv_obj_set_style_bg_color(loading_scr, lv_color_hex(0x000000), 0); // Black background

  lv_obj_t* bootLogoBig = lv_img_create(loading_scr);
  lv_img_set_src(bootLogoBig, &img_logo_big);
  lv_obj_set_width(bootLogoBig, LV_SIZE_CONTENT);   /// 300
  lv_obj_set_height(bootLogoBig, LV_SIZE_CONTENT);    /// 300
  lv_obj_set_x(bootLogoBig, 0);
  lv_obj_set_y(bootLogoBig, 0);
  lv_obj_set_align(bootLogoBig, LV_ALIGN_CENTER);

  lv_scr_load(loading_scr);

  // Force LVGL to manually render the loading screen before WiFi blocks execution
  for (int i = 0; i < 20; i++) {
      lv_timer_handler();
      delay(10);
  }
}

void deleteBootScreen() {
  if (loading_scr != NULL) {
    loadScreen(SCREEN_ID_HOME_SCREEN);

    lv_obj_del(loading_scr);
    loading_scr = NULL;
  }
}