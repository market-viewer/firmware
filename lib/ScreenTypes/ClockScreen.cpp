#include "ClockScreen.h"
#include "ui.h"
#include <time.h>
#include "screens.h"
#include "images.h"

bool ClockScreen::needsUpdate() {    
    // update the data here, we dont want to fetch from our standart backend api
    if (millis() - lastFetchTime >= refreshIntervalMillis) {
        configTime(0, 0, "pool.ntp.org", "time.nist.gov");
    }
    return false;
}


void ClockScreen::updateClockTimeDisplay() {
    static uint32_t last_tick = 0;
    
    // only update once a second
    if (millis() - last_tick > 1000) {
        last_tick = millis();

        // get raw time
        time_t now;
        time(&now);

        // convert to local time safely based on the timezone code
        struct tm timeinfo;
        localtime_r(&now, &timeinfo); 

        hour = timeinfo.tm_hour;
        minute = timeinfo.tm_min;
        second = timeinfo.tm_sec;

        char timeText[16]; 

        //check the clock type
        if (clockType == ClockType::ANALOG_CLOCK) {
            if (!use24Hour) {
                hour = hour % 12;
                if (hour == 0) hour == 12;
            }
            snprintf(timeText, sizeof(timeText), "%02d:%02d", hour, minute);
    
            // calculate angles for needles
            int32_t second_angle = second * 60; 
            int32_t minute_angle = minute * 60; 
            int32_t hour_angle = ((hour % 12) * 300) + (minute * 5); 
            
            // update all needles
            lv_img_set_angle(objects.clock_needle_minute, minute_angle);        
            lv_img_set_angle(objects.clock_needle_second, second_angle);
    
            //update digial clock
            lv_label_set_text(objects.time_label, timeText);
        } else {
            if (use24Hour) {
                snprintf(timeText, sizeof(timeText), "%02d:%02d:%02d", hour, minute, second);
            } else {
                int hour12 = hour % 12;
                if (hour12 == 0) hour12 = 12;
                const char* ampm = (hour < 12) ? "AM" : "PM";
                snprintf(timeText, sizeof(timeText), "%d:%02d %s", hour12, minute, ampm);
            }

            //update date
            char dateText[32];
            strftime(dateText, sizeof(dateText), "%d %b %Y", &timeinfo);

            lv_label_set_text(objects.digital_time_label, timeText);
            lv_label_set_text(objects.digital_date_label, dateText);
        }

    }
}

void ClockScreen::render() {
    //set the timezone for the specific clock
    setenv("TZ", timezoneCode.c_str(), 1);
    tzset();

    if (clockType == ClockType::ANALOG_CLOCK) {
        renderAnalog();
    } else {
        renderDigital();
    }
}

void ClockScreen::renderDigital() {
    //change the background
    lv_obj_set_style_bg_img_src(objects.clock_screen, &img_blue_gradient, LV_PART_MAIN);

    //hide analog parts
    lv_obj_add_flag(objects.timezone_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(objects.time_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(objects.clock_needle_second, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(objects.clock_needle_minute, LV_OBJ_FLAG_HIDDEN);
    
    //show digital parts
    lv_obj_clear_flag(objects.digital_time_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(objects.digital_date_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(objects.digital_timezone_label, LV_OBJ_FLAG_HIDDEN);

    //set the values
    lv_label_set_text(objects.digital_timezone_label, timezone.c_str());
}


void ClockScreen::renderAnalog() {
    //change the background
    lv_obj_set_style_bg_img_src(objects.clock_screen, &img_clock_gauge, LV_PART_MAIN);

    //hide digital parts
    lv_obj_add_flag(objects.digital_time_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(objects.digital_date_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(objects.digital_timezone_label, LV_OBJ_FLAG_HIDDEN);
    
    //show analog parts
    lv_obj_clear_flag(objects.timezone_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(objects.time_label, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(objects.clock_needle_second, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(objects.clock_needle_minute, LV_OBJ_FLAG_HIDDEN);

    //set the values
    lv_label_set_text(objects.digital_timezone_label, timezone.c_str());
}