/**
 * @file       bsp_brc.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-10-14
 * @author     Hiep Le
 * @brief      Board support package for Brushless Motor Driver (DRV10975)
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_BRC_H
#define __BSP_BRC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "drv10975.h"

/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/**
 * @brief         BSP brushless motor driver init
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_brc_init(void);

/**
 * @brief         BSP brushless motor driver set reverse direction for motor
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_brc_forward_direction(void);

/**
 * @brief         BSP brushless motor driver set reverse direction for motor
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_brc_reverse_direction(void);

/**
 * @brief         BSP brushless motor driver set motor speed
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_brc_set_motor_speed(uint16_t percent_speed);

/**
 * @brief         BSP brushless motor driver get motor velocity
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_brc_get_motor_velocity(void);

/**
 * @brief         BSP brushless motor driver get motor period
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_brc_get_motor_period(void);

/**
 * @brief         BSP brushless motor driver get device supply voltage
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_brc_get_motor_supply_voltage(void);

/**
 * @brief         BSP brushless motor driver get motor current
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_brc_get_motor_current(void);

/**
 * @brief         BSP brushless motor driver check device over temp
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_brc_check_over_temp(void);

/**
 * @brief         BSP brushless motor driver check device in sleep mode
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_brc_check_sleep_mode(void);

/**
 * @brief         BSP brushless motor driver check device over current
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_brc_check_over_current(void);

/**
 * @brief         BSP brushless motor driver check motor lock
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
base_status_t bsp_brc_check_motor_lock(void);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __BSP_BRC_H

/* End of file -------------------------------------------------------- */