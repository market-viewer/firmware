#include "ui_events_helper.h"
#include <Arduino.h>
#include "WifiConfig.h"
#include "HardwareDriver.h"
#include "AudioManager.h"
#include "ScreensManager.h"
#include <Preferences.h>
#include "CryptoScreen.h"
#include "StockScreen.h"
#include "TimerScreen.h"
#include "fonts.h"
#include "GuiManager.h"

static Preferences preferences;

extern bool isScreenOff;
extern int currentBrightness;
static lv_obj_t* blackout_shield = NULL;

void loadScreenNoAnim(enum ScreensEnum screenId) {
    lv_obj_t *screen = ((lv_obj_t **)&objects)[screenId - 1];
    
    lv_scr_load(screen);
}

bool changeScreenOnSwipe() {
    if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_LEFT) {
		lv_indev_wait_release(lv_indev_get_act());
        go_next_screen();
        
        return true;
    } else if (lv_indev_get_gesture_dir(lv_indev_get_act()) == LV_DIR_RIGHT) {
		lv_indev_wait_release(lv_indev_get_act());
        go_prev_screen();

        return true;
	}

    return false;
}



void changeWifiScreenNotConnected() {
    //change the connection status
    lv_label_set_text(objects.connection_label, "NOT CONNECTED");
    lv_obj_set_style_bg_color(objects.wifi_connection_round_indicator, lv_color_hex(theme_colors[active_theme_index][COLOR_ID_RED_DARK]), LV_PART_MAIN);
    //display the current wifif ssid
    lv_obj_add_flag(objects.connected_wifi_container, LV_OBJ_FLAG_HIDDEN);
}

void changeWifiScreenConnected() {
    //change the connection status
    lv_label_set_text(objects.connection_label, "CONNECTED");
    lv_obj_set_style_bg_color(objects.wifi_connection_round_indicator, lv_color_hex(0x1ec20c), LV_PART_MAIN);
    //display the current wifif ssid
    lv_label_set_text(objects.connected_wifi_ssid_label, get_connected_ssid());
    lv_obj_clear_flag(objects.connected_wifi_container, LV_OBJ_FLAG_HIDDEN);
    
    //display the backend url and device hash
    lv_label_set_text(objects.backend_url_label, get_backend_url());
}

void displayWifiConnectCredentials(bool shouldDisplay) {
    if (shouldDisplay) {
        lv_obj_clear_flag(objects.overlay_wifi_container, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text(objects.overlay_wifi_pwd_label_value, wifiPassword.c_str());
        lv_label_set_text(objects.overlay_wifi_ssid_label_value, wifiSSID.c_str());
        
        lv_refr_now(NULL);
        delay(100);
    } else {
        lv_obj_add_flag(objects.overlay_wifi_container, LV_OBJ_FLAG_HIDDEN);
    }

}

void changeHomeScreenWifiIcon(bool isConnected) {
    if (isConnected) {
        lv_obj_set_style_bg_color(objects.wifi_button, lv_color_hex(theme_colors[active_theme_index][COLOR_ID_YELLOW_DARK]), LV_PART_MAIN);
    } else {
        lv_obj_set_style_bg_color(objects.wifi_button, lv_color_hex(theme_colors[active_theme_index][COLOR_ID_RED_DARK]), LV_PART_MAIN);
    }
}

void toggleScreenOff(lv_event_t * e) {
        if (isScreenOff) {
        Serial.println("Screen waking up!");
        
        setCpuFrequencyMhz(240); // drop speed when device is 'turned on'
        set_brightness_percentage(currentBrightness);
        isScreenOff = false;

        if (blackout_shield != NULL) {
            lv_obj_del(blackout_shield);
            blackout_shield = NULL; 
        }
    } else {
        Serial.println("Screen going to sleep");

        set_brightness(0);
        isScreenOff = true;

        //CREATE THE SHIELD
        blackout_shield = lv_obj_create(lv_layer_top());        
        lv_obj_set_size(blackout_shield, LV_PCT(100), LV_PCT(100));        
        lv_obj_set_style_bg_opa(blackout_shield, 0, 0);
        lv_obj_set_style_border_width(blackout_shield, 0, 0);        
        lv_obj_add_flag(blackout_shield, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_clear_flag(blackout_shield, LV_OBJ_FLAG_SCROLLABLE);
        lv_obj_add_event_cb(blackout_shield, toggleScreenOff, LV_EVENT_CLICKED, NULL);

        setCpuFrequencyMhz(80); // drop speed when device is 'turned off'

    } 
}

//hardware screens
void saveHardwaveNumberToPreferences(String name, int value) {
    preferences.begin("hardware_config", false);
    preferences.putInt(name.c_str(), value);
    preferences.end();
}
void saveHardwaveBoolToPreferences(String name, bool value) {
    preferences.begin("hardware_config", false);
    preferences.putBool(name.c_str(), value);
    preferences.end();
}


// screens screen
void updateScreensScreenOnDataFetch(bool successfull) {
    if (!successfull) {
        lv_obj_add_flag(objects.screens_list_panel, LV_OBJ_FLAG_HIDDEN);
        lv_label_set_text_fmt(objects.screen_not_fetched_label, "Fetch error...");
        lv_obj_clear_flag(objects.screen_not_fetched_label, LV_OBJ_FLAG_HIDDEN);
    } else {
        lv_obj_clear_flag(objects.screens_list_panel, LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(objects.screen_not_fetched_label, LV_OBJ_FLAG_HIDDEN);

        // Clear existing children in the list panel (except template if you have one)
        lv_obj_clean(objects.screens_list_panel);
        
        std::vector<ScreenInfo> screens = get_all_screens_info();
        
        for (int i = 0; i < screens.size(); i++) {
            // Create a label for each screen
            lv_obj_t* label = lv_label_create(objects.screens_list_panel);
            
            String text = String(screens[i].position + 1) + ". " + screens[i].name;
            lv_label_set_text(label, text.c_str());
            
            // Style the label
            lv_obj_set_width(label, 300);
            lv_obj_set_height(label, 50);    /// 1
            lv_obj_set_align(label, LV_ALIGN_CENTER);
            lv_label_set_long_mode(label, LV_LABEL_LONG_SCROLL);
            lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN);
            lv_obj_set_style_text_font(label, &ui_font_mono30, LV_PART_MAIN);
        }
    }
}

void updateMarketDataSettingsScreenOnLoad(BaseScreen* activeScreen) {    
    bool displayGraph = true;
    bool simpleDisplay = false;
    GraphType graphType = GraphType::LINE;

    ScreenType screenType = activeScreen->getType();

    //set the states
    if(screenType == ScreenType::CRYPTO) {
        CryptoScreen* crypto = static_cast<CryptoScreen*>(activeScreen);

        displayGraph = crypto->shouldDisplayGraph();
        simpleDisplay = crypto->isSimpleDisplay();
        graphType = crypto->getGraphType();
    } else {
        StockScreen* stock = static_cast<StockScreen*>(activeScreen);

        displayGraph = stock->shouldDisplayGraph();
        simpleDisplay = stock->isSimpleDisplay();
        graphType = stock->getGraphType();
    }

    Serial.println("Display graph: " + displayGraph);
    Serial.println("Simple display: " + simpleDisplay);
    Serial.println("Candle graph: " + (graphType == GraphType::CANDLE));

    //update the ui
    if (simpleDisplay) {
        lv_obj_add_state(objects.simple_display_switch, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(objects.simple_display_switch, LV_STATE_CHECKED);
    } 

    if (displayGraph) {
        lv_obj_add_state(objects.display_graph_switch, LV_STATE_CHECKED);
        
        //enable char switch
        lv_obj_clear_state(objects.candle_chart_switch, LV_STATE_DISABLED);
    } else {
        lv_obj_clear_state(objects.display_graph_switch, LV_STATE_CHECKED);
        
        //disable editing candle graph
        lv_obj_add_state(objects.candle_chart_switch, LV_STATE_DISABLED);
    } 

    if (graphType == GraphType::CANDLE) {
        lv_obj_add_state(objects.candle_chart_switch, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(objects.candle_chart_switch, LV_STATE_CHECKED);
    } 

}

void updateSimpleDisplay(bool isSimpleDisplay, BaseScreen* activeScreen) {
    if (activeScreen->getType() == ScreenType::CRYPTO) {
        CryptoScreen* crypto = static_cast<CryptoScreen*>(activeScreen);
        
        crypto->setSimpleDisplay(isSimpleDisplay);
    } else {
        StockScreen* stock = static_cast<StockScreen*>(activeScreen);
        stock->setSimpleDisplay(isSimpleDisplay);

    }
}
void updateDispalyGraph(bool displayGraph, BaseScreen* activeScreen) {
    if (activeScreen->getType() == ScreenType::CRYPTO) {
        CryptoScreen* crypto = static_cast<CryptoScreen*>(activeScreen);
        crypto->setDisplayGraph(displayGraph);
    } else {
        StockScreen* stock = static_cast<StockScreen*>(activeScreen);
        stock->setDisplayGraph(displayGraph);
    }

    if(displayGraph) {
        lv_obj_clear_state(objects.candle_chart_switch, LV_STATE_DISABLED);    
    } else {
        lv_obj_add_state(objects.candle_chart_switch, LV_STATE_DISABLED);
    }

}
void updateCandleGraph(bool isCandleGraph, BaseScreen* activeScreen) {
    if (activeScreen->getType() == ScreenType::CRYPTO) {
        CryptoScreen* crypto = static_cast<CryptoScreen*>(activeScreen);
        
        crypto->setGraphType(isCandleGraph);
    } else {
        StockScreen* stock = static_cast<StockScreen*>(activeScreen);
        stock->setGraphType(isCandleGraph);
    }
}

//Timer actions
void resetTimer(BaseScreen* activeTimerScreen) {
    if (activeTimerScreen->getType() != ScreenType::TIMER) return;
    
    TimerScreen* timerScreen = static_cast<TimerScreen*>(activeTimerScreen);
    timerScreen->resetTimer();

}

void startTimerToggle(BaseScreen* activeTimerScreen) {
    if (activeTimerScreen->getType() != ScreenType::TIMER) return;
    
    TimerScreen* timerScreen = static_cast<TimerScreen*>(activeTimerScreen);
    if (timerScreen->isTimerRunning()) {
        timerScreen->togglePauseTimer();
    } else {
        timerScreen->startTimer();
    }        
}