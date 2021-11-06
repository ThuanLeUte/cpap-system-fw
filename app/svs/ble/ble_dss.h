/**
 * @file       ble_dss.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-10-20
 * @author     Hiep Le
 * @brief      Device setting service
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BLE_DSS_H
#define __BLE_DSS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "platform_common.h"

/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */

/* Public defines ----------------------------------------------------- */
#define DSS_BASE_UUID(uuid) 0x41, 0xEE, 0x68, 0x3A, 0x99, 0x0F, 0x0E, 0x72, 0x85, 0x49, 0x8D, 0xB3, LO_UINT16(uuid), HI_UINT16(uuid), 0x00, 0x00

#define BLE_UUID_DSS_SERVICE	                    DSS_BASE_UUID(0x1234) 
#define BLE_UUID_DSS_PRESSURE_CHARACTERISTIC      DSS_BASE_UUID(0x1235)
#define BLE_UUID_DSS_RAMP_TIME_CHARACTERISTIC     DSS_BASE_UUID(0x1236)
#define BLE_UUID_DSS_ALARM_HOUR_CHARACTERISTIC    DSS_BASE_UUID(0x1237)
#define BLE_UUID_DSS_ALARM_MINUTE_CHARACTERISTIC  DSS_BASE_UUID(0x1238)                                                                                               

/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief Device setting data struct
 */
typedef struct
{
  uint8_t pressure;
  uint8_t ramp_time;
  uint8_t alarm_hour;
  uint8_t alarm_minute;
}
ble_dss_data_t;

/**
 * @brief Device setting charateristic enum
 */
typedef enum
{
   DSS_PRESSURE_CHARACTERISTIC
  ,DSS_RAMP_TIME_CHARACTERISTIC
  ,DSS_ALARM_HOUR_CHARACTERISTIC
  ,DSS_ALARM_MINUTE_CHARACTERISTIC
}
ble_dss_char_t;

/**
 * Variable holding data for the main characteristics.
 */
extern ble_dss_data_t ble_dss_data;

/* Public function prototypes ----------------------------------------- */
/**
 * @brief         BLE device setting service init
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return        None  
 * 
 */
void ble_dss_init(void);

/**
 * @brief         BLE device setting service get pressure value
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return        Pressure value
 * 
 */
uint8_t *ble_dss_get_pressure(void);

/**
 * @brief         BLE device setting service set pressure
 *
 * @param[in]     value     Pointer of pressure value
 *
 * @attention     None
 *
 * @return        None  
 * 
 */
void ble_dss_set_pressure(uint8_t *value);

/**
 * @brief         BLE device setting service get ramp time value
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return        Ramp time value  
 * 
 */
uint8_t *ble_dss_get_ramp_time(void);

/**
 * @brief         BLE device setting service set ramp time
 *
 * @param[in]     value     Pointer of ramp time value
 *
 * @attention     None
 *
 * @return          
 * 
 */
void ble_dss_set_ramp_time(uint8_t *value);

/**
 * @brief         BLE device setting service get alarm hour value
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return        Alarm hour value  
 * 
 */
uint8_t *ble_dss_get_alarm_hour(void);

/**
 * @brief         BLE device setting service set alarm hour
 *
 * @param[in]     value     Pointer of alarm hour value
 *
 * @attention     None
 *
 * @return          
 * 
 */
void ble_dss_set_alarm_hour(uint8_t *value);

/**
 * @brief         BLE device setting service get alarm minute value
 *
 * @param[in]     None
 *
 * @attention     None
 *
 * @return        Alarm minute value  
 * 
 */
uint8_t *ble_dss_get_alarm_minute(void);

/**
 * @brief         BLE device setting service init
 *
 * @param[in]     value     Pointer of alarm minute value
 *
 * @attention     None
 *
 * @return          
 * 
 */
void ble_dss_set_alarm_minute(uint8_t *value);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __BLE_DSS_H

/* End of file -------------------------------------------------------- */
