/**
 * @file       bsp_gyro.c
 * @copyright  Copyright (C) 2020 HiepLe. All rights reserved.
 * @license    This project is released under the HiepLe License.
 * @version    1.0.0
 * @date       2021-10-08
 * @author     Hiep Le
 * @brief      Board support package for GyroScope (IAM20380)
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "bsp_gyro.h"

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static iam20380_t m_iam20380;

/* Private function prototypes ---------------------------------------- */
/* Function definitions ----------------------------------------------- */
base_status_t bsp_gyro_init(void)
{
  // Init
  m_iam20380.device_address               = IAM20380_I2C_ADDR;
  m_iam20380.i2c_read                     = bsp_i2c_read;
  m_iam20380.i2c_write                    = bsp_i2c_write;
  m_iam20380.delay_ms                     = bsp_delay_ms;
  // Configuration
  m_iam20380.config.sample_rate           = IAM20380_SAMPLE_RATE_500HZ;
  m_iam20380.config.digi_low_pass_filter  = IAM20380_DLPF4_NBW31;
  m_iam20380.config.fullscale             = IAM20380_FULLSCALE_2000_DPS;

  CHECK_STATUS(iam20380_init(&m_iam20380));

  return BS_OK;
}

base_status_t bsp_gyro_get_raw_data(void)
{
  CHECK_STATUS(iam20380_get_raw_data(&m_iam20380));

  return BS_OK;
}

base_status_t bsp_gyro_get_gyro_angle(void)
{
  CHECK_STATUS(iam20380_get_gyro_angle(&m_iam20380));

  return BS_OK;
}

base_status_t bsp_gyro_get_sensitivity(void)
{
  CHECK_STATUS(iam20380_get_sensitivity(&m_iam20380));

  return BS_OK; 
}

/* Private function definitions ---------------------------------------- */
/* End of file -------------------------------------------------------- */