#include "StockScreen.h"
#include "ui.h"
#include "screens.h"
#include "images.h"
#include "messageDisplay.h"
#include "HttpRequestManager.h"
#include "utils.h"
#include "string"
#include "graph_drawer.h"
#include "colors.h"

void StockScreen::render() {
    //update current price and asset name (same for simple display and normal)
    std::string formattedPrice = build_price_label(price, currency).c_str();

    String tempName = String(symbol.c_str());
    tempName.toUpperCase();
    std::string assetPlusCurrency = (tempName + " " + currency).c_str();

    //select right font size based on price label size
    const lv_font_t* correctFont = select_correct_font_size(formattedPrice, 450);
    lv_obj_set_style_text_font(objects.stock_price_label, correctFont, LV_PART_MAIN);

    //set values
    lv_label_set_text(objects.stock_price_label, formattedPrice.c_str());
    lv_label_set_text(objects.stock_time_frame_label, timeFrame.c_str());
    lv_label_set_text(objects.stock_symbol_currency_label, assetPlusCurrency.c_str());
    
    //update colors
    if (priceChange >= 0) {
        lv_obj_set_style_bg_img_src(objects.stock_screen, &img_background_green, LV_PART_MAIN);
    } else {
        lv_obj_set_style_bg_img_src(objects.stock_screen, &img_background_red, LV_PART_MAIN);
    }

    //handle simple display and normal display
    if (simpleDisplay) {
        renderSimple();
    } else { 
        renderNormal();
    }

    //clear graph data
    lv_obj_clean(get_screen_panel_from_type(ScreenType::STOCK));

    //display graph data
    if (displayGraph) {
        renderGraph();
    }
}

void StockScreen::renderNormal() {
    //show all widgets
    lv_obj_clear_flag(objects.stock_price_change_label, LV_OBJ_FLAG_HIDDEN);    
    lv_obj_clear_flag(objects.stock_name_label, LV_OBJ_FLAG_HIDDEN);    
    lv_obj_clear_flag(objects.stock_market_open_cont, LV_OBJ_FLAG_HIDDEN);   

    //update widgets values
    std::string formattedPriceChange = build_price_change_label(priceChange).c_str();
    lv_label_set_text(objects.stock_price_change_label, formattedPriceChange.c_str());    

    //handle market dat open
    if (isMarketOpen) {
        lv_label_set_text(objects.stock_market_open_label, "OPEN");
        lv_obj_set_style_bg_color(objects.stock_market_open_icon, lv_color_hex(greenColor), LV_PART_MAIN);
    } else {
        lv_label_set_text(objects.stock_market_open_label, "CLOSED");
        lv_obj_set_style_bg_color(objects.stock_market_open_icon, lv_color_hex(redColor), LV_PART_MAIN);
    }

    lv_label_set_text(objects.stock_name_label, stockName.c_str());

    //chagne colors based on price change
    if (priceChange >= 0) {
        lv_obj_set_style_bg_color(objects.stock_price_change_label, lv_color_hex(greenColor), LV_PART_MAIN);
    } else {
        lv_obj_set_style_bg_color(objects.stock_price_change_label, lv_color_hex(redColor), LV_PART_MAIN);
    }
 
}
void StockScreen::renderSimple() {
    //hide widgets for simple display
    lv_obj_add_flag(objects.stock_price_change_label, LV_OBJ_FLAG_HIDDEN);    
    lv_obj_add_flag(objects.stock_name_label, LV_OBJ_FLAG_HIDDEN);    
    lv_obj_add_flag(objects.stock_market_open_cont, LV_OBJ_FLAG_HIDDEN);     
}



void StockScreen::parseData(JsonObject& data) {
    currency = data["currency"] | "USD";
    price = data["price"] | 0.0f;
    isMarketOpen = data["isMarketOpen"] | false;
    stockName = data["name"] | "";
    priceChange = data["priceChange"] | 0.0f;
    
    // parse graph data array manually
    graphData.clear();
    graphData.shrink_to_fit(); // Release memory

    // Parse new graph data
    JsonArray graphArray = data["graphData"].as<JsonArray>();
    if (graphArray.size() > 0) {
        // Reserve memory to prevent reallocation
        graphData.reserve(graphArray.size());
        
        for (JsonVariant value : graphArray) {
            graphData.push_back(value.as<double>());
        }        
    }
}

bool StockScreen::needsUpdate() {
    unsigned long refreshIntervalMillis = refreshIntervalMinutes * 60 * 1000;

    return (millis() - lastFetchTime >= refreshIntervalMillis);
}

void StockScreen::renderGraph() {
    if (graphData.empty()) return;

    lv_color_t graphColor = priceChange >= 0 ? lv_color_hex(greenColorGraph) : lv_color_hex(redColorGraph);
    draw_graph_on_canvas(ScreenType::STOCK, graphData, graphColor, graphType == GraphType::CANDLE);
}