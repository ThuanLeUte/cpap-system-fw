/**
 * @file       sys_damos_ram.h
 * @copyright  Copyright (C) 2020 ThuanLe. All rights reserved.
 * @license    This project is released under the ThuanLe License.
 * @version    1.0.0
 * @date       2021-03-18
 * @author     Thuan Le
 * @brief      System damos ram
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __SYS_DAMOS_RAM_H
#define __SYS_DAMOS_RAM_H

/* Includes ----------------------------------------------------------- */
#include <stdint.h>

/* Public defines ----------------------------------------------------- */
#define POWER_KEY_TIMEOUT               (2000000) // 2s
#define TIME_OUT_DIVISION               (100000)

/* Public enumerate/structure ----------------------------------------- */
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
extern uint16_t g_shutdown_ms;
extern uint64_t g_epoch_time;

/* Public function prototypes ----------------------------------------- */

#endif // __SYS_DAMOS_RAM_H

/* End of file -------------------------------------------------------- */
