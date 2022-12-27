/*
 * Copyright (c) 2020 Aaron Christophel
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "flash.h"
#include "pinout.h"
#include "fast_spi.h"

#define SPIFLASH_PAGE_WRITE 0x02   // Page Program (up to 256 bytes)
#define SPIFLASH_READ 0x03         // Read Data
#define SPIFLASH_READ_STATUS 0x05  // Read Status Register
#define SPIFLASH_WRITE_ENABLE 0x06 // Write Enable
#define SPIFLASH_SECTOR_ERASE 0x20 // SubSector (4K bytes) Erase
// #define SPIFLASH_SECTOR_ERASE 0xD8    // Sector (usually 64K bytes) Erase
#define SPIFLASH_RDP 0xAB        // Release from Deep Power Down
#define SPIFLASH_DP 0xB9         // Deep Power Down
#define SPIFLASH_MASS_ERASE 0xC7 // Erase entire flash.
#define SPIFLASH_PAGE_ERASE 0x81 // Erase the page.
#define SPIFLASH_IDREAD 0x9F
#define SPIFLASH_MACREAD 0x4B

bool flash_sleeping = false;

uint8_t temp[8];
uint8_t resp[8];
uint8_t sr[1];

void init_flash()
{
  pinMode(SPI_CE, OUTPUT);
  digitalWrite(SPI_CE, HIGH);
  flash_sleep(true);
}

void flash_sleep(int state)
{
  startWrite_flash();
  delay(10);
  if (state)
  {
    temp[0] = SPIFLASH_DP;
    write_fast_spi(temp, 1);
  }
  else
  {
    do
    {
      temp[0] = SPIFLASH_RDP;
      temp[1] = 0x01;
      temp[2] = 0x20;
      temp[3] = 0x30;
      write_fast_spi(temp, 4);
      read_fast_spi(temp, 3);
    } while (temp[0] != 0x15 && temp[1] != 0x15 && temp[2] != 0x15);
  }
  endWrite_flash();
  flash_sleeping = state;
}

uint8_t flash_read_sr()
{
  if (flash_sleeping)
    flash_sleep(false);
  startWrite_flash();
  temp[0] = 0x05;
  write_fast_spi(temp, 1);
  read_fast_spi(sr, 1);
  endWrite_flash();
  flash_sleep(true);
  // delay(250);
  // return (temp[0] << 8 | temp[1]);
  return sr[0];
}

uint16_t flash_read_id()
{
  if (flash_sleeping)
    flash_sleep(false);
  startWrite_flash();
  temp[0] = SPIFLASH_IDREAD;
  write_fast_spi(temp, 1);
  read_fast_spi(temp, 2);
  endWrite_flash();
  flash_sleep(true);
  return (temp[0] << 8 | temp[1]);
}

void sector_erase(uint8_t block, uint8_t sector)
{
  if (flash_sleeping)
    flash_sleep(false);
  startWrite_flash();
  temp[0] = SPIFLASH_WRITE_ENABLE;
  write_fast_spi(temp, 1);
  endWrite_flash();
  startWrite_flash();
  temp[0] = SPIFLASH_SECTOR_ERASE;
  temp[1] = block;
  temp[2] = sector;
  temp[3] = 0xAA;
  write_fast_spi(temp, 4);
  endWrite_flash();
  flash_sleep(true);
}

void flash_read_test(uint8_t block, uint8_t page, uint8_t byte)
{
  if (flash_sleeping)
    flash_sleep(false);
  // temp[7] = flash_read_sr();
  startWrite_flash();
  temp[0] = SPIFLASH_READ;
  temp[1] = block;
  temp[2] = page;
  temp[3] = byte;
  write_fast_spi(temp, 4);
  read_fast_spi(resp, 8);
  endWrite_flash();
  flash_sleep(true);
}

void flash_write_test(uint8_t block, uint8_t page, uint8_t byte, uint8_t value)
{
  if (flash_sleeping)
    flash_sleep(false);
  startWrite_flash();
  temp[0] = SPIFLASH_WRITE_ENABLE;
  write_fast_spi(temp, 1);
  endWrite_flash();
  startWrite_flash();
  temp[0] = SPIFLASH_PAGE_WRITE;
  temp[1] = block;
  temp[2] = page;
  temp[3] = byte;
  write_fast_spi(temp, 4);
  temp[0] = value;
  temp[1] = value;
  temp[2] = value;
  temp[3] = value;
  write_fast_spi(temp, 4);
  endWrite_flash();
  flash_sleep(true);
  flash_read_test(block, page, byte);
}

void get_temp(uint8_t *ptr)
{
  ptr[0] = temp[0];
  ptr[1] = temp[1];
  ptr[2] = temp[2];
  ptr[3] = temp[3];
  ptr[4] = temp[4];
  ptr[5] = temp[5];
  ptr[6] = temp[6];
  ptr[7] = temp[7];
}

void get_resp(uint8_t *ptr)
{
  ptr[0] = resp[0];
  ptr[1] = resp[1];
  ptr[2] = resp[2];
  ptr[3] = resp[3];
  ptr[4] = resp[4];
  ptr[5] = resp[5];
  ptr[6] = resp[6];
  ptr[7] = resp[7];
}

void startWrite_flash(void)
{
  enable_spi(true);
  digitalWrite(SPI_CE, LOW);
}

void endWrite_flash(void)
{
  digitalWrite(SPI_CE, HIGH);
  enable_spi(false);
}

void flash_write(uint32_t addr, uint8_t buf[])
{
  if (flash_sleeping)
    flash_sleep(false);
  startWrite_flash();
  temp[0] = SPIFLASH_WRITE_ENABLE;
  write_fast_spi(temp, 1);
  endWrite_flash();
  startWrite_flash();
  temp[0] = SPIFLASH_PAGE_WRITE;
  temp[1] = (addr >> 16) & 0xFF;
  temp[2] = (addr >> 8) & 0xFF;
  temp[3] = addr & 0xFF;
  write_fast_spi(temp, 4);
  write_fast_spi(buf, sizeof(buf));
  endWrite_flash();
  flash_sleep(true);
}

void flash_read_page(uint32_t addr, uint8_t * read_buf)
{
  // uint8_t read_buf[256];
  if (flash_sleeping)
    flash_sleep(false);
  startWrite_flash();
  temp[0] = SPIFLASH_READ;
  temp[1] = (addr >> 16) & 0xFF;
  temp[2] = (addr >> 8) & 0xFF;
  temp[3] = addr & 0xFF;
  write_fast_spi(temp, 4);
  read_fast_spi(read_buf, 256);
  endWrite_flash();
  flash_sleep(true);
  // return read_buf;
}