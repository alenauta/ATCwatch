#pragma once
#include "Arduino.h"
#include "class.h"
#include "images.h"
#include "menu.h"
#include "display.h"
#include "ble.h"
#include "time.h"
#include "battery.h"
#include "accl.h"
#include "push.h"
#include "heartrate.h"
#include "fonts.h"
#include <lvgl.h>

class widgetArc
{
public:
    lv_obj_t *arc_bg, *arc_fg;
    lv_style_t arc_bg_st, arc_fg_st;

    lv_obj_t *create(lv_obj_t *parent, lv_coord_t x, lv_coord_t y, lv_coord_t w)
    {
        arc_bg_st.line.width = 5;
        arc_fg_st.line.width = 5;

        arc_bg = lv_arc_create(parent, NULL);
        lv_obj_set_style(arc_bg, &arc_bg_st);
        lv_obj_set_pos(arc_bg, x, y);
        lv_obj_set_size(arc_bg, w, w);
        lv_arc_set_angles(arc_bg, 45, 315);

        arc_fg = lv_arc_create(parent, NULL);
        lv_obj_set_style(arc_fg, &arc_fg_st);
        lv_obj_set_pos(arc_fg, x, y);
        lv_obj_set_size(arc_fg, w, w);
        lv_arc_set_angles(arc_fg, 180, 315);
    }

    void set_bg_color()
    {
    }

    void set_value(uint8_t p)
    {
        int v;
        v = (((lv_arc_get_angle_end(arc_bg) - lv_arc_get_angle_start(arc_bg)) / 100) * p) + lv_arc_get_angle_start(arc_bg);
        lv_arc_set_angles(arc_fg, v, lv_arc_get_angle_end(arc_bg));
    }

private:
};
