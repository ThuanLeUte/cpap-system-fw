/**
 * @file       bsp_buzz.h
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
#ifndef __BSP_BUZZ_H
#define __BSP_BUZZ_H

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
void bsp_buzz_init(void);
void bsp_buzz_set_duty(uint8_t duty);
uint32_t bsp_buzz_duty_map(uint8_t duty);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __BSP_BUZZ_H

/* End of file -------------------------------------------------------- */