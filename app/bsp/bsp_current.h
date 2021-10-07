/**
 * @file       bsp_current.h
 * @copyright  Copyright (C) 2020 HiepLe. All rights reserved.
 * @license    This project is released under the HiepLe License.
 * @version    1.0.0
 * @date       2021-10-07
 * @author     Hiep Le
 * @brief      Board support package for Multi Channel Power Monitor (PAC1934)
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_CURRENT_H
#define __BSP_CURRENT_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "pac1934.h"

/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief         BSP Multi Channel Power Monitor sensor init
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_current_init(void);

/**
 * @brief         BSP Multi Channel Power Monitor get voltage
 *
 * @param[in]     voltage  Multi Channel Power Monitor voltage
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_current_voltage_measurement(pac1934_data_t *voltage, uint8_t channel);

/**
 * @brief         BSP Multi Channel Power Monitor get current
 *
 * @param[in]     current   Multi Channel Power Monitor current
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_current_current_measurement(pac1934_data_t *current, uint8_t channel);

/**
 * @brief         BSP Multi Channel Power Monitor get power
 *
 * @param[in]     power  Multi Channel Power Monitor power
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_current_power_measurement(pac1934_data_t *power, uint8_t channel);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __BSP_CURRENT_H

/* End of file -------------------------------------------------------- */