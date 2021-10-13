/**
 * @file       drv10975.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-10-09
 * @author     Hiep Le
 * @brief      Driver support DRV10975 (Multi Channel Power Monitor)
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __DRV10975_H
#define __DRV10975_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "bsp.h"

/* Public defines ----------------------------------------------------- */
#define DRV10975_I2C_ADDR                       (0x52) // 7 Bits

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief DRV10975 motor value
 */
typedef struct
{
  uint16_t speed;    
  float frequency;
  float period;
  float current;
  float supply_voltage;
  float velocity;
}
drv10975_motor_value_t;

/**
 * @brief DRV10975 struct
 */
typedef struct 
{
  uint8_t device_address;  // I2C device address

  drv10975_motor_value_t value; // Motor value

  // Read n-bytes from device's internal address <reg_addr> via I2C bus
  int (*i2c_read) (uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint32_t len);

  // Write n-bytes from device's internal address <reg_addr> via I2C bus
  int (*i2c_write) (uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint32_t len);

  // Delay a time period in milisecond 
  void (*delay_ms) (uint32_t ms);

  // Gpio set
  void (*gpio_write) (uint8_t pin, uint8_t state);

}
drv10975_t;

/* Public function prototypes ----------------------------------------- */
/**
 * @brief         DRV10975 init
 *
 * @param[in]     me      Pointer to handle of DRV10975 module.
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t drv10975_init(drv10975_t *me);



/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __DRV10975_H

/* End of file -------------------------------------------------------- */