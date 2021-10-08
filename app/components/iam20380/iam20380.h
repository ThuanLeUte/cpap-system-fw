/**
 * @file       iam20380.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-10-07
 * @author     Hiep Le
 * @brief      Driver support IAM20380 (Multi Channel Power Monitor)
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __IAM20380_H
#define __IAM20380_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "bsp.h"

/* Public defines ----------------------------------------------------- */
#define IAM20380_I2C_ADDR                       (0x11) // 7 Bits

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief IAM20380 data
 */
typedef struct
{
  short x;
  short y;
  short z;
}
iam20380_data_t;

/**
 * @brief IAM20380 sensor struct
 */
typedef struct 
{
  uint8_t  device_address;  // I2C device address

  // Read n-bytes from device's internal address <reg_addr> via I2C bus
  int (*i2c_read) (uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint32_t len);

  // Write n-bytes from device's internal address <reg_addr> via I2C bus
  int (*i2c_write) (uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint32_t len);

  // delay a time period in milisecond 
  int (*delay_ms) (uint32_t ms);
}
iam20380_t;

/* Public function prototypes ----------------------------------------- */
/**
 * @brief         IAM20380 init
 *
 * @param[in]     me      Pointer to handle of IAM20380 module.
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t iam20380_init(iam20380_t *me);

/**
 * @brief         IAM20380 init
 *
 * @param[in]     me            Pointer to handle of IAM20380 module.
 * @param[in]     channel       Channel number of IAM20380 module.
 * @param[in]     data          Voltage value of IAM20380 module..
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t iam20380_voltage_measurement(iam20380_t *me, iam20380_data_t *data, uint8_t channel)

/**
 * @brief         IAM20380 init
 *
 * @param[in]     me            Pointer to handle of IAM20380 module.
 * @param[in]     channel       Channel number of IAM20380 module.
 * @param[in]     data          Current value of IAM20380 module..
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t iam20380_current_measurement(iam20380_t *me, iam20380_data_t *data, uint8_t channel)

/**
 * @brief         IAM20380 init
 *
 * @param[in]     me            Pointer to handle of IAM20380 module.
 * @param[in]     channel       Channel number of IAM20380 module.
 * @param[in]     data          Power value of IAM20380 module..
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t iam20380_power_measurement(iam20380_t *me, iam20380_data_t *data, uint8_t channel)

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __IAM20380_H

/* End of file -------------------------------------------------------- */