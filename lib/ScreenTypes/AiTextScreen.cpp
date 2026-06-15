#include "AiTextScreen.h"
#include "ui.h"
#include "screens.h"

void AiTextScreen::parseData(JsonObject& data) {
    displayText = data["displayText"] | "";
}

bool AiTextScreen::needsUpdate() {
    unsigned long refreshIntervalMillis = refreshIntervalHours * 3600000UL;
    
    return (millis() - lastFetchTime >= refreshIntervalMillis);
}


void AiTextScreen::render() {
    if (displayText == "") {
        renderNoData();
    } else {
        renderData();
    }
}

void AiTextScreen::renderNoData() {
    //hide text data
    lv_obj_add_flag(objects.ai_text_container, LV_OBJ_FLAG_HIDDEN);

    lv_obj_clear_flag(objects.ai_no_data_container, LV_OBJ_FLAG_HIDDEN);

    //edit the prompt
    lv_label_set_text(objects.ai_prompt_label, prompt.c_str());
}

void AiTextScreen::renderData() {
    //hide prompt data
    lv_obj_add_flag(objects.ai_no_data_container, LV_OBJ_FLAG_HIDDEN);
    
    //show display data
    lv_obj_clear_flag(objects.ai_text_container, LV_OBJ_FLAG_HIDDEN);

    //edit the lables
    lv_label_set_text(objects.ai_text_label, displayText.c_str());

    lv_label_set_text(objects.ai_prompt_label, prompt.c_str());
}