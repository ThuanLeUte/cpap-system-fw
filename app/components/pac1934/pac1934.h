/**
 * @file       pac1934.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-10-07
 * @author     Hiep Le
 * @brief      Driver support PAC1934 (Multi Channel Power Monitor)
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __PAC1934_H
#define __PAC1934_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "bsp.h"

/* Public defines ----------------------------------------------------- */
#define PAC1934_I2C_ADDR                       (0x11) // 7 Bits

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief PAC1934 data
 */
typedef struct
{
  double	volt;            //Temporary variable used for voltage calculation
  double 	current;         //Temporary variable used for current calculation
  double 	power;           //Temporary variable used for power calculation
  double 	energy;          //Temporary variable used for energy calculation
}
pac1934_data_t;

/**
 * @brief PAC1934 sensor struct
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
pac1934_t;

/* Public function prototypes ----------------------------------------- */
/**
 * @brief         PAC1934 init
 *
 * @param[in]     me      Pointer to handle of PAC1934 module.
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t pac1934_init(pac1934_t *me);

/**
 * @brief         PAC1934 init
 *
 * @param[in]     me            Pointer to handle of PAC1934 module.
 * @param[in]     channel       Channel number of PAC1934 module.
 * @param[in]     data          Voltage value of PAC1934 module..
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t pac1934_voltage_measurement(pac1934_t *me, pac1934_data_t *data, uint8_t channel)

/**
 * @brief         PAC1934 init
 *
 * @param[in]     me            Pointer to handle of PAC1934 module.
 * @param[in]     channel       Channel number of PAC1934 module.
 * @param[in]     data          Current value of PAC1934 module..
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t pac1934_current_measurement(pac1934_t *me, pac1934_data_t *data, uint8_t channel)

/**
 * @brief         PAC1934 init
 *
 * @param[in]     me            Pointer to handle of PAC1934 module.
 * @param[in]     channel       Channel number of PAC1934 module.
 * @param[in]     data          Power value of PAC1934 module..
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t pac1934_power_measurement(pac1934_t *me, pac1934_data_t *data, uint8_t channel)

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __PAC1934_H

/* End of file -------------------------------------------------------- */