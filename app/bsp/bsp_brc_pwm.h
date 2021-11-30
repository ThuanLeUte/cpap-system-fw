/**
 * @file       bsp_brc_pwm.h
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
#ifndef __BSP_BRC_PWM_H
#define __BSP_BRC_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "platform_common.h"
#include "driver/ledc.h"
#include "bsp_io.h"

/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
void bsp_brc_pwm_init(void);
void bsp_brc_pwm_set_duty(uint8_t duty);
void bsp_brc_pwm_set_motor_speed(uint8_t percent_speed);
uint32_t bsp_brc_pwm_duty_map(uint8_t duty);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __BSP_BRC_PWM_H

/* End of file -------------------------------------------------------- */