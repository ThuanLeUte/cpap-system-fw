/**
 * @file       sys.c
 * @copyright  Copyright (C) 2021 ThuanLe. All rights reserved.
 * @license    This project is released under the ThuanLe License.
 * @version    1.0.0
 * @date       2020-07-23
 * @author     Thuan Le
 * @brief      System module to handle system state
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------------- */
#include "platform_common.h"

#include "bsp_brc.h"
#include "bsp_gyro.h"
#include "bsp_pm.h"
#include "bsp_rtc.h"

#include "bsp.h"
#include "ble.h"
#include "sys_damos_ram.h"

/* Private defines ---------------------------------------------------------- */
/* Private Constants -------------------------------------------------------- */
static const char *TAG = "sys";

/* Private macros ----------------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* Public variables --------------------------------------------------------- */
char out[24];
uint64_t epoch_time = 0;
uint64_t epoch_time_cvrt = 0;
htime_t htime;

/* Private function prototypes ---------------------------------------------- */
void sys_task_create(void);

/* Function definitions ----------------------------------------------------- */
void sys_boot(void)
{
  bsp_init(); 

  // bsp_brc_init();
  // bsp_gyro_init();
  // bsp_pm_init();
  // bsp_rtc_init();

  ble_init();
  sys_task_create();
}

void sys_run(void)
{
  // if(g_epoch_time != epoch_time)
  // {
  //   epoch_time = g_epoch_time;

  //   bsp_rtc_makestring_timestyle_1(out, epoch_time);

  //   ESP_LOGE(TAG, "Date time: %s", out);

  //   htime = bsp_rtc_epoch_to_htime(epoch_time);

  //   ESP_LOGE(TAG, "Human date time: %d-%d-%d-%d-%d-%d", htime.hour, htime.min, htime.sec, htime.day, htime.month, htime.year);

  //   epoch_time_cvrt = bsp_rtc_htime_to_epoch(htime);

  //   ESP_LOGE(TAG, "Epoch Time: %li", (long int) epoch_time_cvrt);
  // }

  // bsp_delay_ms(100);


  bsp_led_dim(IO_LED_RED, 0, 100, 2000);
  bsp_delay_ms(2200); 
  bsp_led_dim(IO_LED_RED, 100, 0, 2000);
  bsp_delay_ms(2200);    

  // bsp_buzz_set_duty(70);
  // bsp_delay_ms(200);
  // bsp_buzz_set_duty(0);
  // bsp_delay_ms(2000);

  // bsp_brc_init();
  // bsp_gyro_init();
  // bsp_pm_init();
  // bsp_rtc_init();
}

void sys_task_create(void)
{
  xTaskCreate(&bsp_power_shutdown_device_task, "Shutdown device task", 2048, NULL, 5, NULL );
}

/* Private function --------------------------------------------------------- */
/* End of file -------------------------------------------------------- */