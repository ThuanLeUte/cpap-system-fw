/**
* @file       bsp_adc.c
* @copyright  Copyright (C) 2021 Hydratech. All rights reserved.
* @license    This project is released under the Hydratech License.
* @version    01.00.00
* @date       2021-11-06
* @author     Hiep Le
* @brief      BSP (Board Support Package)
* @note       None
* @example    None
*/

/* Includes ----------------------------------------------------------------- */
#include "bsp_adc.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"

/* Private defines ---------------------------------------------------------- */
// static const char *TAG = "bsp_adc";

/* Public variables --------------------------------------------------------- */
#define BSP_ADC_DEFAULT_VREF            (1100)
#define BSP_ADC_NO_OF_SAMPLES           (64)                    // Multisampling

#define BSP_ADC_RESISTER_1_VALUE        (49.9)
#define BSP_ADC_RESISTER_2_VALUE        (100)

#define BSP_ADC_CHANNEL                 ADC_CHANNEL_7           // ADC 1 channel 7 (GPIO35)
#define BSP_ADC_ATTEN                   ADC_ATTEN_DB_11         // Range measurement up to 2600mV
#define BSP_ADC_UNIT                    ADC_UNIT_1              // ADC 1 
#define BSP_ADC_RESOLUTION              ADC_WIDTH_BIT_12        // 12-Bit resolution

/* Private variables -------------------------------------------------------- */
static esp_adc_cal_characteristics_t *m_adc_chars;
// static const adc_channel_t m_adc_channel = ADC_CHANNEL_0;
// static const adc_atten_t m_adc_atten     = ADC_ATTEN_DB_11;
// static const adc_unit_t mA_adc_unit      = ADC_UNIT_1;

/* Private function prototypes ---------------------------------------------- */
/* Function definitions ----------------------------------------------------- */
void bsp_adc_init(void)
{
  adc1_config_width((adc_bits_width_t)BSP_ADC_RESOLUTION);
  adc1_config_channel_atten((adc_channel_t)BSP_ADC_CHANNEL, (adc_atten_t)BSP_ADC_ATTEN);

  // Characterize ADC
  m_adc_chars = calloc(1, sizeof(esp_adc_cal_characteristics_t));
  esp_adc_cal_characterize((adc_unit_t)BSP_ADC_UNIT, 
                           (adc_atten_t)BSP_ADC_ATTEN, 
                           (adc_bits_width_t)BSP_ADC_RESOLUTION, 
                           (uint32_t)BSP_ADC_DEFAULT_VREF, 
                           m_adc_chars);
}

void bsp_adc_get_voltage(uint16_t *voltage)
{
  uint32_t adc_reading = 0;

  // Multisampling
  for (int i = 0; i < BSP_ADC_NO_OF_SAMPLES; i++)
  {
    adc_reading += adc1_get_raw((adc1_channel_t)BSP_ADC_CHANNEL);
  }
  adc_reading /= BSP_ADC_NO_OF_SAMPLES;

  // Convert adc_reading to voltage in mV
  *voltage = (uint16_t)((float)((float)(BSP_ADC_RESISTER_1_VALUE + BSP_ADC_RESISTER_2_VALUE) / BSP_ADC_RESISTER_2_VALUE) *
                        esp_adc_cal_raw_to_voltage(adc_reading, m_adc_chars));
}

/* Private function --------------------------------------------------------- */
/* End of file -------------------------------------------------------- */