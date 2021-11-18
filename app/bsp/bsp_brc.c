/**
 * @file       bsp_brc.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-10-14
 * @author     Hiep Le
 * @brief      Board support package for Brushless Motor (DRV10975)
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_brc.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static const char *TAG = "bsp_brc";
static drv10975_t m_drv10975;

/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
base_status_t bsp_brc_init(void)
{
  m_drv10975.device_address = DRV10975_I2C_ADDR;
  m_drv10975.i2c_read       = bsp_i2c_read;
  m_drv10975.i2c_write      = bsp_i2c_write;
  m_drv10975.delay_ms       = bsp_delay_ms;
  m_drv10975.gpio_write     = bsp_io_write;

  CHECK_STATUS(drv10975_init(&m_drv10975));

  return BS_OK;
}

void bsp_brc_power_on(void)
{
  bsp_io_write(IO_BRC_POWER, 1);
}

base_status_t bsp_brc_set_motor_direction(uint8_t dir)
{
  CHECK_STATUS(drv10975_set_motor_direction(&m_drv10975, dir));

  return BS_OK;
}

base_status_t bsp_brc_set_motor_speed(uint8_t percent_speed)
{
  CHECK_STATUS(drv10975_set_motor_speed(&m_drv10975, percent_speed));

  return BS_OK;
}

base_status_t bsp_brc_get_motor_velocity(void)
{
  CHECK_STATUS(drv10975_get_motor_velocity(&m_drv10975));

  return BS_OK;
}

base_status_t bsp_brc_get_motor_period(void)
{
  CHECK_STATUS(drv10975_get_motor_period(&m_drv10975));

  return BS_OK;
}

base_status_t bsp_brc_get_motor_supply_voltage(void)
{
  CHECK_STATUS(drv10975_get_motor_supply_voltage(&m_drv10975));

  return BS_OK;
}

base_status_t bsp_brc_get_motor_current(void)
{
  CHECK_STATUS(drv10975_get_motor_current(&m_drv10975));

  return BS_OK;
}

base_status_t bsp_brc_check_over_temp(void)
{
  CHECK_STATUS(drv10975_check_over_temp(&m_drv10975));

  return BS_OK;
}

base_status_t bsp_brc_check_sleep_mode(void)
{
  CHECK_STATUS(drv10975_check_sleep_mode(&m_drv10975));

  return BS_OK;
}

base_status_t bsp_brc_check_over_current(void)
{
  CHECK_STATUS(drv10975_check_over_current(&m_drv10975));

  return BS_OK;
}

base_status_t bsp_brc_check_motor_lock(void)
{
  CHECK_STATUS(drv10975_check_motor_lock(&m_drv10975));

  return BS_OK;
}

/* Private function definitions ---------------------------------------- */
/* End of file -------------------------------------------------------- */