
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
// #include "widgets.h"
// #include "widgets_class.h"

class WidgetsScreen : public Screen
{
public:
  virtual void pre()
  {
    lv_style_copy(&arc_bg_st, &lv_style_plain);
    arc_bg_st.line.width = 5;

    lv_style_copy(&arc_fg_st, &lv_style_plain);
    arc_fg_st.line.color = lv_color_hex(0x2db710);
    arc_fg_st.text.color = lv_color_hex(0x2db710);
    arc_fg_st.line.width = 5;

    // BATTERY GAUGE
    x = 0;
    y = 0;
    w = 60;
    arc_bg = lv_arc_create(lv_scr_act(), NULL);
    lv_obj_set_style(arc_bg, &arc_bg_st);
    lv_obj_set_pos(arc_bg, x, y);
    lv_obj_set_size(arc_bg, w, w);
    lv_arc_set_angles(arc_bg, 45, 315);

    arc_fg = lv_arc_create(lv_scr_act(), NULL);
    lv_obj_set_style(arc_fg, &arc_fg_st);
    lv_obj_set_pos(arc_fg, x, y);
    lv_obj_set_size(arc_fg, w, w);
    lv_arc_set_angles(arc_fg, 315, 315);

    label_charge = lv_label_create(arc_fg, NULL);
    lv_obj_align_origo(label_charge, arc_fg, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_style(label_charge, &arc_fg_st);

    label_battery = lv_label_create(arc_fg, NULL);
    lv_obj_align_origo(label_battery, arc_fg, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    lv_obj_set_style(label_battery, &arc_fg_st);
    lv_label_set_text(label_charge, "Battery");

    // create_gauge(lv_scr_act(), 0, 0, 60);
    // x = 120;
    // y = 120;
    // w = 120;
    // arc_bg = lv_arc_create(lv_scr_act(), NULL);
    // lv_obj_set_style(arc_bg, &arc_bg_st);
    // lv_obj_set_pos(arc_bg, x, y);
    // lv_obj_set_size(arc_bg, w, w);
    // lv_arc_set_angles(arc_bg, 45, 315);

    // arc_fg = lv_arc_create(lv_scr_act(), NULL);
    // lv_obj_set_style(arc_fg, &arc_fg_st);
    // lv_obj_set_pos(arc_fg, x, y);
    // lv_obj_set_size(arc_fg, w, w);
    // lv_arc_set_angles(arc_fg, 315, 315);
    // try
    // widgetArc arc1;
    // arc1.create(lv_scr_act(), 120, 0, 60);
    // }
  }

  virtual void main()
  {
    int p = get_battery_percent();
    int v = (((lv_arc_get_angle_end(arc_bg) - lv_arc_get_angle_start(arc_bg)) / 100) * p) + lv_arc_get_angle_start(arc_bg);
    lv_arc_set_angles(arc_fg, v, 315);
    lv_label_set_text_fmt(label_charge, "%i%%", p);
  }

  virtual void up()
  {
  }

  virtual void down()
  {
  }

  virtual void right()
  {
    set_last_menu();
  }

private:
  lv_obj_t *arc_bg, *arc_fg, *label_charge, *label_battery;
  lv_style_t arc_bg_st, arc_fg_st;
  lv_coord_t x, y, w;
};

WidgetsScreen widgetsScreen;
