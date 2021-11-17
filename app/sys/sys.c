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
static const char *TAG = "SYS";
uint16_t volt = 0;

/* Private macros ----------------------------------------------------------- */
/* Private enumerate/structure ---------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* Public variables --------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
void sys_task_create(void);

/* Function definitions ----------------------------------------------------- */
void sys_boot(void)
{
  bsp_init(); 

  bsp_rtc_init();
  bsp_gyro_init();
  bsp_pm_init();

  // bsp_brc_init();

  ble_init();
  sys_task_create();

  // bsp_power_startup_indicate();

  // bsp_adc_get_voltage(&volt);
  // ESP_LOGE(TAG, "v = %d", volt);
}

void sys_run(void)
{

  bsp_delay_ms(100);
}

void sys_task_create(void) 
{
  xTaskCreate(&bsp_power_shutdown_device_task, "Shutdown device task", 2048, NULL, 5, NULL );
}

/* Private function --------------------------------------------------------- */
/* End of file -------------------------------------------------------- */