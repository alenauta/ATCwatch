#include "alarm.h"
#include "flash.h"

// #define ALARMBLOCK 0x01

// void setAlarm(struct Alarm a)
void setAlarm(uint8_t data[3])
{
  uint32_t addr = (0x01 << 16) + (0x00 << 8) + 0x00;
  // uint8_t data[3] = {a.id, a.h, a.m};
  flash_write(addr, data);
}

uint8_t *getAlarm(uint8_t id)
{
  uint32_t addr = (0x01 << 16) + (0x00 << 8) + 0x00;
  uint8_t *data;
  data = flash_read(addr, 3);
  return data;
}