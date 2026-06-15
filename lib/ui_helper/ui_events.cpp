#include "ui.h"
#include "screens.h"
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
#include <stdio.h>

//global shield to not control screen when it is off
lv_obj_t * blackout_shield = NULL;

#define WAKE_BUTTON_PIN GPIO_NUM_0 


void action_home_next_screen(lv_event_t * e) {
    //check if the gesture is swipe to left
    if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
        lv_indev_wait_release(lv_indev_get_act());

        go_next_screen();
    }
}

void action_restart_device(lv_event_t * e) {
    play_button_click_sound();

    show_info_message("Restarting device");
    delay(400);
    ESP.restart();

}

void action_nav_to_brightness_scr(lv_event_t * e) {
    play_button_click_sound();

	loadScreenNoAnim(SCREEN_ID_BRIGHTNESS_SCREEN);
        
}

void action_nav_to_volume_scr(lv_event_t * e) {
    play_button_click_sound();

	loadScreenNoAnim(SCREEN_ID_VOLUME_SCREEN);
}

void action_turn_off_backlight(lv_event_t * e) {
    play_button_click_sound();

    display_message("Click again to wake up.", MessageSeverity::INFO);
    delay(500);
    destroy_message();
    toggleScreenOff(e);
}

void action_nav_to_screens_scr(lv_event_t * e) {
    play_button_click_sound();

	loadScreenNoAnim(SCREEN_ID_SCREENS_SCREEN);
}

void action_toggle_rotation_settings(lv_event_t * e) {
    play_button_click_sound();

    shouldRotate = !shouldRotate;
    saveHardwaveBoolToPreferences("rotation", shouldRotate);
}

void action_nav_to_wifi_scr(lv_event_t * e) {
    play_button_click_sound();

	loadScreenNoAnim(SCREEN_ID_WIFI_SCREEN);
}

void action_nav_to_home_scr(lv_event_t * e) {
    play_button_click_sound();

	loadScreenNoAnim(SCREEN_ID_HOME_SCREEN);
}

void action_set_brightness_from_arc(lv_event_t * e) {
    lv_obj_t * slider = lv_event_get_target(e);
    int32_t percentage = lv_arc_get_value(slider);
        
    currentBrightness = percentage;

    set_brightness_percentage(percentage);

	char buf[16];     
    snprintf(buf, sizeof(buf), "%d%%", (int)percentage);     
    lv_label_set_text(objects.brightness_value_label, buf);
}

void action_open_wifi_portal(lv_event_t * e) {
    play_button_click_sound();

    //show wifi credentials
    displayWifiConnectCredentials(true);

    bool success = start_wifi_portal();

    //hide credentials
    displayWifiConnectCredentials(false);
    
    if (success) {
        Serial.println("WiFi configured!");
        play_beep(1000, 100);  // Success beep
        changeWifiScreenConnected();
    } else {
        Serial.println("WiFi config cancelled/failed");
        play_beep(400, 200);  // Error beep
        show_error_message("Wifi connection failed");
        changeWifiScreenNotConnected();
    }
}

void action_reset_wifi_config(lv_event_t * e) {
    play_button_click_sound();

	Serial.println("Resetting WiFi configuration...");
    show_info_message("Resetting device config");
    reset_wifi_config();
    changeWifiScreenNotConnected();
    play_beep(600, 100);
}

void action_timer_reset_pressed(lv_event_t * e) {
    play_button_click_sound();

	resetTimer(get_active_screen());
}

void action_timer_start_pressed(lv_event_t * e) {
    play_button_click_sound();

	startTimerToggle(get_active_screen());
}

void action_toggle_market_screen_setting(lv_event_t * e) {
    lv_obj_t * sw = lv_event_get_target(e);
    bool isSwitchedOn = lv_obj_has_state(sw, LV_STATE_CHECKED);
    updateDispalyGraph(isSwitchedOn, get_active_screen());
}

void action_simple_display_switch_toggle(lv_event_t * e) {
    play_button_click_sound();

    lv_obj_t * sw = lv_event_get_target(e);
    bool isSwitchedOn = lv_obj_has_state(sw, LV_STATE_CHECKED);
    updateSimpleDisplay(isSwitchedOn, get_active_screen());
}
void action_display_graph_switch_toggle(lv_event_t * e) {
    play_button_click_sound();

    lv_obj_t * sw = lv_event_get_target(e);
    bool isSwitchedOn = lv_obj_has_state(sw, LV_STATE_CHECKED);
    updateDispalyGraph(isSwitchedOn, get_active_screen());
}
void action_candle_chart_switch_toggle(lv_event_t * e) {
    play_button_click_sound();

    lv_obj_t * sw = lv_event_get_target(e);
    bool isSwitchedOn = lv_obj_has_state(sw, LV_STATE_CHECKED);
    updateCandleGraph(isSwitchedOn, get_active_screen());
}

void action_save_volume(lv_event_t * e) {
	saveHardwaveNumberToPreferences("volume", currentVolume);
}

void action_save_brightness(lv_event_t * e) {
	saveHardwaveNumberToPreferences("brightness", currentBrightness);
}

void action_update_wifi_screen_status_on_load(lv_event_t * e) {
	if (is_wifi_connected()) {
        changeWifiScreenConnected();
    } else {
        changeWifiScreenNotConnected();
    }
}

void action_handle_screens_screen_load(lv_event_t * e) {
	if(is_wifi_connected()) {
        lv_obj_clear_state(objects.screens_refetch_button, LV_STATE_DISABLED);
        lv_label_set_text(objects.screen_not_fetched_label, "No screens");
    } else {
        lv_obj_add_state(objects.screens_refetch_button, LV_STATE_DISABLED);
        lv_label_set_text(objects.screen_not_fetched_label, "No wifi...");
    }
}

void action_set_buttons_status_home_screen(lv_event_t * e) {
    changeHomeScreenWifiIcon(is_wifi_connected());
}

void action_screen_change_swipe(lv_event_t * e) {
	changeScreenOnSwipe();
}

void action_finance_screen_gesture(lv_event_t * e) {
	// first check the horizontal swipes
	if (changeScreenOnSwipe()) {
		return;
	}

	//check the vertial swipes
	if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_BOTTOM) {
		updateScreenForce();
	} else if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_TOP) {
		loadScreenNoAnim(SCREEN_ID_MARKET_DATA_SETTING_SCREEN);
	}
}

void action_market_data_setting_screen_load(lv_event_t * e) {
	updateMarketDataSettingsScreenOnLoad(get_active_screen());
}

void action_exit_market_data_setting(lv_event_t * e) {
	if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_BOTTOM) {
		go_back_from_market_data_setting();
	}
}

void action_turn_off_device(lv_event_t * e) {
    play_button_click_sound();

    Serial.println("Shutting down...");    
    if (gfx) {
        gfx->displayOff(); 
    }
    digitalWrite(PA, LOW); 

    esp_sleep_enable_ext0_wakeup(WAKE_BUTTON_PIN, 0);
    delay(100);

    esp_deep_sleep_start();
}

void action_set_volume_from_arc(lv_event_t * e) {
    lv_obj_t * arc = lv_event_get_target(e);
    int32_t percentage = lv_arc_get_value(arc);
    
    Serial.println("Setting volume to: " + String(percentage));
    currentVolume = percentage;
    
    set_volume_percentage(percentage);

    // play sound to verify volume
    play_beep((percentage + 100) * 5, 50);

	//update the label
	char buf[16];     
    snprintf(buf, sizeof(buf), "%d%%", (int)percentage);     
    lv_label_set_text(objects.volume_value_label, buf);
}

void action_refetch_screens(lv_event_t * e) {
    play_button_click_sound();

    display_message("Fetching screens...", MessageSeverity::INFO);
    bool successful = get_screens_from_backend();
    destroy_message();

    if (successful) {
        show_success_message("Screens updated");
    }

    updateScreensScreenOnDataFetch(successful);
}

void action_force_screen_update(lv_event_t * e) {
    updateScreenForce();
}

void action_close_ai_prompt_screen(lv_event_t * e) {
    play_button_click_sound();

    lv_obj_add_flag(objects.ai_prompt_container, LV_OBJ_FLAG_HIDDEN);
}

void action_open_ai_prompt_screen(lv_event_t * e) {
    play_button_click_sound();

    lv_obj_clear_flag(objects.ai_prompt_container, LV_OBJ_FLAG_HIDDEN);
}

void action_update_ai_text_screen_from_prompt(lv_event_t * e) {
    //close the prompt screen
    lv_obj_add_flag(objects.ai_prompt_container, LV_OBJ_FLAG_HIDDEN);

    //update the screen
    updateScreenForce();


}
