#include "ui.h"
#include "actions.h"
#include <Arduino.h>
#include "HardwareDriver.h"
#include "esp32-hal-cpu.h"
#include "AudioManager.h"
#include "WifiConfig.h"
#include "ui_events_helper.h"
#include "ScreensManager.h"
#include "messageDisplay.h"
#include "GuiManager.h"
#include <ArduinoJson.h>
#include "esp_sleep.h"
#include "HardwareDriver.h"
#include "pin_config.h" 

#include "AudioManager.h"


void action_next_screen(lv_event_t * e) {
    Serial.println("hi");
}

void action_toggle_turn_off(lv_event_t * e) {
        Serial.println("hi");

}

void action_play_button_clicked_sound(lv_event_t * e) {
        Serial.println("hi");

}

void action_restart_device(lv_event_t * e) {
        Serial.println("hi");

}

void action_nav_to_brightness_scr(lv_event_t * e) {
        Serial.println("hi");

}

void action_nav_to_volume_scr(lv_event_t * e) {
        Serial.println("hi");

}

void action_turn_off_backlight(lv_event_t * e) {
        Serial.println("hi");

}

void action_nav_to_screens_scr(lv_event_t * e) {
        Serial.println("hi");

}

void action_toggle_rotation_settings(lv_event_t * e) {
        Serial.println("hi");

}

void action_nav_to_wifi_scr(lv_event_t * e) {
        Serial.println("hi");

}

void action_nav_to_home_scr(lv_event_t * e) {
        Serial.println("hi");

}

void action_set_brightness_from_arc(lv_event_t * e) {
        Serial.println("hi");

}

void action_open_wifi_portal(lv_event_t * e) {
        Serial.println("hi");

}

void action_reset_wifi_config(lv_event_t * e) {
        Serial.println("hi");
}

void action_timer_reset_pressed(lv_event_t * e) {
        Serial.println("hi");
}

void action_timer_start_pressed(lv_event_t * e) {
        Serial.println("hi");
}

void action_simple_display_switch_toggle(lv_event_t * e) {
        Serial.println("hi");
}

void action_display_graph_switch_toggle(lv_event_t * e) {
        Serial.println("hi");
}

void action_candle_chart_switch_toggle(lv_event_t * e) {
        Serial.println("hi");
}

void action_save_volume(lv_event_t * e) {
        Serial.println("hi");
}

void action_save_brightness(lv_event_t * e) {
        Serial.println("hi");
}

void action_update_wifi_screen_status_on_load(lv_event_t * e) {
        Serial.println("hi");
}

void action_handle_screens_screen_load(lv_event_t * e) {
        Serial.println("hi");
}

void action_set_buttons_status_home_screen(lv_event_t * e) {
        Serial.println("hi");
}

void action_screen_change_swipe(lv_event_t * e) {
        Serial.println("hi");
}

void action_finance_screen_gesture(lv_event_t * e) {
        Serial.println("hi");
}

void action_market_data_setting_screen_load(lv_event_t * e) {
        Serial.println("hi");
}

void action_exit_market_data_setting(lv_event_t * e) {
        Serial.println("hi");
}

void action_turn_off_device(lv_event_t * e) {
        Serial.println("hi");
}

void action_toggle_roation_settings(lv_event_t * e) {
        Serial.println("hi");
}

void action_set_volume_from_arc(lv_event_t * e) {
        Serial.println("hi");
}