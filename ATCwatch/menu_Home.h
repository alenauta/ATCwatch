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
#include "accl.h"
#include "push.h"
#include "heartrate.h"
#include "fonts.h"
#include "sleep.h"
#include <lvgl.h>
#include <TimeLib.h>

class HomeScreen : public Screen
{
public:
  virtual void pre()
  {
    start_accl();

    time_data = get_time();

    lv_style_copy(&st, &lv_style_plain);
    st.text.color = lv_color_hex(0x1acc10);
    st.text.font = &sharetech60;

    // TIME
    label_hours = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text_fmt(label_hours, "%02i", time_data.hr);
    lv_obj_set_style(label_hours, &st);
    lv_obj_align(label_hours, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 0, 30);
    label_mins = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text_fmt(label_mins, "%02i", time_data.min);
    lv_obj_set_style(label_mins, &st);
    lv_obj_align(label_mins, label_hours, LV_ALIGN_OUT_RIGHT_TOP, 0, 0);

    lv_style_copy(&st_m, &lv_style_plain);
    st_m.text.color = lv_color_hex(0x1acc10);
    // st_m.text.font = &sharetech16;

    // WEEKDAY
    label_weekday = lv_label_create(lv_scr_act(), NULL);
    lv_obj_set_style(label_weekday, &st_m);
    lv_obj_align(label_weekday, label_mins, LV_ALIGN_OUT_RIGHT_TOP, 0, 0);

    // DATE
    label_date = lv_label_create(lv_scr_act(), NULL);
    lv_obj_set_style(label_date, &st_m);
    lv_obj_align(label_date, label_weekday, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

    // BATTERY
    label_battery = lv_label_create(lv_scr_act(), NULL);
    // lv_obj_set_event_cb(label_battery, lv_event_handler);
    lv_obj_align(label_battery, lv_scr_act(), LV_ALIGN_IN_TOP_RIGHT, -10, 5);

    lv_style_copy(&style_battery, lv_label_get_style(label_battery, LV_LABEL_STYLE_MAIN));
    // style_battery.text.color = lv_color_hsv_to_rgb(10, 5, 95);
    style_battery.text.color = lv_color_hex(0x1acc10);
    style_battery.text.font = LV_FONT_DEFAULT;
    lv_obj_set_style(label_battery, &style_battery);

    label_charge = lv_label_create(lv_scr_act(), NULL);
    lv_obj_align(label_charge, label_battery, LV_ALIGN_OUT_RIGHT_TOP, 0, 0);
    lv_obj_set_style(label_charge, &style_battery);

    // BLE
    label_ble = lv_label_create(lv_scr_act(), NULL);
    lv_obj_align(label_ble, lv_scr_act(), LV_ALIGN_IN_TOP_LEFT, 5, 5);
    lv_label_set_text(label_ble, LV_SYMBOL_BLUETOOTH);

    lv_style_copy(&style_ble, lv_label_get_style(label_ble, LV_LABEL_STYLE_MAIN));
    style_ble.text.color = LV_COLOR_GRAY;
    style_ble.text.font = LV_FONT_DEFAULT;
    lv_obj_set_style(label_ble, &style_ble);

    // LOOK
    label_look = lv_label_create(lv_scr_act(), NULL);
    lv_obj_align(label_look, label_ble, LV_ALIGN_OUT_RIGHT_TOP, 5, 0);

    lv_style_copy(&style_look, lv_label_get_style(label_look, LV_LABEL_STYLE_MAIN));
    style_look.text.color = lv_color_hex(0x1acc10);
    style_look.text.font = LV_FONT_DEFAULT;
    lv_obj_set_style(label_look, &style_look);

    // HEART
    // img_heart = lv_img_create(lv_scr_act(), NULL);
    // lv_img_set_src(img_heart, &IsymbolHeartSmall);
    // lv_obj_align(img_heart, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, -34);

    // label_heart = lv_label_create(lv_scr_act(), NULL);
    // lv_obj_set_width(label_heart, 240);
    // lv_label_set_text_fmt(label_heart, "%i", get_last_heartrate());
    // lv_obj_align(label_heart, img_heart, LV_ALIGN_OUT_RIGHT_MID, 2, 0);

    // // STEPS
    // img_steps = lv_img_create(lv_scr_act(), NULL);
    // lv_img_set_src(img_steps, &IsymbolStepsSmall);
    // lv_obj_align(img_steps, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 120, -34);

    // label_steps = lv_label_create(lv_scr_act(), NULL);
    // lv_obj_set_width(label_steps, 240);
    // lv_label_set_text_fmt(label_steps, "%i", time_data.weekday);
    // lv_obj_align(label_steps, img_steps, LV_ALIGN_OUT_RIGHT_MID, 2, 0);

    // MESSAGE
    img_msg = lv_img_create(lv_scr_act(), NULL);
    lv_img_set_src(img_msg, &IsymbolMsgSmall);
    lv_obj_align(img_msg, NULL, LV_ALIGN_IN_BOTTOM_LEFT, 0, -8);

    label_msg = lv_label_create(lv_scr_act(), NULL);

    lv_style_copy(&style_msg, lv_label_get_style(label_ble, LV_LABEL_STYLE_MAIN));
    style_msg.text.color = lv_color_hex(0x1acc10);
    // style_msg.text.font = &sans_regular;
    lv_obj_set_style(label_msg, &style_msg);

    lv_obj_set_width(label_msg, 240);
    lv_label_set_text(label_msg, " ");
    lv_label_set_text(label_msg, string2char(get_push_msg(30)));
    lv_obj_align(label_msg, img_msg, LV_ALIGN_OUT_RIGHT_MID, 2, 0);
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

    // lv_label_set_text_fmt(label_battery, "%i%%", get_battery_percent());
    set_battery_icon();

    // lv_label_set_text_fmt(label_heart, "%i", get_last_heartrate());
    // lv_label_set_text_fmt(label_steps, "%s", monthStr(time_data.month));

    if (get_is_looked_at() && get_charge()) // is looked at and is not charging
      lv_label_set_text(label_look, LV_SYMBOL_EYE_OPEN);
    else
      lv_label_set_text(label_look, " ");

    if (get_vars_ble_connected())
      style_ble.text.color = lv_color_hex(0x0082FC);
      // style_ble.text.color = LV_COLOR_RED;
    else
      style_ble.text.color = LV_COLOR_GRAY;
    lv_obj_set_style(label_ble, &style_ble);

    // if (get_charge())
    //   style_battery.text.color = lv_color_hsv_to_rgb(10, 5, 95);
    // else
    //   style_battery.text.color = LV_COLOR_MAKE(0x05, 0xF9, 0x25);
    // lv_obj_set_style(label_battery, &style_battery);
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
    display_widgets();
  }

  virtual void right()
  {
  }

  virtual void button_push(int length)
  {
    sleep_down();
  }

  // virtual void lv_event_class(lv_obj_t * object, lv_event_t event)
  //   {
  //     if (object == label_battery && event == LV_EVENT_SHORT_CLICKED) {
  //       lv_label_set_text(label_msg, "CLICK");
  //       display_charging();
  //     }
  //   }

private:
  time_data_struct time_data;
  lv_style_t st, st_m;
  lv_obj_t *label, *label_heart, *label_steps, *label_msg;
  lv_obj_t *label_hours, *label_mins, *label_date, *label_weekday;
  lv_obj_t *label_ble, *label_battery, *label_charge, *label_look;
  lv_style_t style_ble, style_battery, style_msg, style_look;
  lv_obj_t *img_heart, *img_steps, *img_msg;

  char *string2char(String command)
  {
    if (command.length() != 0)
    {
      char *p = const_cast<char *>(command.c_str());
      return p;
    }
  }

  void set_battery_icon()
  {
    if (!get_charge())
      lv_label_set_text(label_charge, LV_SYMBOL_CHARGE);
    else
      lv_label_set_text(label_charge, " ");
    {
      switch (get_battery_percent())
      {
      case 90 ... 100:
        lv_label_set_text(label_battery, LV_SYMBOL_BATTERY_FULL);
        break;
      case 70 ... 89:
        lv_label_set_text(label_battery, LV_SYMBOL_BATTERY_3);
        break;
      case 45 ... 69:
        lv_label_set_text(label_battery, LV_SYMBOL_BATTERY_2);
        break;
      case 15 ... 44:
        lv_label_set_text(label_battery, LV_SYMBOL_BATTERY_1);
        break;
      case 0 ... 14:
        lv_label_set_text(label_battery, LV_SYMBOL_BATTERY_EMPTY);
        break;
      }
    }
  }
};

HomeScreen homeScreen;
