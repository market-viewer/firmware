#pragma once
#include <Arduino.h>

// Initialize audio manager (call after init_hardware())
void init_audio_manager();

//synchrounous sounds
void play_beep(uint16_t frequency = 800, uint16_t duration_ms = 100);
void play_volume_beep();
void play_click();
void play_sound(const int16_t* samples, uint32_t num_samples, bool stereo = false);
void play_bop();


//asynchrounous sounds
void start_timer_alarm();
void stop_timer_alarm();
bool is_timer_alarm_playing();