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
// #include "fonts.h"

class HeartScreen : public Screen
{
public:
  virtual void pre()
  {
    start_hrs3300();

    // static lv_style_t image_1_s0;
    heart = lv_img_create(lv_scr_act());
    lv_obj_set_pos(heart, 10, 10);
    lv_img_set_src(heart, &heart1);

    // lv_style_copy(&styleBIG, &lv_style_plain);
    // lv_style_copy(&styleSMALL, &lv_style_plain);

    // styleBIG = lv.style_t();
    // styleSMALL = lv.style_t();
    lv_style_init(&styleBIG);
    lv_style_init(&styleSMALL);

    // styleBIG.text.font = &mksd90;
    lv_style_set_text_font(&styleBIG, &lv_font_montserrat_48);

    label_hr = lv_label_create(lv_scr_act());
    // lv_label_set_style(label_hr, LV_LABEL_STYLE_MAIN, &styleBIG);
    lv_obj_add_style(label_hr, &styleBIG, 0);
    lv_label_set_text(label_hr, "--");
    lv_obj_set_pos(label_hr, 20, 90);

    // styleSMALL.text.font = &lv_font_roboto_22;
    lv_style_set_text_font(&styleSMALL, &lv_font_montserrat_22);

    label_2 = lv_label_create(lv_scr_act());
    // lv_label_set_style(label_2, LV_LABEL_STYLE_MAIN, &styleSMALL);
    lv_obj_add_style(label_2, &styleSMALL, 0);
    lv_label_set_text(label_2, "BPM");
    lv_obj_set_pos(label_2, 100, 90);

    // styleSMALL.text.font = &lv_font_roboto_12;
    label_3 = lv_label_create(lv_scr_act());
    // lv_label_set_style(label_3, LV_LABEL_STYLE_MAIN, &styleSMALL);
    lv_obj_add_style(label_3, &styleSMALL, 0);
    lv_label_set_text(label_3, "LAST HR:");
    lv_obj_set_pos(label_3, 10, 179);

    // style.text.font = &lv_font_roboto_28;
    label_hr_last = lv_label_create(lv_scr_act());
    // lv_label_set_style(label_hr_last, LV_LABEL_STYLE_MAIN, &styleSMALL);
    lv_obj_add_style(label_hr_last, &styleSMALL, 0);
    lv_label_set_text(label_hr_last, "00");
    lv_obj_set_pos(label_hr_last, 110, 179);

    // lv_obj_t *image_1 = lv_img_create(lv_scr_act());
    // lv_obj_set_pos(image_1, 10, 10);
    // lv_img_set_src(image_1, &heart1);
    // image_1_ev_0 = image_1;

    // // set_gray_screen_style(&lv_font_123abc_90);

    // lv_obj_t *label_1 = lv_label_create(lv_scr_act());
    // lv_label_set_text(label_1, "00");
    // lv_obj_set_pos(label_1, 10, 70);
    // label_1_ev_0 = label_1;

    // lv_obj_t *label_2 = lv_label_create(lv_scr_act());
    // lv_label_set_text(label_2, "BPM");
    // lv_obj_set_pos(label_2, 116, 90);
    // label_2_ev_0 = label_2;

    // lv_obj_t *label_3 = lv_label_create(lv_scr_act());
    // lv_label_set_text(label_3, "LAST HR:");
    // lv_obj_set_pos(label_3, 20, 179);
    // label_3_ev_0 = label_3;

    // lv_obj_t *label_4 = lv_label_create(lv_scr_act());
    // lv_label_set_text(label_4, "00");
    // lv_obj_set_pos(label_4, 95, 172);
    // label_4_ev_0 = label_4;

    // ################################
    //  label = lv_label_create(lv_scr_act());
    //  lv_label_set_text(label, "Heartrate");
    //  lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_LEFT, 0, 0);

    // set_gray_screen_style(&lv_font_roboto_28);

    // label_hr = lv_label_create(lv_scr_act());
    // lv_label_set_text(label_hr, "HR:");
    // lv_obj_align(label_hr, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 50);

    // label_hr_last = lv_label_create(lv_scr_act());
    // lv_label_set_text(label_hr_last, "Last HR:");
    // lv_obj_align(label_hr_last, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 80);

    // lv_obj_t *img1 = lv_img_create(lv_scr_act());
    // lv_img_set_src(img1, &IsymbolHeart);
    // lv_obj_align(img1, NULL, LV_ALIGN_IN_BOTTOM_MID, 0, 0);
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
      lv_label_set_text_fmt(label_hr, "--"); // No Touch
      break;
    case 253:
      lv_label_set_text_fmt(label_hr, "00"); // Wait
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
