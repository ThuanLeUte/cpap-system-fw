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
/* Private macros ----------------------------------------------------------- */
#define SHUTDOWN()                    bsp_power_shutdown()
#define POWER_KEY_PRESSING            bsp_io_read(IO_POWER_KEY) == 1
#define POWER_KEY_RELEASING           bsp_io_read(IO_POWER_KEY) == 0

/* Public variables --------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
static const char *TAG = "bsp_power";

/* Private function prototypes ---------------------------------------------- */
/* Private function --------------------------------------------------------- */
/* Function definitions ----------------------------------------------------- */
void bsp_power_start_up_device_task(void)
{
  uint64_t start_time = esp_timer_get_time();

  while (1)
  {
    if(POWER_KEY_PRESSING)
    {
      if (esp_timer_get_time() - start_time >= POWER_KEY_TIMEOUT)
        break;
    }
    else if (POWER_KEY_RELEASING)
      SHUTDOWN();

    bsp_delay_ms(100);
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
    if (POWER_KEY_PRESSING)
    {
      g_shutdown_ms--;

      if (g_shutdown_ms == 0)
      {
        ESP_LOGI(TAG, "Shutdown device !!!");
        bsp_power_shutdown_indicate();
        SHUTDOWN();
      }
    }

    bsp_delay_ms(100);
  }
}

void bsp_power_init(void)
{
  bsp_power_start_up_device_task();
}

void bsp_power_shutdown_indicate(void)
{
  LED_OFF();
  BUZZ_ON();
  LED_ON(IO_LED_RED);
  bsp_delay_ms(2000);
  BUZZ_OFF();
  LED_OFF();
}

void bsp_power_startup_indicate(void)
{
  LED_OFF();
  BUZZ_ON();
  LED_ON(IO_LED_GREEN);
  bsp_delay_ms(2000);
  BUZZ_OFF();
  LED_OFF();
}
  
/* End of file -------------------------------------------------------- */