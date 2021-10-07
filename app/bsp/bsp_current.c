/**
 * @file       bsp_current.c
 * @copyright  Copyright (C) 2020 HiepLe. All rights reserved.
 * @license    This project is released under the HiepLe License.
 * @version    1.0.0
 * @date       2021-10-07
 * @author     Hiep Le
 * @brief      Board support package for Multi Channel Power Monitor (PAC1934)
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_current.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static pac1934_t m_pac1934;

/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
base_status_t bsp_current_init(void)
{
  m_pac1934.device_address = PAC1934_I2C_ADDR;
  m_pac1934.i2c_read       = bsp_i2c_read;
  m_pac1934.i2c_write      = bsp_i2c_write;

  CHECK_STATUS(pac1934_init(&m_pac1934));

  return BS_OK;
}

base_status_t bsp_current_voltage_measurement(pac1934_data_t *voltage, uint8_t channel);
{
  CHECK_STATUS(pac1934_voltage_measurement(&m_pac1934, voltage, channel));

  return BS_OK;
}

base_status_t bsp_current_current_measurement(pac1934_data_t *current, uint8_t channel);
{
  CHECK_STATUS(pac1934_current_measurement(&m_pac1934, current, channel));

  return BS_OK;
}

base_status_t bsp_current_power_measurement(pac1934_data_t *power, uint8_t channel);
{
  CHECK_STATUS(pac1934_power_measurement(&m_pac1934, power, channel));

  return BS_OK;
}

/* Private function definitions ---------------------------------------- */
/* End of file -------------------------------------------------------- */