/**
 * @file       bsp_pm.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-10-07
 * @author     Hiep Le
 * @brief      Board support package for Multi Channel Power Monitor (PAC1934)
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_pm.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static pac1934_t m_pac1934;

/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
base_status_t bsp_pm_init(void)
{
  m_pac1934.device_address        = PAC1934_I2C_ADDR;
  m_pac1934.i2c_read              = bsp_i2c_read;
  m_pac1934.i2c_write             = bsp_i2c_write;
  m_pac1934.delay_ms              = bsp_delay_ms;

  m_pac1934.config.sample_rate    = PAC1934_SAMPLE_RATE_1000HZ;
  m_pac1934.config.sleep_mode_bit = 0; // 1: Sleep mode, 0: Normal mode

  CHECK_STATUS(pac1934_init(&m_pac1934));

  return BS_OK;
}

base_status_t bsp_pm_voltage_measurement(pac1934_channel_t channel)
{
  CHECK_STATUS(pac1934_voltage_measurement(&m_pac1934, channel));

  return BS_OK;
}

base_status_t bsp_pm_current_measurement(pac1934_channel_t channel)
{
  CHECK_STATUS(pac1934_current_measurement(&m_pac1934, channel));

  return BS_OK;
}

base_status_t bsp_pm_power_measurement(pac1934_channel_t channel)
{
  CHECK_STATUS(pac1934_power_measurement(&m_pac1934, channel));

  return BS_OK;
}

base_status_t bsp_pm_into_sleep_mode(void)
{
  CHECK_STATUS(pac1934_into_sleep_mode(&m_pac1934));

  return BS_OK;
}

base_status_t bsp_pm_into_normal_mode(void)
{
  CHECK_STATUS(pac1934_into_normal_mode(&m_pac1934));

  return BS_OK;
}

/* Private function definitions ---------------------------------------- */
/* End of file -------------------------------------------------------- */