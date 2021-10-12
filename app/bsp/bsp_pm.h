/**
 * @file       bsp_pm.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-10-07
 * @author     Hiep Le
 * @brief      Board support package for Multi Channel Power Monitor (PAC1934)
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_PM_H
#define __BSP_PM_H

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
base_status_t bsp_pm_init(void);

/**
 * @brief         BSP Multi Channel Power Monitor get voltage
 *
 * @param[in]     channel   Multi Channel Power Monitor Channel
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_pm_voltage_measurement(pac1934_channel_t channel);

/**
 * @brief         BSP Multi Channel Power Monitor get current
 *
 * @param[in]     channel   Multi Channel Power Monitor Channel
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_pm_current_measurement(pac1934_channel_t channel);

/**
 * @brief         BSP Multi Channel Power Monitor get power
 *
 * @param[in]     channel   Multi Channel Power Monitor Channel
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_pm_power_measurement(pac1934_channel_t channel);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __BSP_PM_H

/* End of file -------------------------------------------------------- */