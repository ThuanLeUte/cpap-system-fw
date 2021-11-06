/**
 * @file       ble_bas.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-10-20
 * @author     Hiep Le
 * @brief      BLE Battery service
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BLE_BAS_H
#define __BLE_BAS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Public defines ----------------------------------------------------- */
#define BLE_BAS_UUID16                                   0x180F // 16 Bit Battery Service UUID 
#define BLE_BAS_CHR_UUID16_BATTERY_LEVEL                 0x2A19 // 16 Bit Battery Service Characteristic UUIDs 

/* Public function prototypes ----------------------------------------- */
/**
 * @brief         Battery service set battery level
 *
 * @param[in]     level      Voltage level of battery
 *
 * @attention     None
 *
 * @return
 */
void ble_bas_battery_level_set(uint8_t level);

/**
 * @brief         Battery service init
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return
 */
void ble_bas_init(void);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __BLE_BAS_H

/* End of file -------------------------------------------------------- */