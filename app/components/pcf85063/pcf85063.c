/**
 * @file       pcf85063.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-11-05
 * @author     Hiep Le
 * @brief      Driver support RTC chip (PCF85063)
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "pcf85063.h"

/* Private defines ---------------------------------------------------- */
#define PCF85063_REG_CONTROL_1        (0X00)
#define PCF85063_REG_CONTROL_2        (0X01)
#define PCF85063_REG_OFFSET           (0X02)
#define PCF85063_REG_RAM_BYTE         (0X03)
#define PCF85063_REG_SECONDS          (0X04)
#define PCF85063_REG_MINUTES          (0X05)
#define PCF85063_REG_HOURS            (0X06)
#define PCF85063_REG_DAYS             (0X07)
#define PCF85063_REG_WEEKDAYS         (0X08)
#define PCF85063_REG_MONTHS           (0X09)
#define PCF85063_REG_YEARS            (0X0A)
#define PCF85063_REG_SECOND_ALARM     (0X0B)
#define PCF85063_REG_MINUTE_ALARM     (0X0C)
#define PCF85063_REG_HOUR_ALARM       (0X0D)
#define PCF85063_REG_DAY_ALARM        (0X0E)
#define PCF85063_REG_WEEKDAY_ALARM    (0X0F)
#define PCF85063_REG_TIMER_VALUE      (0X10)
#define PCF85063_REG_TIMER_MODE       (0X11)

/* Private macros ----------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
static uint8_t m_pcf85063_bin_to_bcd(uint8_t val);
static uint8_t m_pcf85063_bcd_to_bin(uint8_t val);
static base_status_t m_pcf85063_write_reg(pcf85063_t *me, uint8_t reg, uint8_t *p_data, uint32_t len);
static base_status_t m_pcf85063_read_reg(pcf85063_t *me, uint8_t reg, uint8_t *p_data, uint32_t len);

/* Function definitions ----------------------------------------------- */
base_status_t pcf85063_init(pcf85063_t *me)
{
  uint8_t days;

  if ((me == NULL) || (me->i2c_read == NULL) || (me->i2c_write == NULL))
    return BS_ERROR;

  CHECK_STATUS(m_pcf85063_read_reg(me, PCF85063_REG_DAYS, &days, 1)); // Read data at time days register

  days = m_pcf85063_bcd_to_bin(days & 0x3F);

  if ((days < 1) || (days > 31))  // Check days value
    return BS_ERROR;

  return BS_OK;
}

base_status_t pcf85063_stop_clock(pcf85063_t *me)
{
  uint8_t tmp;

  CHECK_STATUS(m_pcf85063_read_reg(me, PCF85063_REG_CONTROL_1, &tmp, 1));

  tmp |= 0x20;

  CHECK_STATUS(m_pcf85063_write_reg(me, PCF85063_REG_CONTROL_1, &tmp, 1));

  return BS_OK;
}

base_status_t pcf85063_start_clock(pcf85063_t *me)
{
  uint8_t tmp;

  CHECK_STATUS(m_pcf85063_read_reg(me, PCF85063_REG_CONTROL_1, &tmp, 1));

  tmp &= ~0x20;

  CHECK_STATUS(m_pcf85063_write_reg(me, PCF85063_REG_CONTROL_1, &tmp, 1));

  return BS_OK;
}

base_status_t pcf85063_set_time(pcf85063_t *me, uint64_t epoch_time)
{
  uint8_t tmp[7];
  time_t t;
  struct tm *htime;

  t = (time_t)epoch_time;

  htime = localtime(&t);

  CHECK_STATUS(pcf85063_stop_clock(me)); // Stop RTC

  tmp[0] = m_pcf85063_bin_to_bcd(htime->tm_sec) & 0x7F;
  tmp[1] = m_pcf85063_bin_to_bcd(htime->tm_min);
  tmp[2] = m_pcf85063_bin_to_bcd(htime->tm_hour);
  tmp[3] = m_pcf85063_bin_to_bcd(htime->tm_mday);
  tmp[4] =                      (htime->tm_wday & 0x07);
  tmp[5] = m_pcf85063_bin_to_bcd(htime->tm_mon + 1);
  tmp[6] = m_pcf85063_bin_to_bcd(htime->tm_year - 100);

  CHECK_STATUS(m_pcf85063_write_reg(me, PCF85063_REG_SECONDS, tmp, sizeof(tmp)));

  CHECK_STATUS(pcf85063_start_clock(me)); // Start RTC

  return BS_OK;
}

base_status_t pcf85063_get_time(pcf85063_t *me, uint64_t *epoch_time)
{
  uint8_t tmp[7];
  struct tm *htime = {0};
  
  CHECK_STATUS(m_pcf85063_read_reg(me, PCF85063_REG_SECONDS, tmp, sizeof(tmp)));

  htime->tm_sec  = m_pcf85063_bcd_to_bin(tmp[0] & 0x7F);
  htime->tm_min  = m_pcf85063_bcd_to_bin(tmp[1] & 0x7F);
  htime->tm_hour = m_pcf85063_bcd_to_bin(tmp[2] & 0x3F);        // RTC hr 0-23
  htime->tm_mday = m_pcf85063_bcd_to_bin(tmp[3] & 0x3F);
  htime->tm_wday =                      (tmp[4] & 0x07);
  htime->tm_mon  = m_pcf85063_bcd_to_bin(tmp[5] & 0x1F) - 1;    // RTC mn 1-12
  htime->tm_year = m_pcf85063_bcd_to_bin(tmp[6] & 0xFF) + 100;  // Adjust for 1900 base of rtc_time

  *epoch_time = (uint64_t)(mktime(htime));

  return BS_OK;
}

/* Private function definitions ---------------------------------------- */
/**
 * @brief         Binary to BCD converter
 *
 * @param[in]     val     Binary value
 *
 * @attention     None
 * 
 * @return        BCD value
 */
static uint8_t m_pcf85063_bin_to_bcd(uint8_t val)
{
  return (((val / 10) << 4) + (val % 10));
}

/**
 * @brief         BCD to Binary converter
 *
 * @param[in]     val     BCD value
 *
 * @attention     None
 * 
 * @return        Binary value
 */
static uint8_t m_pcf85063_bcd_to_bin(uint8_t val)
{
  return ((val & 0x0F) + (val >> 4) * 10);
}

/**
 * @brief         PCF85063 write register
 *
 * @param[in]     me      Pointer to handle of DRV10975 module.
 * @param[in]     reg     Register
 * @param[in]     p_data  Pointer to handle of data
 * @param[in]     len     Data length
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
static base_status_t m_pcf85063_write_reg(pcf85063_t *me, uint8_t reg, uint8_t *p_data, uint32_t len)
{
  CHECK(0 == me->i2c_write(me->device_address, reg, p_data, len), BS_ERROR);

  return BS_OK;
}

/**
 * @brief         PCF85063 read register
 *
 * @param[in]     me      Pointer to handle of DRV10975 module.
 * @param[in]     reg     Register
 * @param[in]     p_data  Pointer to handle of data
 * @param[in]     len     Data length
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
static base_status_t m_pcf85063_read_reg(pcf85063_t *me, uint8_t reg, uint8_t *p_data, uint32_t len)
{
  CHECK(0 == me->i2c_read(me->device_address, reg, p_data, len), BS_ERROR);

  return BS_OK;
}

/* End of file -------------------------------------------------------- */
