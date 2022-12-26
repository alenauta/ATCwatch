
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
    // STYLES
    lv_style_copy(&arc_bg_st, &lv_style_plain);
    arc_bg_st.line.width = 5;

    lv_style_copy(&arc_fg_st, &lv_style_plain);
    arc_fg_st.line.color = lv_color_hex(0x2db710);
    arc_fg_st.text.color = lv_color_hex(0x2db710);
    arc_fg_st.line.width = 5;

    lv_style_copy(&txt_st, &lv_style_plain);
    txt_st.text.color = lv_color_hex(0x2db710);
    txt_st.text.font = &lv_font_roboto_12;

    // BATTERY GAUGE
    x = 0;
    y = 0;
    w = 60;
    bat_arc_bg = lv_arc_create(lv_scr_act(), NULL);
    lv_obj_set_style(bat_arc_bg, &arc_bg_st);
    lv_obj_set_pos(bat_arc_bg, x, y);
    lv_obj_set_size(bat_arc_bg, w, w);
    lv_arc_set_angles(bat_arc_bg, 45, 315);

    bat_arc_fg = lv_arc_create(lv_scr_act(), NULL);
    lv_obj_set_style(bat_arc_fg, &arc_fg_st);
    lv_obj_set_pos(bat_arc_fg, x, y);
    lv_obj_set_size(bat_arc_fg, w, w);
    lv_arc_set_angles(bat_arc_fg, 315, 315);

    bat_val = lv_label_create(bat_arc_fg, NULL);
    lv_obj_set_auto_realign(bat_val, true);
    lv_obj_set_style(bat_val, &arc_fg_st);
    lv_obj_align_origo(bat_val, bat_arc_fg, LV_ALIGN_CENTER, 0, 0);

    bat_txt = lv_label_create(lv_scr_act(), NULL);
    lv_obj_set_style(bat_txt, &txt_st);
    lv_label_set_text(bat_txt, "Battery");
    lv_obj_align_origo(bat_txt, bat_arc_fg, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);

  }

  virtual void main()
  {
    int p = get_battery_percent();
    // int v = (int)(lv_arc_get_angle_end(bat_arc_bg) - ((((float)lv_arc_get_angle_end(bat_arc_bg) - (float)lv_arc_get_angle_start(bat_arc_bg)) / 100) * p));
    lv_arc_set_angles(bat_arc_fg, get_arc_value(p, lv_arc_get_angle_start(bat_arc_bg), lv_arc_get_angle_end(bat_arc_bg), 100), lv_arc_get_angle_end(bat_arc_bg));
    lv_label_set_text_fmt(bat_val, "%i%%", p);
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
  lv_obj_t *bat_arc_bg, *bat_arc_fg, *bat_val, *bat_txt;
  lv_style_t arc_bg_st, arc_fg_st, txt_st;
  lv_coord_t x, y, w;

  int get_arc_value(int source, int start, int end, int scale)
  {
    return (int)(end - ((((float)end - (float)start) / scale) * source));
  }
};

WidgetsScreen widgetsScreen;
