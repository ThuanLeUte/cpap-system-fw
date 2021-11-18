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
#define PAC1934_I2C_ADDR                       (0x11 << 1) // I2C bus need 8 bits address

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief PAC1934 sample rate
 */
typedef enum
{
    PAC1934_SAMPLE_RATE_1000HZ = 0
  , PAC1934_SAMPLE_RATE_256HZ  
  , PAC1934_SAMPLE_RATE_64HZ   
  , PAC1934_SAMPLE_RATE_8HZ    
}
pac1934_sample_rate_t;

/**
 * @brief PAC1934 channels enum
 */
typedef enum
{
   PAC1934_CHANNEL_1 = 0
  ,PAC1934_CHANNEL_2
  ,PAC1934_CHANNEL_3
  ,PAC1934_CHANNEL_4
}
pac1934_channel_t;

/**
 * @brief PAC1934 data
 */
typedef struct
{
  double volt;
  double current;
  double power;
  double energy;
}
pac1934_data_t;

/**
 * @brief PAC1934 config
 */
typedef struct
{
  pac1934_sample_rate_t sample_rate;
  bool sleep_mode_bit;
}
pac1934_config_t;

/**
 * @brief PAC1934 sensor struct
 */
typedef struct 
{
  uint8_t device_address;  // I2C device address

  pac1934_data_t data;     // PAC1934 data
  pac1934_config_t config; // PAC1934 config

  // Read n-bytes from device's internal address <reg_addr> via I2C bus
  int (*i2c_read) (uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint32_t len);

  // Write n-bytes from device's internal address <reg_addr> via I2C bus
  int (*i2c_write) (uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint32_t len);

  // Write n-bytes to device via I2C bus
  int (*i2c_write_data) (uint8_t slave_addr, uint8_t *data, uint32_t len);

  // Delay a time period in milisecond
  void (*delay_ms) (uint32_t ms);
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
 * @brief         PAC1934 config
 *
 * @param[in]     me      Pointer to handle of PAC1934 module.
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t pac1934_config(pac1934_t *me);

/**
 * @brief         PAC1934 measure voltage
 *
 * @param[in]     me            Pointer to handle of PAC1934 module.
 * @param[in]     channel       Channel number of PAC1934 module.
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t pac1934_voltage_measurement(pac1934_t *me, pac1934_channel_t channel);

/**
 * @brief         PAC1934 measure current
 *
 * @param[in]     me            Pointer to handle of PAC1934 module.
 * @param[in]     channel       Channel number of PAC1934 module.
 * 
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t pac1934_current_measurement(pac1934_t *me, pac1934_channel_t channel);

/**
 * @brief         PAC1934 measure power
 *
 * @param[in]     me            Pointer to handle of PAC1934 module.
 * @param[in]     channel       Channel number of PAC1934 module.
 * 
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t pac1934_power_measurement(pac1934_t *me, pac1934_channel_t channel);

/**
 * @brief         PAC1934 into sleep mode
 *
 * @param[in]     me      Pointer to handle of PAC1934 module.
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t pac1934_into_sleep_mode(pac1934_t *me);

/**
 * @brief         PAC1934 active to normal mode
 *
 * @param[in]     me      Pointer to handle of PAC1934 module.
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t pac1934_into_normal_mode(pac1934_t *me);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __PAC1934_H

/* End of file -------------------------------------------------------- */