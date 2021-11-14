/**
 * @file       bsp_i2c.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-10-30
 * @author     Hiep Le
 * @brief      Board Support Package (BSP)
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_I2C_H
#define __BSP_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "platform_common.h"
#include "bsp_io_10.h"

/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief         Board support package I2C write
 *
 * @param[in]     slave_addr    Slave address
 * @param[in]     reg_addr      Register address
 * @param[in]     data          Pointer to handle of data
 * @param[in]     len           Data length
 *
 * @attention     None
 *
 * @return
 * - 0      Succes
 * - 1      Error
 */
int bsp_i2c_write(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint32_t len);

/**
 * @brief         Board support package I2C read
 *
 * @param[in]     slave_addr    Slave address
 * @param[in]     reg_addr      Register address
 * @param[in]     data          Pointer to handle of data
 * @param[in]     len           Data length
 *
 * @attention     None
 *
 * @return
 * - 0      Succes
 * - 1      Error
 */
int bsp_i2c_read(uint8_t slave_addr, uint8_t reg_addr, uint8_t *data, uint32_t len);

/**
 * @brief         Board support package I2C init
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return        None
 */
esp_err_t bsp_i2c_init(void);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __BSP_I2C_H

/* End of file -------------------------------------------------------- */