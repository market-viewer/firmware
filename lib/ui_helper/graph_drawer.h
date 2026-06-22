#ifndef GRAPH_DRAWER_H
#define GRAPH_DRAWER_H

#include <Arduino.h>
#include <vector>
#include "ui.h"
#include "BaseScreen.h"

void draw_graph_on_canvas(ScreenType screenType, const std::vector<double>& graphData, lv_color_t color, bool isCandleGraph);

lv_obj_t* draw_graph_circle(lv_point_t x_point, lv_point_t y_point, lv_color_t color, lv_obj_t* panel);
void graph_anim_cb(void * var, int32_t current_point_count);

lv_obj_t* get_screen_panel_from_type(ScreenType screenType);

#endif