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
#define IAM20380_I2C_ADDR                       (0x68) // 7 Bits

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief IAM20380 fullscale enum
 */
typedef enum
{
     IAM20380_FULLSCALE_250_DPS  = 0x00
   , IAM20380_FULLSCALE_500_DPS  = 0x01
   , IAM20380_FULLSCALE_1000_DPS = 0x02
   , IAM20380_FULLSCALE_2000_DPS = 0x03
}
iam20380_fullscale_t;

/**
 * @brief IAM20380 digital lowpass filter enum
 */
typedef enum
{
      IAM20380_DLPF0_NBW307  = 0x00
    , IAM20380_DLPF1_NBW177  = 0x01
    , IAM20380_DLPF2_NBW109  = 0x02
    , IAM20380_DLPF3_NBW59   = 0x03
    , IAM20380_DLPF4_NBW31   = 0x04
    , IAM20380_DLPF5_NBW16   = 0x05
    , IAM20380_DLPF6_NBW8    = 0x06
    , IAM20380_DLPF7_NBW3451 = 0x07
}
iam20380_digi_low_pass_filter_t;

/**
 * @brief IAM20380 sample rate enum
 */
typedef enum
{
      IAM20380_SAMPLE_RATE_1000HZ = 0x00
    , IAM20380_SAMPLE_RATE_500HZ  = 0x01
    , IAM20380_SAMPLE_RATE_200HZ  = 0x04
    , IAM20380_SAMPLE_RATE_125HZ  = 0x07
    , IAM20380_SAMPLE_RATE_100HZ  = 0x09
    , IAM20380_SAMPLE_RATE_50HZ   = 0x13
    , IAM20380_SAMPLE_RATE_20HZ   = 0x31
}
iam20380_sample_rate_t;

/**
 * @brief IAM20380 angle data
 */
typedef struct
{
  iam20380_fullscale_t fullscale;
  iam20380_digi_low_pass_filter_t digi_low_pass_filter;
  iam20380_sample_rate_t sample_rate;
}
iam20380_config_t;

/**
 * @brief IAM20380 raw data
 */
typedef struct
{
  short x;
  short y;
  short z;
}
iam20380_raw_data_t;

/**
 * @brief IAM20380 angle
 */
typedef struct
{
  float x;
  float y;
  float z;
}
iam20380_angle_t;

/**
 * @brief IAM20380 data
 */
typedef struct
{
  iam20380_raw_data_t raw_data;
  iam20380_angle_t angle;
  float sensitivity;
}
iam20380_data_t;

/**
 * @brief IAM20380 sensor struct
 */
typedef struct 
{
  uint8_t device_address;  // I2C device address
  iam20380_data_t data;
  iam20380_config_t config;

  // Read n-bytes from device's internal address <reg_addr> via I2C bus
  int (*i2c_read) (uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint32_t len);

  // Write n-bytes from device's internal address <reg_addr> via I2C bus
  int (*i2c_write) (uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint32_t len);

  // Delay a time period in milisecond 
  void (*delay_ms) (uint32_t ms);
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
 * @brief         IAM20380 config
 *
 * @param[in]     me      Pointer to handle of IAM20380 module.
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t iam20380_config(iam20380_t *me);

/**
 * @brief         IAM20380 read raw data
 *
 * @param[in]     me            Pointer to handle of IAM20380 module.
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t iam20380_get_raw_data(iam20380_t *me);

/**
 * @brief         IAM20380 calculate gyro angle
 *
 * @param[in]     me            Pointer to handle of IAM20380 module.
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t iam20380_get_gyro_angle(iam20380_t *me);

/**
 * @brief         IAM20380 get sensitivity
 *
 * @param[in]     me            Pointer to handle of IAM20380 module.
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t iam20380_get_sensitivity(iam20380_t *me);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __IAM20380_H

/* End of file -------------------------------------------------------- */