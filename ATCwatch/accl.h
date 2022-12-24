#pragma once

#include "Arduino.h"

struct accl_data_struct {
  int16_t x;
  int16_t y;
  int16_t z;
  uint8_t temp;
};

bool init_accl();
void end_accl();
void start_accl();
bool get_is_looked_at();
accl_data_struct get_accl_data();
void update_accl_data();
