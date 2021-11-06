/**
 * @file       ble.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-10-24
 * @author     Hiep Le
 * @brief      BLE profile
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BLE_H
#define __BLE_H

#ifdef __cplusplus
extern "C" {
#endif

/* Public defines ----------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
void ble_init(void);
void print_addr(const void *addr);
void ble_host_task(void *param);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __BLE_H

/* End of file -------------------------------------------------------- */