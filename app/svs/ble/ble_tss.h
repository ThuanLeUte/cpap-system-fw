/**
 * @file       ble_tss.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-11-05
 * @author     Hiep Le
 * @brief      Time synchronize service
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BLE_TSS_H
#define __BLE_TSS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "platform_common.h"

/* Public macros ------------------------------------------------------ */
/* Public enumerate/structure ----------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Public defines ----------------------------------------------------- */
#define TSS_BASE_UUID(uuid) 0x41, 0xEE, 0x68, 0x3A, 0x99, 0x0F, 0x0E, 0x72, 0x85, 0x49, 0x8D, 0xB3, LO_UINT16(uuid), HI_UINT16(uuid), 0x00, 0x00

#define BLE_UUID_TSS_SERVICE	                        TSS_BASE_UUID(0x3234) 
#define BLE_UUID_TSS_EPOCH_TIME_CHARACTERISTIC          TSS_BASE_UUID(0x3235)                                                                                              

/* Public function prototypes ----------------------------------------- */
/**
 * @brief         BLE time synchronize service init
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return        None  
 * 
 */
void ble_tss_init(void);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __BLE_TSS_H

/* End of file -------------------------------------------------------- */
