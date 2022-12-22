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
#include <lvgl.h>

class widgetArc
{
public:
    void create(lv_obj_t *parent, int x, int y, int w)
    {
        lv_obj_t *arc_bg, *arc_fg;
        lv_style_t arc_bg_st, arc_fg_st;

        arc_bg_st.line.width = 5;

        arc_fg_st.line.width = 5;

        arc_bg = lv_arc_create(parent, NULL);
        lv_obj_set_pos(arc_bg, x, y);
        lv_obj_set_size(arc_bg, w, w);
        lv_arc_set_angles(arc_bg, 45, 315);
        lv_obj_set_style(arc_bg, &arc_bg_st);

        arc_fg = lv_arc_create(parent, NULL);
        lv_obj_set_pos(arc_fg, x, y);
        lv_obj_set_size(arc_fg, w, w);
        lv_arc_set_angles(arc_fg, 180, 315);
        lv_obj_set_style(arc_fg, &arc_fg_st);
    }

    void set_bg_color()
    {
    }

    void set_value(lv_obj_t *arc, uint8_t p)
    {
        int v;
        v = (((lv_arc_get_angle_end(arc) - lv_arc_get_angle_start(arc)) / 100) * p ) + lv_arc_get_angle_start(arc);
        lv_arc_set_angles(arc_fg, v, lv_arc_get_angle_end(arc));
    }

private:
};
