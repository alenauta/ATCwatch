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
#include "inputoutput.h"
#include "display.h"
#include "ble.h"
#include "time.h"
#include "battery.h"
// #include "accl.h"
#include "push.h"
#include "heartrate.h"
// #include "fonts.h"
#include "sleep.h"
#include <lvgl.h>
#include <TimeLib.h>

class HomeScreen2 : public Screen
{
public:
  virtual void pre()
  {
    time_data = get_time();
    // accl_data = get_accl_data();

    static lv_style_t st, st_m;
    lv_style_init(&st);
    lv_style_init(&st_m);
    // lv_style_copy(&st, &lv_style_plain);
    // st = lv.style_t();
    // st.text.color = lv_color_hex(0x1acc10);
    // st.text.font = &mksd90;
    lv_style_set_text_font(&st, &lv_font_montserrat_48);

    // TIME
    label_hours = lv_label_create(lv_scr_act());
    lv_label_set_text_fmt(label_hours, "%02i", time_data.hr);
    lv_obj_add_style(label_hours, &st, 0);
    lv_obj_align(label_hours, LV_ALIGN_TOP_MID, 0, 30);
    label_mins = lv_label_create(lv_scr_act());
    lv_label_set_text_fmt(label_mins, "%02i", time_data.min);
    lv_obj_add_style(label_mins, &st, 0);
    lv_obj_align_to(label_mins, label_hours, LV_ALIGN_OUT_RIGHT_TOP, 0, 0);

    // lv_style_copy(&st_m, &lv_style_plain);
    // st_m = lv.style_t();
    // st_m.text.color = lv_color_hex(0x1acc10);
    // st_m.text.font = LV_FONT_DEFAULT;
    lv_style_set_text_font(&st, LV_FONT_DEFAULT);

    // WEEKDAY
    label_weekday = lv_label_create(lv_scr_act());
    lv_obj_add_style(label_weekday, &st_m, 0);
    lv_obj_align_to(label_weekday, label_hours, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

    // DATE
    label_date = lv_label_create(lv_scr_act());
    lv_obj_add_style(label_date, &st_m, 0);
    lv_obj_align_to(label_date, label_weekday, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

    // BATTERY
    label_battery = lv_label_create(lv_scr_act());
    lv_obj_align(label_battery, LV_ALIGN_TOP_RIGHT, -10, 5);
    lv_label_set_text_fmt(label_battery, "%i%%", get_battery_percent());

    // lv_style_copy(&style_battery, lv_label_get_style(label_battery, LV_LABEL_STYLE_MAIN));
    // style_battery.text.color = lv_color_hsv_to_rgb(10, 5, 95);
    lv_obj_add_style(label_battery, &style_battery, 0);

    // BLE
    label_ble = lv_label_create(lv_scr_act());
    lv_obj_align(label_ble, LV_ALIGN_TOP_LEFT, 5, 5);
    lv_label_set_text(label_ble, LV_SYMBOL_BLUETOOTH);

    // lv_style_copy(&style_ble, lv_label_get_style(label_ble, LV_LABEL_STYLE_MAIN));
    // style_ble.text.color = LV_PALETTE_GREY;
    // style_ble.text.font = LV_FONT_DEFAULT;
    lv_style_set_text_font(&st, LV_FONT_DEFAULT);
    lv_obj_add_style(label_ble, &style_ble, 0);

    // HEART
    // img_heart = lv_img_create(lv_scr_act());
    // lv_img_set_src(img_heart, &IsymbolHeartSmall);
    // lv_obj_align(img_heart, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, -34);

    // label_heart = lv_label_create(lv_scr_act());
    // lv_obj_set_width(label_heart, 240);
    // lv_label_set_text_fmt(label_heart, "%i", get_last_heartrate());
    // lv_obj_align(label_heart, img_heart, LV_ALIGN_OUT_RIGHT_MID, 2, 0);

    // // STEPS
    // img_steps = lv_img_create(lv_scr_act());
    // lv_img_set_src(img_steps, &IsymbolStepsSmall);
    // lv_obj_align(img_steps, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 120, -34);

    // label_steps = lv_label_create(lv_scr_act());
    // lv_obj_set_width(label_steps, 240);
    // lv_label_set_text_fmt(label_steps, "%i", time_data.weekday);
    // lv_obj_align(label_steps, img_steps, LV_ALIGN_OUT_RIGHT_MID, 2, 0);

    // MESSAGE
    img_msg = lv_img_create(lv_scr_act());
    lv_img_set_src(img_msg, &IsymbolMsgSmall);
    lv_obj_align(img_msg, LV_ALIGN_BOTTOM_LEFT, 0, -8);

    label_msg = lv_label_create(lv_scr_act());

    // lv_style_copy(&style_msg, lv_label_get_style(label_ble, LV_LABEL_STYLE_MAIN));
    // style_msg.text.color = lv_color_hsv_to_rgb(10, 5, 95);
    // style_msg.text.font = &sans_regular;
    lv_style_set_text_font(&st, LV_FONT_DEFAULT);
    lv_obj_add_style(label_msg, &style_msg, 0);

    lv_obj_set_width(label_msg, 240);
    lv_label_set_text(label_msg, " ");
    lv_label_set_text(label_msg, string2char(get_push_msg(30)));
    lv_obj_align_to(label_msg, img_msg, LV_ALIGN_OUT_RIGHT_MID, 2, 0);
  }

  virtual void main()
  {
    time_data = get_time();
    // accl_data = get_accl_data();

    lv_label_set_text_fmt(label_hours, "%02i", time_data.hr);
    lv_label_set_text_fmt(label_mins, "%02i", time_data.min);
    lv_label_set_text_fmt(label_date, "%02i/%02i/%04i", time_data.day, time_data.month, time_data.year);
    lv_label_set_text_fmt(label_weekday, "%s", dayStr(time_data.weekday));
    // lv_obj_realign(label_date);
    // lv_obj_realign(label_weekday);

    lv_label_set_text_fmt(label_battery, "%i%%", get_battery_percent());

    // lv_label_set_text_fmt(label_heart, "%i", get_last_heartrate());
    // lv_label_set_text_fmt(label_steps, "%s", monthStr(time_data.month));

    // if (get_vars_ble_connected())
    // style_ble.text.color = lv_color_hex(0x0082FC);
    // style_ble.text.color = LV_PALETTE_BLUE;
    // else
    // style_ble.text.color = LV_PALETTE_GREY;
    // lv_obj_add_style(label_ble, &style_ble, 0);

    // if (get_charge())
    // style_battery.text.color = lv_color_hsv_to_rgb(10, 5, 95);
    // else
    // style_battery.text.color = LV_COLOR_MAKE(0x05, 0xF9, 0x25);
    // lv_obj_add_style(label_battery, &style_battery, 0);
  }

  virtual void up()
  {
    inc_vars_menu();
  }

  virtual void down()
  {
    dec_vars_menu();
  }

  virtual void left()
  {
  }

  virtual void right()
  {
  }

  virtual void button_push(int length)
  {
    sleep_down();
  }

private:
  time_data_struct time_data;
  // accl_data_struct accl_data;
  // static lv_style_t st, st_m;
  lv_obj_t *label, *label_heart, *label_steps, *label_msg;
  lv_obj_t *label_hours, *label_mins, *label_date, *label_weekday;
  lv_obj_t *label_ble, *label_battery;
  lv_style_t style_ble, style_battery, style_msg;
  lv_obj_t *img_heart, *img_steps, *img_msg;

  char *string2char(String command)
  {
    if (command.length() != 0)
    {
      char *p = const_cast<char *>(command.c_str());
      return p;
    }
  }
};

HomeScreen2 homeScreen2;
