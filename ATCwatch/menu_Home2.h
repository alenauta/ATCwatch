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
// #include "fonts.h"
#include "sleep.h"
#include <lvgl.h>
#include <TimeLib.h>

class HomeScreen2 : public Screen
{
public:
    virtual void pre()
    {
        // ui_Screen1 = lv_obj_create(NULL);
        lv_obj_clear_flag(lv_scr_act(), LV_OBJ_FLAG_SCROLLABLE); /// Flags

        ui_labelHours = lv_label_create(lv_scr_act());
        lv_obj_set_width(ui_labelHours, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_labelHours, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_labelHours, -85);
        lv_obj_set_y(ui_labelHours, -55);
        lv_obj_set_align(ui_labelHours, LV_ALIGN_CENTER);
        lv_label_set_text(ui_labelHours, "12");
        lv_obj_set_style_text_color(ui_labelHours, lv_color_hex(0x31BC45), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui_labelHours, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(ui_labelHours, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);

        ui_labelMinutes = lv_label_create(lv_scr_act());
        lv_obj_set_width(ui_labelMinutes, LV_SIZE_CONTENT);  /// 1
        lv_obj_set_height(ui_labelMinutes, LV_SIZE_CONTENT); /// 1
        lv_obj_set_x(ui_labelMinutes, -30);
        lv_obj_set_y(ui_labelMinutes, -54);
        lv_obj_set_align(ui_labelMinutes, LV_ALIGN_CENTER);
        lv_label_set_text(ui_labelMinutes, "43");
        lv_obj_set_style_text_color(ui_labelMinutes, lv_color_hex(0x31BC45), LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_opa(ui_labelMinutes, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_text_font(ui_labelMinutes, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    virtual void main()
    {
        time_data = get_time();
        // accl_data = get_accl_data();

        lv_label_set_text_fmt(ui_labelHours, "%02i", time_data.hr);
        lv_label_set_text_fmt(ui_labelMinutes, "%02i", time_data.min);
        // lv_label_set_text_fmt(label_date, "%02i/%02i/%04i", time_data.day, time_data.month, time_data.year);
        // lv_label_set_text_fmt(label_weekday, "%s", dayStr(time_data.weekday));
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

        // if (get_vars_ble_connected())
        // lv_style_set_text_color(&st, LV_STATE_DEFAULT, LV_COLOR_RED);
        // else
        // lv_style_set_text_color(&st, LV_STATE_DEFAULT, LV_COLOR_GRAY);
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
    // lv_obj_t *ui_Screen1;
    lv_obj_t *ui_labelHours;
    lv_obj_t *ui_labelMinutes;
    static lv_style_t st, st_m;
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

HomeScreen2 homeScreen2;
