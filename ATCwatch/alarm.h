#pragma once

#include "Arduino.h"

struct Alarm
{
    uint8_t id;
    uint8_t h;
    uint8_t m;
};

void setAlarm(uint8_t data[3]);
uint8_t *getAlarm(uint8_t id);