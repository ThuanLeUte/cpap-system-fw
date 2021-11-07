/**
* @file       bsp_power.c
* @copyright  Copyright (C) 2021 Hydratech. All rights reserved.
* @license    This project is released under the Hydratech License.
* @version    01.00.00
* @date       2021-11-04
* @author     Hiep Le
* @brief      BSP (Board Support Package)
* @note       None
* @example    None
*/

/* Includes ----------------------------------------------------------------- */
#include "bsp.h"
#include "driver/gpio.h"
#include "sys_damos_ram.h"

/* Private defines ---------------------------------------------------------- */
static const char *TAG = "bsp_power";

#define SHUTDOWN()  bsp_power_shutdown()

/* Public variables --------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
/* Private function --------------------------------------------------------- */
/* Function definitions ----------------------------------------------------- */
void bsp_power_start_up_device_check(void)
{
  uint64_t start_time = esp_timer_get_time();

  while (1)
  {
    if (bsp_io_read(IO_POWER_KEY) == 1)
      SHUTDOWN();
    
    bsp_delay_ms(100);

    if (esp_timer_get_time() - start_time >= 3000000)
      break;
  }

  bsp_io_write(IO_POWER_LATCH, 1);
}

void bsp_power_shutdown(void)
{
  bsp_io_write(IO_POWER_LATCH, 0);
  
  while (1)
  {
    bsp_delay_ms(100);
  }
}

void bsp_power_shutdown_device_task(void *pvParameter)
{
  while (1)
  {
    bsp_delay_ms(100);

    if (bsp_io_read(IO_POWER_KEY) == 0)
    {
      g_shutdown_ms--;

      if (g_shutdown_ms == 0)
      {
        ESP_LOGI(TAG, "Shutdown device !!!");
      }
    }
  }
}

void bsp_power_init(void)
{
  bsp_power_start_up_device_check();
}
  
/* End of file -------------------------------------------------------- */