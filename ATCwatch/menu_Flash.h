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
#include "flash.h"
#include "heartrate.h"
#include "screen_style.h"

class FlashScreen : public Screen
{
public:
  virtual void pre()
  {

    flash_read_test(block, page, byte);

    label = lv_label_create(lv_scr_act(), NULL);
    // lv_label_set_text(label, "Flash");
    lv_obj_align(label, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 0);

    label_x = lv_label_create(lv_scr_act(), NULL);
    // lv_label_set_text(label_x, "0x0000000000000000");
    lv_obj_align(label_x, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 25);

    label_y = lv_label_create(lv_scr_act(), NULL);
    // lv_label_set_text_fmt(label_y, "0x%04X%", flash_read_bpr());
    lv_obj_align(label_y, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 45);

    label_read = lv_label_create(lv_scr_act(), NULL);
    lv_label_set_text_fmt(label_read, "ID 0x%04X", flash_read_id());
    lv_obj_align(label_read, NULL, LV_ALIGN_IN_TOP_LEFT, 10, 65);
  }

  virtual void main()
  {
    get_temp(temp);
    get_resp(resp);
    lv_label_set_text_fmt(label, "block %02X page %02X byte %02X", block, page, byte);
    lv_label_set_text_fmt(label_x, "resp %02X %02X %02X %02X %02X %02X %02X %02X", resp[0], resp[1], resp[2], resp[3], resp[4], resp[5], resp[6], resp[7]);
    lv_label_set_text_fmt(label_y, "temp %02X %02X %02X %02X %02X %02X %02X %02X", temp[0], temp[1], temp[2], temp[3], temp[4], temp[5], temp[6], temp[7]);
  }

  virtual void click(touch_data_struct touch_data)
  {
    value = 0x77;
    flash_write_test(block, page, byte, value);
  }

  virtual void left()
  {
    sector_erase(block, page);
  }

  virtual void right()
  {
    set_last_menu();
  }

  virtual void up()
  {
    // startRead_flash();
    byte += 8;
    flash_read_test(block, page, byte);
    // endRead_flash();
    // flash_sleep(true);
  }

  virtual void down()
  {
    // if (addr > 0x00)
    byte -= 8;
    flash_read_test(block, page, byte);
    // flash_sleep(false);
  }

private:
  uint8_t temp[8];
  uint8_t resp[8];
  uint8_t block = 0x01;
  uint8_t page = 0x00;
  uint8_t byte = 0x00;
  uint8_t value = 0x00;
  lv_obj_t *label, *label_x, *label_y, *label_read;
};

FlashScreen flashScreen;
