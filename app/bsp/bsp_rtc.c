/**
 * @file       bsp_rtc.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-11-05
 * @author     Hiep Le
 * @brief      Board support package for RTC driver (PCF85063)
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_rtc.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static const char *TAG = "bsp_rtc";
static pcf85063_t m_pcf85063;

/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
base_status_t bsp_rtc_init(void)
{
  m_pcf85063.device_address = PCF85063_I2C_ADDR;
  m_pcf85063.i2c_read       = bsp_i2c_read;
  m_pcf85063.i2c_write      = bsp_i2c_write;

  CHECK_STATUS(pcf85063_init(&m_pcf85063));

  return BS_OK;
}

base_status_t bsp_rtc_get_time(uint64_t *epoch_time)
{
  CHECK_STATUS(pcf85063_get_time(&m_pcf85063, epoch_time));

  return BS_OK;
}

base_status_t bsp_rtc_set_time(uint64_t epoch_time)
{
  CHECK_STATUS(pcf85063_set_time(&m_pcf85063, epoch_time));

  return BS_OK;
}

htime_t bsp_rtc_epoch_to_htime(uint64_t t)
{
  time_t mtime = (time_t)t;
  struct tm *htime;
  htime_t res;

  htime = localtime(&mtime);

  res.year  = (uint16_t)(htime->tm_year + 1900);
  res.month = (uint8_t)(htime->tm_mon + 1);
  res.day   = (uint8_t)(htime->tm_mday);
  res.hour  = (uint8_t)(htime->tm_hour);
  res.min   = (uint8_t)(htime->tm_min);
  res.sec   = (uint8_t)(htime->tm_sec);

  return res;
}

uint64_t bsp_rtc_htime_to_epoch(htime_t t)  
{
  struct tm htime = {0};

  htime.tm_year = t.year - 1900;
  htime.tm_mon  = t.month - 1;
  htime.tm_mday = t.day;
  htime.tm_hour = t.hour;
  htime.tm_min  = t.min;
  htime.tm_sec  = t.sec;

  return (uint64_t)mktime(&htime);
}

void bsp_rtc_realtime_synchronize(uint64_t epoch_time)
{
  uint64_t epoch_time_cvrt = 0;
  htime_t stime;

  bsp_rtc_set_time(epoch_time);
  // bsp_delay_ms(3000);
  bsp_rtc_get_time(&epoch_time_cvrt);
  ESP_LOGI(TAG, "Epoch Time: %li", (long int)epoch_time_cvrt);
  stime = bsp_rtc_epoch_to_htime(epoch_time_cvrt);
  ESP_LOGI(TAG, "Human date time: %d:%d:%d___%d/%d/%d", stime.hour, stime.min, stime.sec, stime.day, stime.month, stime.year);
}

void bsp_rtc_makestring_timestyle_1(char *out, time_t timestamp)
{
  time_t mtime = (time_t)timestamp;
  struct tm *htime;

  htime = localtime(&mtime);

  // strftime(out, 14, "%y%m%d:%H%M%S", htime);

  strftime(out, 100, "%d/%m/20%y-%H:%M:%S", htime);
}

/* Private function definitions ---------------------------------------- */
/* End of file -------------------------------------------------------- */