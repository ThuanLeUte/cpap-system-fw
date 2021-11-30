/**
* @file       bsp_brc_pwm.c
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
#include "bsp_brc_pwm.h"
#include "sys_damos_ram.h"
#include "math.h"

/* Private defines ---------------------------------------------------------- */
#define BSP_BRC_PWM_TIMER_RESOLUTION     LEDC_TIMER_13_BIT
#define BSP_BRC_PWM_TIMER_NUM            LEDC_TIMER_2
#define BSP_BRC_PWM_TIMER_CLK_CFG        LEDC_AUTO_CLK
#define BSP_BRC_PWM_PWM_FREQ             (5000)
#define BSP_BRC_PWM_PWM_SPEED_MODE       LEDC_HIGH_SPEED_MODE      
#define BSP_BRC_PWM_PWM_CHANNEL_NUM      LEDC_CHANNEL_3
#define BSP_BRC_PWM_GPIO_NUM             IO_BRC_SPEED

/* Public variables --------------------------------------------------------- */
/* Private variables -------------------------------------------------------- */
// static const char *TAG = "bsp_brc_pwm";

ledc_timer_config_t bsp_brc_pwm_timer =
{
  .duty_resolution = BSP_BRC_PWM_TIMER_RESOLUTION,         // Resolution of PWM duty
  .freq_hz         = BSP_BRC_PWM_PWM_FREQ,                 // Frequency of PWM signal
  .speed_mode      = BSP_BRC_PWM_PWM_SPEED_MODE,           // Timer mode
  .timer_num       = BSP_BRC_PWM_TIMER_NUM,                // Timer index
  .clk_cfg         = BSP_BRC_PWM_TIMER_CLK_CFG,            // Auto select the source clock
};

ledc_channel_config_t bsp_brc_pwm_channel =
{ 
  .channel    = BSP_BRC_PWM_PWM_CHANNEL_NUM,
  .duty       = 0,
  .gpio_num   = BSP_BRC_PWM_GPIO_NUM,
  .speed_mode = BSP_BRC_PWM_PWM_SPEED_MODE,
  .hpoint     = 0,
  .timer_sel  = BSP_BRC_PWM_TIMER_NUM
};

/* Private function prototypes ---------------------------------------------- */
/* Function definitions ----------------------------------------------------- */
void bsp_brc_pwm_init(void)
{
  ledc_timer_config(&bsp_brc_pwm_timer);

  ledc_channel_config(&bsp_brc_pwm_channel);

  ledc_fade_func_install(0);
}

void bsp_brc_pwm_set_duty(uint8_t duty)
{
  ledc_set_duty(bsp_brc_pwm_channel.speed_mode, bsp_brc_pwm_channel.channel, bsp_brc_pwm_duty_map(duty));

  ledc_update_duty(bsp_brc_pwm_channel.speed_mode, bsp_brc_pwm_channel.channel);
}

void bsp_brc_pwm_set_motor_speed(uint8_t percent_speed)
{
  bsp_brc_pwm_set_duty(percent_speed);
}

uint32_t bsp_brc_pwm_duty_map(uint8_t duty)
{
  if(duty > 100) duty = 100;
  return (uint32_t)ldexp((double)duty, (int)BSP_BRC_PWM_TIMER_RESOLUTION) / 100;
}

/* Private function --------------------------------------------------------- */

/* End of file -------------------------------------------------------- */