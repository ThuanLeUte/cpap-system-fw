/**
* @file       bsp_led.c
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
#include "bsp_led.h"
#include "bsp.h"
#include "sys_damos_ram.h"
#include "math.h"

/* Private defines ---------------------------------------------------------- */
#define BSP_LED_CHANNEL_NUM           (2)

#define BSP_LED_CHANNEL_0_GPIO        IO_LED_RED
#define BSP_LED_CHANNEL_1_GPIO        IO_LED_GREEN       

#define BSP_LED_TIMER_RESOLUTION      LEDC_TIMER_13_BIT
#define BSP_LED_TIMER_NUM             LEDC_TIMER_0
#define BSP_LED_TIMER_CLK_CFG         LEDC_AUTO_CLK
#define BSP_LED_PWM_FREQ              (5000)
#define BSP_LED_PWM_SPEED_MODE        LEDC_HIGH_SPEED_MODE      
#define BSP_LED_PWM_CHANNEL_0         LEDC_CHANNEL_0
#define BSP_LED_PWM_CHANNEL_1         LEDC_CHANNEL_1

/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
// static const char *TAG = "bsp_led";

ledc_timer_config_t bsp_led_timer =
{
  .duty_resolution = BSP_LED_TIMER_RESOLUTION,        // Resolution of PWM duty
  .freq_hz         = BSP_LED_PWM_FREQ,                // Frequency of PWM signal
  .speed_mode      = BSP_LED_PWM_SPEED_MODE,          // Timer mode
  .timer_num       = BSP_LED_TIMER_NUM,               // Timer index
  .clk_cfg         = BSP_LED_TIMER_CLK_CFG,           // Auto select the source clock
};

ledc_channel_config_t bsp_led_channel[BSP_LED_CHANNEL_NUM] =
{ 
  {
    .channel    = BSP_LED_PWM_CHANNEL_0,
    .duty       = 0,
    .gpio_num   = BSP_LED_CHANNEL_0_GPIO,
    .speed_mode = BSP_LED_PWM_SPEED_MODE,
    .hpoint     = 0,
    .timer_sel  = BSP_LED_TIMER_NUM
  },
  {
    .channel    = BSP_LED_PWM_CHANNEL_1,
    .duty       = 0,
    .gpio_num   = BSP_LED_CHANNEL_1_GPIO,
    .speed_mode = BSP_LED_PWM_SPEED_MODE,
    .hpoint     = 0,
    .timer_sel  = BSP_LED_TIMER_NUM
  },
};

/* Private function prototypes ---------------------------------------------- */
/* Function definitions ----------------------------------------------------- */
void bsp_led_init(void)
{
  uint8_t channel;

  ledc_timer_config(&bsp_led_timer);

  for (channel = 0; channel < BSP_LED_CHANNEL_NUM; channel++) 
  {
    ledc_channel_config(&bsp_led_channel[channel]);
  }

  ledc_fade_func_install(0);
}

void bsp_led_dim(uint32_t led, uint8_t duty_x, uint8_t duty_y, uint32_t time)
{
  uint8_t index = 0;

  switch (led)
  {
    case IO_LED_RED: 
      index = 0;
      break;

    case IO_LED_GREEN: 
      index = 1;
      break;
    
    default:
      break;
  }

  ledc_set_duty(bsp_led_channel[index].speed_mode, bsp_led_channel[index].channel, bsp_led_duty_map(duty_x));
  ledc_update_duty(bsp_led_channel[index].speed_mode, bsp_led_channel[index].channel);

  vTaskDelay(pdMS_TO_TICKS(10)); 

  ledc_set_fade_with_time(bsp_led_channel[index].speed_mode, 
                          bsp_led_channel[index].channel, bsp_led_duty_map(duty_y), (int)time);
  ledc_fade_start(bsp_led_channel[index].speed_mode, 
                  bsp_led_channel[index].channel, LEDC_FADE_NO_WAIT);
}

void bsp_led_set_duty(uint32_t led, uint8_t duty)
{
  uint8_t index = 0;

  switch (led)
  {
    case IO_LED_RED: 
      index = 0;
      break;

    case IO_LED_GREEN: 
      index = 1;
      break;
    
    default:
      break;
  }

  ledc_set_duty(bsp_led_channel[index].speed_mode, bsp_led_channel[index].channel, bsp_led_duty_map(duty));
  ledc_update_duty(bsp_led_channel[index].speed_mode, bsp_led_channel[index].channel);
}

void LED_ON(uint32_t led)                
{
  bsp_led_set_duty(led, 80);
  bsp_delay_ms(10); 
  if(led == IO_LED_GREEN)    bsp_led_set_duty(IO_LED_RED, 0);
  else if(led == IO_LED_RED) bsp_led_set_duty(IO_LED_GREEN, 0); 
}

void LED_OFF(void)                 
{
  bsp_led_set_duty(IO_LED_RED, 0); 
  bsp_led_set_duty(IO_LED_GREEN, 0);
}

uint32_t bsp_led_duty_map(uint8_t duty)
{
  if(duty > 100) duty = 100;
  return (uint32_t)ldexp((double)duty, (int)BSP_LED_TIMER_RESOLUTION) / 100;
}

/* Private function --------------------------------------------------------- */

/* End of file -------------------------------------------------------- */