#pragma once
#include <Arduino.h>

// Initialize audio manager (call after init_hardware())
void init_audio_manager();

void play_beep(uint16_t frequency = 800, uint16_t duration_ms = 100);
void play_volume_beep();
void play_sound(const uint8_t* samples, uint32_t num_samples);
void play_button_click_sound();

void start_timer_alarm();
void stop_timer_alarm();
bool is_timer_alarm_playing();