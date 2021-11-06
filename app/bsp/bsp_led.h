/**
 * @file       bsp_led.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-10-30
 * @author     Thuan Le
 * @brief      Board Support Package (BSP)
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_LED_H
#define __BSP_LED_H

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
void bsp_led_init(void);
// void bsp_led_dim(uint32_t led, uint32_t duty_x, uint32_t duty_y, uint32_t time);
void bsp_led_dim(uint32_t led, uint8_t duty_x, uint8_t duty_y, uint32_t time);
void bsp_led_set_duty(uint32_t led, uint8_t duty);
uint32_t bsp_led_duty_map(uint8_t duty);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __BSP_LED_H

/* End of file -------------------------------------------------------- */