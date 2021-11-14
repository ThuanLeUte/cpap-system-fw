/**
 * @file       bsp_io_10.h
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-10-26
 * @author     Hiep Le
 * @brief      Board Support Package IO (BSP)
 * @note       None
 * @example    None
 */

/* Define to prevent recursive inclusion ------------------------------ */
#ifndef __BSP_IO_10_H
#define __BSP_IO_10_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ----------------------------------------------------------- */
#include <stdint.h>
#include <stdbool.h>

/* Public defines ----------------------------------------------------- */
// #define IO_UART0_TX                     (1)     // UART TX signal pin
// #define IO_UART0_RX                     (3)     // UART RX signal pin
// #define IO_RTC_INT                      (5)     // PCF85063 interrupt pin
// #define IO_FLASH_CLK                    (6)     // GD25Q64 clock pin
// #define IO_FLASH_MISO                   (7)     // GD25Q64 SPI MISO signal pin
// #define IO_FLASH_MOSI                   (8)     // GD25Q64 SPI MOSI signal pin
// #define IO_FLASH_CS                     (11)    // GD25Q64 SPI chip select pin
// #define IO_FLASH_HOLD                   (17)    // GD25Q64 hold pin
// #define IO_FLASH_WP                     (26)    // GD25Q64 write protection pin
// #define IO_I2C_SDA                      (9)     // SDA signal pin
// #define IO_I2C_SCL                      (10)    // SCL signal pin
// #define IO_GYRO_INT                     (13)    // IAM20380 interrupt pin
// #define IO_PM_ALERT                     (12)    // PAC1934 alert pin
// #define IO_PM_PWRDN                     (15)    // PAC1934 power down 
// #define IO_BRC_SPEED                    (14)    // DRV10975 speed control pin
// #define IO_BRC_FG                       (23)    // DRV10975 motor speed feedback pin
// #define IO_BRC_POWER                    (25)    // DRV10975 power supply trigger pin
// #define IO_BRC_DIR                      (27)    // DRV10975 motor direction control pin
// #define IO_BUZZER                       (16)    // Buzzer control pin                           
// #define IO_THERM                        (18)    // Thermistor signal pin
// #define IO_LED_GREEN                    (19)    // LED green control pin
// #define IO_LED_RED                      (22)    // LED red control pin 
// #define IO_POWER_LATCH                  (21)    // Power supply latch pin
// #define IO_POWER_KEY                    (34)    // Button power/function pin
// #define IO_BAT_LEVEL                    (35)    // Battery voltage measure pin      

#define IO_UART0_TX                     (1)     // UART TX signal pin
#define IO_UART0_RX                     (3)     // UART RX signal pin
#define IO_RTC_INT                      (5)     // PCF85063 interrupt pin
#define IO_FLASH_CLK                    (6)     // GD25Q64 clock pin
#define IO_FLASH_MISO                   (7)     // GD25Q64 SPI MISO signal pin
#define IO_FLASH_MOSI                   (8)     // GD25Q64 SPI MOSI signal pin
#define IO_FLASH_CS                     (11)    // GD25Q64 SPI chip select pin
#define IO_FLASH_HOLD                   (17)    // GD25Q64 hold pin
#define IO_FLASH_WP                     (26)    // GD25Q64 write protection pin
#define IO_I2C_SDA                      (9)     // SDA signal pin
#define IO_I2C_SCL                      (10)    // SCL signal pin
#define IO_GYRO_INT                     (13)    // IAM20380 interrupt pin
#define IO_PM_ALERT                     (12)    // PAC1934 alert pin
#define IO_PM_PWRDN                     (15)    // PAC1934 power down 
#define IO_BRC_SPEED                    (14)    // DRV10975 speed control pin
#define IO_BRC_FG                       (23)    // DRV10975 motor speed feedback pin
#define IO_BRC_POWER                    (25)    // DRV10975 power supply trigger pin
#define IO_BRC_DIR                      (27)    // DRV10975 motor direction control pin
#define IO_BUZZER                       (16)    // Buzzer control pin                           
#define IO_THERM                        (18)    // Thermistor signal pin
#define IO_LED_GREEN                    (19)    // LED green control pin
#define IO_LED_RED                      (22)    // LED red control pin 
#define IO_POWER_LATCH                  (21)    // Power supply latch pin
#define IO_POWER_KEY                    (34)    // Button power/function pin
#define IO_BAT_LEVEL                    (35)    // Battery voltage measure pin      

/* Public enumerate/structure ----------------------------------------- */
/* Public macros ------------------------------------------------------ */
/* Public variables --------------------------------------------------- */
/* Public function prototypes ----------------------------------------- */
/* -------------------------------------------------------------------------- */
#ifdef __cplusplus
} // extern "C"
#endif
#endif // __BSP_IO_10_H

/* End of file -------------------------------------------------------- */