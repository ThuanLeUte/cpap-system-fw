/**
 * @file       pcf85063.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-11-05
 * @author     Hiep Le
 * @brief      Driver support RTC driver (PCF85063)
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __PCF85063_H
#define __PCF85063_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "bsp.h"
#include <time.h>

/* Private defines ---------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Public defines ----------------------------------------------------- */
#define PCF85063_I2C_ADDR             (0x51 << 1) // I2C bus need 8 bits address

/* Public enumerate/structure ----------------------------------------- */
typedef struct
{
  uint8_t device_address; // I2C device address

  // Read n-bytes from device's internal address <reg_addr> via I2C bus
  int (*i2c_read) (uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint32_t len);

  // Write n-bytes from device's internal address <reg_addr> via I2C bus
  int (*i2c_write) (uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint32_t len);
}
pcf85063_t;

/* Public function prototypes ----------------------------------------- */
base_status_t pcf85063_init(pcf85063_t *me);
base_status_t pcf85063_stop_clock(pcf85063_t *me);
base_status_t pcf85063_start_clock(pcf85063_t *me);
base_status_t pcf85063_set_time(pcf85063_t *me, uint64_t epoch_time);
base_status_t pcf85063_get_time(pcf85063_t *me, uint64_t *epoch_time);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __PCF85063_H

/* End of file -------------------------------------------------------- */
