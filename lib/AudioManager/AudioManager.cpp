#include "AudioManager.h"
#include "HardwareDriver.h"
#include <math.h>
#include "sounds/bop_sound.h"

#define SAMPLE_RATE 16000

static bool audio_ready = false;

static volatile bool is_alarm_ringing = false;
static TaskHandle_t alarm_task_handle = NULL;
static SemaphoreHandle_t i2s_mutex = NULL;

//background worker thread
void alarm_background_task(void *pvParameters) {
    while (true) {
        if (is_alarm_ringing) {
            play_beep(523, 100); // C5
            vTaskDelay(pdMS_TO_TICKS(100));
            if (!is_alarm_ringing) continue; // Early exit check
            
            play_beep(659, 100); // E5
            vTaskDelay(pdMS_TO_TICKS(100));
            if (!is_alarm_ringing) continue;
            
            play_beep(784, 100); // G5
            vTaskDelay(pdMS_TO_TICKS(100));
            if (!is_alarm_ringing) continue;
            
            play_beep(1046, 200); // C6 (High, held longer)
            
            // Wait 1 second before playing the sequence again
            vTaskDelay(pdMS_TO_TICKS(700));
        } else {
            vTaskDelay(pdMS_TO_TICKS(50));
        }
    }
}

void init_audio_manager() {
    if (es_handle != NULL) {
        audio_ready = true;

        // create the Mutex lock
        i2s_mutex = xSemaphoreCreateMutex();

        //create the background tast
        xTaskCreatePinnedToCore(
            alarm_background_task,   // The function to run
            "AlarmTask",             // Task name
            4096,                    // Stack size (4KB)
            NULL,                    // Parameters
            1,                       // Priority (1 is low, keeps UI fast)
            &alarm_task_handle,      // Task handle
            0                        // Pin to Core 0
        );

        Serial.println("AudioManager ready!");
    } else {
        Serial.println("AudioManager: ES8311 not available!");
    }
}

void play_beep(uint16_t frequency, uint16_t duration_ms) {
    if (!audio_ready) {
        Serial.println("Audio not ready!");
        return;
    }
    
    // wait for the lock before writing to I2S
    if (xSemaphoreTake(i2s_mutex, portMAX_DELAY)) {
        int num_samples = (SAMPLE_RATE * duration_ms) / 1000;
        float samples_per_cycle = (float)SAMPLE_RATE / frequency;
        
        for (int i = 0; i < num_samples; i++) {
            float angle = (2.0f * M_PI * i) / samples_per_cycle;
            int16_t sample = (int16_t)(sinf(angle) * 16000);  
            int16_t stereo_sample[2] = {sample, sample};
            i2s.write((uint8_t*)stereo_sample, sizeof(stereo_sample));
        }
        // Release the lock
        xSemaphoreGive(i2s_mutex);
    }
}

void start_timer_alarm() {
    if (!audio_ready) return;
    is_alarm_ringing = true;
}

void stop_timer_alarm() {
    is_alarm_ringing = false;
}

bool is_timer_alarm_playing() {
    return is_alarm_ringing;
}


void play_volume_beep() {
    play_beep(800, 80);
}

void play_click() {
    play_beep(1200, 30);
}

void play_sound(const int16_t* samples, uint32_t num_samples, bool stereo) {
    if (!audio_ready) {
        Serial.println("Audio not ready!");
        return;
    }
    
    // Wait for the lock before writing to I2S
    if (xSemaphoreTake(i2s_mutex, portMAX_DELAY)) {
        if (stereo) {
            i2s.write((uint8_t*)samples, num_samples * sizeof(int16_t));
        } else {
            for (uint32_t i = 0; i < num_samples; i++) {
                int16_t sample = pgm_read_word(&samples[i]);
                int16_t stereo_sample[2] = {sample, sample};
                i2s.write((uint8_t*)stereo_sample, sizeof(stereo_sample));
            }
        }
        // Release the lock
        xSemaphoreGive(i2s_mutex);
    }
}

void play_bop() {
    play_sound(bop_sound, bop_sound_len, false);
}

