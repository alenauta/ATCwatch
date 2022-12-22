/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

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
#include "widgets.h"

class WidgetsScreen : public Screen
{
public:
  virtual void pre()
  {

    // lv_style_copy( &st, &lv_style_plain );
    //   st.text.color = lv_color_hsv_to_rgb(10, 5, 95);
    //   st.text.font = &sharetech60;

    //   label_battery_big = lv_label_create(lv_scr_act(), NULL);
    //   lv_obj_set_style( label_battery_big, &st );
    //   lv_label_set_text(label_battery_big, "---%");
    //   lv_obj_align(label_battery_big, lv_scr_act(), LV_ALIGN_CENTER, 0, -20);

    
    // lv_style_init(&arc_1_s0);
    lv_style_copy( &arc_bg_st, &lv_style_plain );
    // lv_style_set_bg_opa(&arc_1_s0, LV_STATE_DEFAULT, 0);
    // lv_style_set_border_opa(&arc_1_s0, LV_STATE_DEFAULT, 0);
    // lv_style_set_line_width(&arc_bg_st, LV_STATE_DEFAULT, 5);
    arc_bg_st.line.width = 5;
    arc_bg_st.line.rounded = true;

    // lv_style_init(&arc_1_s1);
    lv_style_copy( &arc_fg_st, &lv_style_plain );
    // lv_style_set_line_color(&arc_fg_st, LV_STATE_DEFAULT, lv_color_hex(0x2db710));
    arc_fg_st.line.color = lv_color_hex(0x2db710);
    // lv_style_set_line_width(&arc_fg_st, LV_STATE_DEFAULT, 5);
    arc_fg_st.line.width = 5;
    arc_fg_st.line.rounded = true;

    arc_bg = lv_arc_create(lv_scr_act(), NULL);
    // lv_obj_set_opa_scale_enable(arc_bg, true)
    lv_obj_set_style(arc_bg, &arc_bg_st);
    // lv_obj_add_style(arc_1, 1, &arc_1_s1);
    lv_obj_set_pos(arc_bg, 0, 0);
    lv_obj_set_size(arc_bg, 50, 50);
    lv_arc_set_angles(arc_bg, 45, 315);
    // lv_arc_set_rotation(arc_bg, 0);

    arc_fg = lv_arc_create(lv_scr_act(), NULL);
    // lv_obj_set_opa_scale_enable(arc_bg, true)
    lv_obj_set_style(arc_fg, &arc_fg_st);
    // lv_obj_add_style(arc_1, 1, &arc_1_s1);
    lv_obj_set_pos(arc_fg, 0, 0);
    lv_obj_set_size(arc_fg, 50, 50);
    lv_arc_set_angles(arc_fg, 135, 315);

    widgetArc arc1;
    arc1.create(lv_scr_act(), 120, 0, 60);

  }

  virtual void main()
  {
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
  lv_obj_t *arc_bg, *arc_fg;
  lv_style_t arc_bg_st, arc_fg_st;
  // lv_obj_t *label;
  // lv_obj_t *label_battery, *label_battery_big, *label_backlight_big;
  // lv_style_t style_battery, st;
};

WidgetsScreen widgetsScreen;
