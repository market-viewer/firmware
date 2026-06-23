#include "graph_drawer.h"
#include <algorithm>
#include "colors.h"

static lv_point_t pointBuffer[400]; 

struct GraphAnimData {
    lv_obj_t* line;
    lv_obj_t* circle;
};
static GraphAnimData graph_anim_data;

static int32_t circle_size = 20;


void draw_candle_graph(lv_obj_t* panel, size_t pointCount) {
    Serial.println("Rendering candle graph");
    lv_color_t colorGreen = lv_color_hex(redColorGraph);
    lv_color_t colorRed = lv_color_hex(greenColorGraph);

    for (size_t i = 1; i < pointCount; i++) {
        int32_t prev_x = pointBuffer[i-1].x;
        int32_t prev_y = pointBuffer[i-1].y;
        int32_t current_x = pointBuffer[i].x;
        int32_t current_y = pointBuffer[i].y;

        // Width with a safe 2px gap
        int32_t rect_w = current_x - prev_x - 2; 
        if (rect_w < 2) rect_w = 2;

        int32_t rect_y = std::min(prev_y, current_y);
        int32_t rect_h = std::abs(prev_y - current_y);
        if (rect_h < 3) rect_h = 3; // ensure visible dash for flat prices

        lv_color_t candleColor = (current_y <= prev_y) ? colorGreen : colorRed;

        lv_obj_t* candle = lv_obj_create(panel);
        lv_obj_remove_style_all(candle); 
        
        lv_obj_set_size(candle, rect_w, rect_h);
        lv_obj_set_pos(candle, prev_x, rect_y);
        
        lv_obj_set_style_bg_color(candle, candleColor, 0);
        lv_obj_set_style_bg_opa(candle, LV_OPA_COVER, 0);
        lv_obj_set_style_radius(candle, 5, LV_PART_MAIN);
    }

}


void graph_anim_cb(void * var, int32_t current_point_count) {
    GraphAnimData* data = (GraphAnimData*)var;
    
    if (current_point_count < 2) return; 

    lv_line_set_points(data->line, pointBuffer, current_point_count);

    int32_t tip_x = pointBuffer[current_point_count - 1].x;
    int32_t tip_y = pointBuffer[current_point_count - 1].y;
    
    lv_obj_set_pos(data->circle, tip_x - (circle_size / 2), tip_y - (circle_size / 2));
}


void draw_line_graph(lv_obj_t* panel, size_t pointCount, lv_color_t color) {
    lv_obj_t* line = lv_line_create(panel);
    lv_line_set_points(line, pointBuffer, pointCount);
    lv_obj_set_style_line_width(line, 4, LV_PART_MAIN);
    lv_obj_set_style_line_color(line, color, LV_PART_MAIN);
    lv_obj_set_style_line_rounded(line, false, LV_PART_MAIN);
    
    //add round ball at the end
    lv_obj_t* circle = draw_graph_circle(pointBuffer[pointCount - 1], pointBuffer[pointCount - 1], color, panel);

    graph_anim_data.line = line;
    graph_anim_data.circle = circle;

    // start the graph animation
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, &graph_anim_data);
    lv_anim_set_values(&a, 1, pointCount);
    lv_anim_set_time(&a, 2000);                
    lv_anim_set_delay(&a, 200);                
    lv_anim_set_exec_cb(&a, graph_anim_cb);        
    lv_anim_set_path_cb(&a, lv_anim_path_ease_in_out);
    
    lv_anim_start(&a);
}

lv_obj_t* draw_graph_circle(lv_point_t x_point, lv_point_t y_point, lv_color_t color, lv_obj_t* panel) {
    int32_t x_pos = x_point.x;
    int32_t y_pos = y_point.y;

    lv_obj_t* circle = lv_obj_create(panel);
    lv_obj_remove_style_all(circle);
    
    lv_obj_set_size(circle, circle_size, circle_size);
    lv_obj_set_style_bg_color(circle, color, LV_PART_MAIN);       
    lv_obj_set_style_bg_opa(circle, LV_OPA_COVER, LV_PART_MAIN); 
    lv_obj_set_style_radius(circle, LV_RADIUS_CIRCLE, LV_PART_MAIN);

    return circle;
}


void draw_graph_on_canvas(ScreenType screenType, const std::vector<double>& rawData, lv_color_t color, bool isCandleGraph) {
    if (rawData.size() < 2) return;

    lv_obj_t* panel = get_screen_panel_from_type(screenType);
    if (panel == nullptr) return;

    int32_t w = lv_obj_get_width(panel);
    int32_t h = lv_obj_get_height(panel);
    
    if (w < 5 || h < 5) return;

    //horizontal padding 
    int32_t pad_x = 40;
    int32_t usable_w = w - (pad_x * 2);

    size_t totalDataPoints = rawData.size();
    size_t step = 1;
    
    int minPixelsPerPoint = isCandleGraph ? 20 : 10; 
    size_t maxPoints = usable_w / minPixelsPerPoint;
    if (totalDataPoints > maxPoints) step = totalDataPoints / maxPoints;

    double minVal = rawData[0];
    double maxVal = rawData[0];
    for (size_t i = 0; i < totalDataPoints; i += step) {
        if (rawData[i] < minVal) minVal = rawData[i];
        if (rawData[i] > maxVal) maxVal = rawData[i];
    }
    
    double range = maxVal - minVal;
    if (range < 0.000001) range = 1.0;
    
    double padding = range * 0.1;
    minVal -= padding;
    maxVal += padding;
    range = maxVal - minVal;

    size_t pointCount = 0;
    for (size_t i = 0; i < totalDataPoints; i += step) {
        if (pointCount >= 400) break; 

        double normalized = (rawData[i] - minVal) / range;
        if (normalized < 0.0) normalized = 0.0;
        if (normalized > 1.0) normalized = 1.0;

        pointBuffer[pointCount].x = pad_x + (lv_coord_t)((i * usable_w) / (totalDataPoints - 1));
        pointBuffer[pointCount].y = (lv_coord_t)(h - (normalized * h));
        pointCount++;
    }

    if (pointCount > 0) pointBuffer[0].x = pad_x;
    if (pointCount > 1) pointBuffer[pointCount-1].x = w - pad_x - 1;

    
    if (!isCandleGraph) {
        draw_line_graph(panel, pointCount, color);
    } else {
        draw_candle_graph(panel, pointCount);
    }
}

lv_obj_t* get_screen_panel_from_type(ScreenType screenType) {
    if (screenType == ScreenType::CRYPTO) {
        return objects.crypto_graph_panel;
    } else if (screenType == ScreenType::STOCK) {
        return objects.stock_graph_panel;
    }

    return nullptr;
}
