/**
 * @file       bsp_rtc.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-11-05
 * @author     Hiep Le
 * @brief      Board support package for RTC driver (PCF85063)
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_RTC_H
#define __BSP_RTC_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include "pcf85063.h"

/* Public defines ----------------------------------------------------- */
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public enumerate/structure ----------------------------------------- */
/**
 * @brief Human readable time struct
 */
typedef struct
{
  uint16_t year;
  uint8_t  month;
  uint8_t  day;
  uint8_t  hour;
  uint8_t  min;
  uint8_t  sec;
}
htime_t;

/* Public function prototypes ----------------------------------------- */
base_status_t bsp_rtc_init(void);
base_status_t bsp_rtc_get_time(uint64_t *epoch_time);
base_status_t bsp_rtc_set_time(uint64_t epoch_time);
htime_t bsp_rtc_epoch_to_htime(uint64_t t);
uint64_t bsp_rtc_htime_to_epoch(htime_t t);
void bsp_rtc_makestring_timestyle_1(char *out, time_t timestamp);

/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __BSP_RTC_H

/* End of file -------------------------------------------------------- */