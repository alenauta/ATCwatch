/*
   Copyright (c) 2020 Aaron Christophel

   SPDX-License-Identifier: GPL-3.0-or-later
*/

#include "accl.h"
#include "accl_config.h"
#include "Arduino.h"
#include "i2c.h"
#include "pinout.h"
#include "watchdog.h"
#include "inputoutput.h"
#include "ble.h"
#include "sleep.h"
#include "SparkFun_LIS2DH12.h"

struct accl_data_struct accl_data;
SPARKFUN_LIS2DH12 accel;

bool init_accl()
{
  if (accel.begin() == false)
    return false;

  accel.setMode(LIS2DH12_LP_8bit);
  accel.setDataRate(LIS2DH12_ODR_1Hz);
  accel.setScale(LIS2DH12_2g);
  // accel.disableTemperature();

  end_accl();

  return true;
}

void end_accl()
{
  accel.setDataRate(LIS2DH12_POWER_DOWN); // Stop measurements
}

void start_accl()
{
  accel.setDataRate(LIS2DH12_ODR_1Hz);
}

bool get_is_looked_at()
{
  update_accl_data();
  if ((-75 <= accl_data.x && accl_data.x <= 60) && (-60 <= accl_data.y && accl_data.y <= 60) && accl_data.z < 10)
    return true;
  return false;
}

accl_data_struct get_accl_data()
{
  update_accl_data();
  return accl_data;
}

void update_accl_data()
{
  if (accel.available())
    {
      accl_data.x = (int)(accel.getX() / 10);
      accl_data.y = (int)(accel.getY() / 10);
      accl_data.z = (int)(accel.getZ() / 10);
    }
}

