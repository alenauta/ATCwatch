/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Arduino.h"
#include <lvgl.h>

lv_color_t color_list[] = {lv_color_hsv_to_rgb(10, 5, 95), LV_COLOR_GRAY, LV_COLOR_BLACK, LV_COLOR_RED, LV_COLOR_GREEN, LV_COLOR_BLUE};

int main_color_save = 2;
int grad_color_save = 2;
int font_color_save = 0;

void set_gray_screen_style(lv_font_t *font = LV_FONT_DEFAULT)
{
  static lv_style_t style_screen;
  // lv_style_copy(&style_screen, &lv_style_plain);
  lv_style_init(&style_screen);
  // style_screen.body.main_color = color_list[main_color_save];// LV_COLOR_GREEN;
  // style_screen.body.grad_color = color_list[grad_color_save];//LV_COLOR_BLUE;
  // style_screen.text.color = color_list[font_color_save];
  // style_screen.text.font = font;
  lv_style_set_bg_color(&style_screen, LV_STATE_DEFAULT, color_list[main_color_save]);
  lv_style_set_bg_grad_color(&style_screen, LV_STATE_DEFAULT, color_list[grad_color_save]);
  lv_style_set_text_color(&style_screen, LV_STATE_DEFAULT, color_list[font_color_save]);
  lv_style_set_text_font(&style_screen, LV_STATE_DEFAULT, font);
  lv_obj_add_style(lv_scr_act(), LV_OBJ_PART_MAIN, &style_screen);
}

void set_main_color(int new_color)
{
  main_color_save = new_color;
}

void set_grad_color(int new_color)
{
  grad_color_save = new_color;
}

void set_font_color(int new_color)
{
  font_color_save = new_color;
}

int get_main_color()
{
  return main_color_save;
}

int get_grad_color()
{
  return grad_color_save;
}

int get_font_color()
{
  return font_color_save;
}
