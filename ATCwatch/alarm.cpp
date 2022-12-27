#include "alarm.h"
#include "flash.h"

// #define ALARMBLOCK 0x01

static uint8_t alarms[256];
uint32_t alarms_addr = (0x01 << 16) + (0x00 << 8) + 0x00; // block 1, sector 0, page 0 choosen as alarms location

void init_alarm()
{
  reload_alarms();
}

void reload_alarms()
{
  // load the saved alarms from flash
  flash_read_page(alarms_addr, alarms);
}

void setAlarm(int h, int m)
{
  // uint32_t addr = (0x01 << 16) + (0x00 << 8) + 0x00;
  // uint8_t write_buf[3] = {0x00, data[0], data[1]};
  // uint8_t last_id = 0x00;
  for (int i = 0; i < 256; i = i + 8)
  {
    if (alarms[i] == 0xFF)
    {
      // uint8_t write_buf[3] = {last_id + 1, h, m};
      uint8_t write_buf[3] = {(int)(i/8)+ 1, h, m};
      flash_write(alarms_addr + i, write_buf);
      break;
    } 
    // else {
      // last_id = alarms[i];
    // }
  }
  reload_alarms();
}

void getAlarm(uint8_t id, uint8_t *alarm_data)
{
  // uint32_t addr = (0x01 << 16) + (0x00 << 8) + 0x00;
  // uint8_t *data;
  // flash_read(addr, 3, data);
  // return data;
  // uint8_t temp_page[256];
  // flash_read_page(alarms_addr, temp_page);
  for (int i = 0; i < 256; i = i + 8)
  {
    if (alarms[i] == id)
    {
      for (int j = 0; j < 8; j++)
      {
        alarm_data[j] = alarms[i + j];
      }
      break;
    }
  }
}