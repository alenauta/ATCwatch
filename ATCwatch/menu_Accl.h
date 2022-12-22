/*
   Copyright (c) 2020 Aaron Christophel

   SPDX-License-Identifier: GPL-3.0-or-later
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
#include "screen_style.h"

class AcclScreen : public Screen
{
public:
  virtual void pre()
  {
    start_accl();

    label = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label, "Accelerometer Test");
    lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    label_x = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label_x, "X:");
    lv_obj_align(label_x, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 25);
    label_y = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label_y, "Y:");
    lv_obj_align(label_y, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 45);
    label_z = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text(label_z, "Z:");
    lv_obj_align(label_z, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 65);
    label_temp = lv_label_create(lv_scr_act(), NULL);
    lv_obj_align(label_temp, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 85);
  }

  virtual void main()
  {

    accl_data_struct data = get_accl_data();
    String look = (get_is_looked_at()) ? "YES\0" : "NO\0";

    lv_label_set_text_fmt(label_x, "X: %i", data.x);
    lv_label_set_text_fmt(label_y, "Y: %i", data.y);
    lv_label_set_text_fmt(label_z, "Z: %i", data.z);
    lv_label_set_text(label_temp, look.c_str());

    // lv_label_set_text_fmt(label_temp, "Temp: %g", tempC);
  }

  virtual void post()
  {
    end_accl();
  }

  virtual uint32_t sleepTime()
  {
    return 50000;
  }

  virtual void right()
  {
    set_last_menu();
  }

private:
  lv_obj_t *label, *label_x, *label_y, *label_z;
  lv_obj_t *label_temp, *label_steps, *label_activity;
};

AcclScreen acclScreen;
