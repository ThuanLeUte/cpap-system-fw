/**
* @file       bsp_io.c
* @copyright  Copyright (C) 2021 Hydratech. All rights reserved.
* @license    This project is released under the Hydratech License.
* @version    01.00.00
* @date       2021-10-30
* @author     Thuan Le
* @brief      BSP (Board Support Package)
* @note       None
* @example    None
*/

/* Includes ----------------------------------------------------------------- */
#include "bsp_io.h"
#include "driver/gpio.h"
#include "sys_damos_ram.h"

/* Private defines ---------------------------------------------------------- */
// static const char *TAG = "bsp_io";

/* Public variables --------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
/* Private function prototypes ---------------------------------------------- */
static void m_bsp_io_isr_handler(void* arg);

/* Function definitions ----------------------------------------------------- */
void bsp_io_init(void)
{
  gpio_pad_select_gpio(IO_BRC_DIR);
  // gpio_pad_select_gpio(IO_BUZZER);
  // gpio_pad_select_gpio(IO_LED_GREEN);
  // gpio_pad_select_gpio(IO_LED_RED);
  gpio_pad_select_gpio(IO_POWER_LATCH);
  gpio_pad_select_gpio(IO_POWER_KEY);

  gpio_set_direction(IO_BRC_DIR,     GPIO_MODE_OUTPUT);
  // gpio_set_direction(IO_BUZZER,      GPIO_MODE_OUTPUT);
  // gpio_set_direction(IO_LED_GREEN,   GPIO_MODE_OUTPUT);
  // gpio_set_direction(IO_LED_RED,     GPIO_MODE_OUTPUT);
  gpio_set_direction(IO_POWER_LATCH, GPIO_MODE_OUTPUT);
  gpio_set_direction(IO_POWER_KEY,   GPIO_MODE_INPUT);

  gpio_pullup_en(IO_POWER_KEY);
  gpio_intr_enable(IO_POWER_KEY);
  gpio_set_intr_type(IO_POWER_KEY, GPIO_INTR_NEGEDGE);
  gpio_install_isr_service(0);
  gpio_isr_handler_add(IO_POWER_KEY, m_bsp_io_isr_handler, (void*) IO_POWER_KEY);
}

void bsp_io_write(uint8_t pin, uint8_t state)
{
  gpio_set_level((gpio_num_t)pin, (uint32_t)state);
}

int bsp_io_read(uint8_t pin)
{
  return gpio_get_level((gpio_num_t)pin);
}

/* Private function --------------------------------------------------------- */
static void m_bsp_io_isr_handler(void* arg)
{
  g_shutdown_ms = 30;
}

/* End of file -------------------------------------------------------- */