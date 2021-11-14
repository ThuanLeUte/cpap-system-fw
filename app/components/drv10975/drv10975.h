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
#define DRV10975_I2C_ADDR                       (0x52 << 1) // I2C bus need 8 bits address

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief DRV10975 motor value
 */
typedef struct
{
  uint16_t speed;    
  float period;
  float current;
  float supply_voltage;
  float velocity;
}
drv10975_motor_value_t;

/**
 * @brief DRV10975 motor value
 */
typedef enum
{
    DRV10975_OVER_TEMP    = 0X80
  , DRV10975_SLEEP        = 0X40
  , DRV10975_OVER_CURRENT = 0X20
  , DRV10975_MOTOR_LOCK   = 0X10
}
drv10975_status_t;

/**
 * @brief DRV10975 struct
 */
typedef struct 
{
  uint8_t device_address;  // I2C device address
  drv10975_status_t status; // Device status
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

/**
 * @brief         DRV10975 set motor direction
 *
 * @param[in]     me      Pointer to handle of DRV10975 module.
 * @param[in]     dir     Motor direction
 * 
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t drv10975_set_motor_direction(drv10975_t *me, uint8_t dir);

/**
 * @brief         DRV10975 set motor speed in percent
 *
 * @param[in]     me                Pointer to handle of DRV10975 module.
 * @param[in]     percent_speed     Motor speed in percent
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t drv10975_set_motor_speed(drv10975_t *me, uint8_t percent_speed);

/**
 * @brief         DRV10975 get motor velocity
 *
 * @param[in]     me      Pointer to handle of DRV10975 module.
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t drv10975_get_motor_velocity(drv10975_t *me);

/**
 * @brief         DRV10975 get motor period
 *
 * @param[in]     me      Pointer to handle of DRV10975 module.
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t drv10975_get_motor_period(drv10975_t *me);

/**
 * @brief         DRV10975 get device supply voltage
 *
 * @param[in]     me      Pointer to handle of DRV10975 module.
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t drv10975_get_motor_supply_voltage(drv10975_t *me);

/**
 * @brief         DRV10975 get motor current
 *
 * @param[in]     me      Pointer to handle of DRV10975 module.
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t drv10975_get_motor_current(drv10975_t *me);

/**
 * @brief         DRV10975 check device over temp
 *
 * @param[in]     me      Pointer to handle of DRV10975 module.
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t drv10975_check_over_temp(drv10975_t *me);

/**
 * @brief         DRV10975 check device is in sleep mode
 *
 * @param[in]     me      Pointer to handle of DRV10975 module.
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t drv10975_check_sleep_mode(drv10975_t *me);

/**
 * @brief         DRV10975 check device over current
 *
 * @param[in]     me      Pointer to handle of DRV10975 module.
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t drv10975_check_over_current(drv10975_t *me);

/**
 * @brief         DRV10975 check motor lock
 *
 * @param[in]     me      Pointer to handle of DRV10975 module.
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t drv10975_check_motor_lock(drv10975_t *me);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __DRV10975_H

/* End of file -------------------------------------------------------- */