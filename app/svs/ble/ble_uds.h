/**
 * @file       ble_uds.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-10-20
 * @author     Hiep Le
 * @brief      BLE User data service
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BLE_UDS_H
#define __BLE_UDS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "platform_common.h"

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */

/* Public defines ----------------------------------------------------- */
#define UDS_BASE_UUID(uuid) 0x41, 0xEE, 0x68, 0x3A, 0x99, 0x0F, 0x0E, 0x72, 0x85, 0x49, 0x8D, 0xB3, LO_UINT16(uuid), HI_UINT16(uuid), 0x00, 0x00

#define BLE_UUID_UDS_SERVICE	                          UDS_BASE_UUID(0x2234) 
#define BLE_UUID_UDS_OPERATION_HOUR_CHARACTERISTIC      UDS_BASE_UUID(0x2235)
#define BLE_UUID_UDS_OPERATION_MINUTE_CHARACTERISTIC    UDS_BASE_UUID(0x2236)
#define BLE_UUID_UDS_SLEEP_POSITION_CHARACTERISTIC      UDS_BASE_UUID(0x2237)

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief User data struct
 */
typedef struct
{
  uint8_t operation_hour;
  uint8_t operation_minute;
  uint8_t sleep_position;
}
ble_uds_data_t;

/**
 * @brief User data charateristic enum
 */
typedef enum
{
   UDS_OPERATION_HOUR_CHARACTERISTIC
  ,UDS_OPERATION_MINUTE_CHARACTERISTIC
  ,UDS_SLEEP_POSITION_CHARACTERISTIC
}
ble_uds_char_t;

// Variable holding data for the main characteristics
extern ble_uds_data_t ble_uds_data;

/* Public function prototypes ----------------------------------------- */
/**
 * @brief         BLE User data service init
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return        None  
 * 
 */
void ble_uds_init(void);

/**
 * @brief         BLE User data service get operation hour value
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return        Pressure value
 * 
 */
uint8_t *ble_uds_get_operation_hour(void);

/**
 * @brief         BLE User data service set operation hour
 *
 * @param[in]     value     Pointer of operation hour value
 *
 * @attention     None
 *
 * @return        None  
 * 
 */
void ble_uds_set_operation_hour(uint8_t *value);

/**
 * @brief         BLE User data service get Operation minute value
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return        Operation minute value  
 * 
 */
uint8_t *ble_uds_get_operation_minute(void);

/**
 * @brief         BLE User data service set Operation minute
 *
 * @param[in]     value     Pointer of Operation minute value
 *
 * @attention     None
 *
 * @return          
 * 
 */
void ble_uds_set_operation_minute(uint8_t *value);

/**
 * @brief         BLE User data service get sleep position
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return        Sleep position value  
 * 
 */
uint8_t *ble_uds_get_sleep_position(void);

/**
 * @brief         BLE User data service set sleep position
 *
 * @param[in]     value     Pointer of sleep position
 *
 * @attention     None
 *
 * @return          
 * 
 */
void ble_uds_set_sleep_position(uint8_t *value);

#endif // __BLE_UDS_H

/* End of file -------------------------------------------------------- */
