// /**
// * @file       bsp_i2c.c
// * @copyright  Copyright (C) 2021 Hydratech. All rights reserved.
// * @license    This project is released under the Hydratech License.
// * @version    01.00.00
// * @date       2021-11-07
// * @author     Hiep Le
// * @brief      BSP (Board Support Package)
// * @note       None
// * @example    None
// */

// /* Includes ----------------------------------------------------------------- */
// #include "bsp_i2c.h"
// #include "driver/gpio.h"
// #include "sys_damos_ram.h"

// /* Private defines ---------------------------------------------------------- */
// // static const char *TAG = "bsp_i2c";
// static i2c_bus_handle_t m_i2c_hdl;

// /* Public variables --------------------------------------------------------- */
// /* Private variables -------------------------------------------------------- */
// /* Private function prototypes ---------------------------------------------- */
// static inline esp_err_t bsp_i2c_init(void);

// /* Function definitions ----------------------------------------------------- */
// int bsp_i2c_write(uint8_t slave_addr, uint8_t reg, uint8_t *p_data, uint16_t len)
// {
//   int ret = 0;
//   ret =  i2c_bus_write_bytes(m_i2c_hdl, slave_addr, &reg, sizeof(reg), p_data, len);
//   if (ret != 0)
//   {
//     ESP_LOGE(TAG, "i2c 0 error: %d. Restart i2c.", ret);
//     i2c_bus_delete(m_i2c_hdl);
//     bsp_i2c_init();
//     ret = i2c_bus_write_bytes(m_i2c_hdl, slave_addr, &reg, sizeof(reg), p_data, len);
//   }
//   return ret;
// }

// int bsp_i2c_read(uint8_t slave_addr, uint8_t reg, uint8_t *p_data, uint16_t len)
// {
//   int ret = 0;
//   ret = i2c_bus_read_bytes(m_i2c_hdl, slave_addr, &reg, sizeof(reg), p_data, len);
//   if (ret != 0)
//   {
//     ESP_LOGE(TAG, "i2c 0 error: %d. Restart i2c.", ret);
//     i2c_bus_delete(m_i2c_hdl);
//     bsp_i2c_init();
//     ret = i2c_bus_read_bytes(m_i2c_hdl, slave_addr, &reg, sizeof(reg), p_data, len);
//   }
//   return ret;
// }

// /* Private function definitions--------------------------------------------------------- */
// static inline esp_err_t bsp_i2c_init(void)
// {
//   esp_err_t res = 0;
//   i2c_config_t es_i2c_cfg = 
//   {
//     .mode             = I2C_MODE_MASTER,
//     .sda_io_num       = IO_I2C_SDA,
//     .scl_io_num       = IO_I2C_SCL,
//     .sda_pullup_en    = GPIO_PULLUP_ENABLE,
//     .scl_pullup_en    = GPIO_PULLUP_ENABLE,
//     .master.clk_speed = 400000
//   };

//   m_i2c_hdl = i2c_bus_create(I2C_NUM_0, &es_i2c_cfg);
//   i2c_set_timeout(I2C_NUM_0, 0xfffff);

//   return res;
// }

// /* End of file -------------------------------------------------------- */