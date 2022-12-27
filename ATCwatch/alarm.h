#pragma once
#include "Arduino.h"

void init_alarm();
void reload_alarms();
void setAlarm(int h, int m);
void getAlarm(uint8_t id, uint8_t *alarm_data);