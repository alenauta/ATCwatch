/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#pragma once

#include "Arduino.h"

void init_flash();
void flash_sleep(int state);
uint16_t flash_read_id();
uint8_t flash_read_sr();
void flash_read_test(uint8_t block, uint8_t page, uint8_t byte);
void flash_write_test(uint8_t block, uint8_t page, uint8_t byte, uint8_t value);
void sector_erase(uint8_t block, uint8_t page);
void get_temp(uint8_t *ptr);
void get_resp(uint8_t *ptr);
void startWrite_flash(void);
void endWrite_flash(void);
void flash_write(uint32_t addr, uint8_t buf[]);
void flash_read_page(uint32_t addr, uint8_t * read_buf);