/**
 * @file       bsp_gyro.h
 * @copyright  Copyright (C) 2020 HiepLe. All rights reserved.
 * @license    This project is released under the HiepLe License.
 * @version    1.0.0
 * @date       2021-10-07
 * @author     Hiep Le
 * @brief      Board support package for GyroScope
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_GYRO_H
#define __BSP_GYRO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "bsp_gyro.h"

/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief         BSP GyroScope init
 *
 * @param[in]     me      Pointer to handle of GyroScope module.
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_gyro_init(void);

/**
 * @brief         BSP GyroScope reset
 *
 * @param[in]     me      Pointer to handle of GyroScope module.
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_gyro_reset(void)

/**
 * @brief         BSP GyroScope read raw data
 *
 * @param[in]     me            Pointer to handle of GyroScope module.
 * @param[in]     raw_data      GyroScope raw data
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_gyro_get_raw_data(iam20380_data_t *raw_data)

/**
 * @brief         BSP GyroScope calculate gyro angle
 *
 * @param[in]     me            Pointer to handle of GyroScope module.
 * @param[in]     raw_data      GyroScope raw data
 * @param[in]     angle         GyroScope angle
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_gyro_get_gyro_angle(iam20380_data_t *raw_data, iam20380_angle_t *angle)

/**
 * @brief         BSP GyroScope get sensitivity
 *
 * @param[in]     me            Pointer to handle of GyroScope module.
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_gyro_get_sensitivity(void)

/**
 * @brief         BSP GyroScope set fullscale
 *
 * @param[in]     me            Pointer to handle of GyroScope module.
 * @param[in]     scale         GyroScope scale
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_gyro_set_fullscale(iam20380_fullscale_t scale)

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __BSP_GYRO_H

/* End of file -------------------------------------------------------- */