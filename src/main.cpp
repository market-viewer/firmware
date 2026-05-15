#include <Arduino.h>
#include "HardwareDriver.h"
#include "AudioManager.h"
#include "GuiManager.h"
#include "WifiConfig.h"
#include "startupEvents.h"
#include "ScreensManager.h"
#include "ui_events.h"

#define WAKE_BUTTON_PIN 0
bool lastWakeButtonState = HIGH;
unsigned long lastWakeButtonTime = 0;

void setup() {
  Serial.begin(115200);
  
  pinMode(WAKE_BUTTON_PIN, INPUT_PULLUP);

  //initialize Hardware (Screen, Touch, I2C)
  init_hardware();

  //initialize audio 
  init_audio_manager();
  
  //try to connect to saved wifi
  init_wifi_config();
  
  //initialize LVGL (Buffers, UI)
  init_lvgl_interface();

  // load saved hardware settings (brightness, volume, rotation)
  loadHardwareSettingsFromPreferences();

  //load screens on startup
  loadScreensOnStartup();
  
  Serial.println("System Ready!");
}

void loop() {
    update_gui();
  
    updateScreen();

    // check the button to return to the home screen
    bool currentButtonState = digitalRead(WAKE_BUTTON_PIN);
    if (currentButtonState == LOW && lastWakeButtonState == HIGH) {
        if (millis() - lastWakeButtonTime > 200) { // debounce
            go_to_home_screen();
            lastWakeButtonTime = millis();
        }
    }
    lastWakeButtonState = currentButtonState;

    delay(5);
}