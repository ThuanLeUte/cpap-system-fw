/**
 * @file       bsp_power.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-01-23
 * @author     Thuan Le
 * @brief      Board Support Package (BSP)
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_POWER_H
#define __BSP_POWER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "platform_common.h"
// #include "bsp_io_10.h"
// #include "bsp_io.h"

/* Public defines ----------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
extern uint8_t count;

/* Public function prototypes ----------------------------------------- */
void bsp_power_init(void);
void bsp_power_start_up_device_task(void);
void bsp_power_shutdown(void);
void bsp_power_shutdown_indicate(void);
void bsp_power_startup_indicate(void);
void bsp_power_shutdown_device_task(void *pvParameter);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __BSP_POWER_H

/* End of file -------------------------------------------------------- */