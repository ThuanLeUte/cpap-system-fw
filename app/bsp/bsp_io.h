/**
 * @file       bsp_io.h
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
#ifndef __BSP_IO_H
#define __BSP_IO_H

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
void bsp_io_init(void);
void bsp_io_write(uint8_t pin, uint8_t state);
int bsp_io_read(uint8_t pin);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __BSP_IO_H

/* End of file -------------------------------------------------------- */