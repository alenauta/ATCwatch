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
// #include "accl.h"
#include "push.h"
#include "inputoutput.h"
#include "heartrate.h"
#include "fonts.h"

class HeartScreen : public Screen
{
public:
  virtual void pre()
  {
    start_hrs3300();

    // static lv_style_t image_1_s0;
    heart = lv_img_create(lv_scr_act(), NULL);
    lv_obj_set_pos(heart, 10, 10);
    lv_img_set_src(heart, &heart1);

    lv_style_copy(&styleBIG, &lv_style_plain);
    lv_style_copy(&styleSMALL, &lv_style_plain);

    styleBIG.text.font = &sharetech90;
    label_hr = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_style(label_hr, LV_LABEL_STYLE_MAIN, &styleBIG);
    lv_label_set_text(label_hr, "--");
    lv_obj_set_pos(label_hr, 20, 90);


    styleSMALL.text.font = &sharetech22;
    label_2 = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_style(label_2, LV_LABEL_STYLE_MAIN, &styleSMALL);
    lv_label_set_text(label_2, "BPM");
    // lv_obj_set_pos(label_2, 100, 90);
    lv_obj_align(label_2, label_hr, LV_ALIGN_OUT_RIGHT_TOP, 0, 0);


    // styleSMALL.text.font = &lv_font_roboto_12;
    label_3 = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_style(label_3, LV_LABEL_STYLE_MAIN, &styleSMALL);
    lv_label_set_text(label_3, "LAST HR:");
    lv_obj_set_pos(label_3, 10, 179);


    // style.text.font = &lv_font_roboto_28;
    label_hr_last = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_style(label_hr_last, LV_LABEL_STYLE_MAIN, &styleSMALL);
    lv_label_set_text(label_hr_last, "--");
    lv_obj_set_pos(label_hr_last, 110, 179);
  }

  virtual void main()
  {
    byte hr = get_heartrate();
    switch (hr)
    {
    case 0:
    case 255:
      break;
    case 254:
      lv_label_set_text_fmt(label_hr, "NT"); // No Touch
      break;
    case 253:
      lv_label_set_text_fmt(label_hr, "**"); // Wait
      break;
    default:
      lv_label_set_text_fmt(label_hr, "%i", hr);
      break;
    }
    lv_label_set_text_fmt(label_hr_last, "%i", get_last_heartrate());
  }

  virtual void post()
  {
    end_hrs3300();
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
  // lv_obj_t *label, *label_hr, *label_hr_last;
  lv_obj_t *heart;
  lv_style_t styleBIG, styleSMALL;
  lv_obj_t *label_hr;
  lv_obj_t *label_1;
  lv_obj_t *label_2;
  lv_obj_t *label_3;
  lv_obj_t *label_hr_last;
};

HeartScreen heartScreen;
