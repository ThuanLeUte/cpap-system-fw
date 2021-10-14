/**
 * @file       drv10975.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-10-09
 * @author     Hiep Le
 * @brief      Driver support DRV10975 (Brushless Motor Driver)
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "drv10975.h"

/* Private defines ---------------------------------------------------- */
// DRV10975 Registers
#define DRV10975_REG_SPEED_CTRL1                   (0X00)
#define DRV10975_REG_SPEED_CTRL2                   (0X01)
#define DRV10975_REG_DEV_CTRL                      (0X02)
#define DRV10975_REG_EE_CTRL                       (0X03)
#define DRV10975_REG_STATUS                        (0X10)
#define DRV10975_REG_MOTOR_SPEED1                  (0X11)
#define DRV10975_REG_MOTOR_SPEED2                  (0X12)
#define DRV10975_REG_MOTOR_PERIOD1                 (0X13)
#define DRV10975_REG_MOTOR_PERIOD2                 (0X14)
#define DRV10975_REG_MOTOR_KT1                     (0X15)
#define DRV10975_REG_MOTOR_KT2                     (0X16)
#define DRV10975_REG_MOTOR_CURRENT1                (0X17)
#define DRV10975_REG_MOTOR_CURRENT2                (0X18)
#define DRV10975_REG_IPD_POSITION                  (0X19)
#define DRV10975_REG_SUPPLY_VOLTAGE                (0X1A)
#define DRV10975_REG_SPEED_CMD                     (0X1B)
#define DRV10975_REG_SPD_CMD_BUFFER                (0X1C)
#define DRV10975_REG_FAULT_CODE                    (0X1E)
#define DRV10975_REG_MOTOR_PARAM1                  (0X20)
#define DRV10975_REG_MOTOR_PARAM2                  (0X21)
#define DRV10975_REG_MOTOR_PARAM3                  (0X22)
#define DRV10975_REG_SYS_OPT1                      (0X23)
#define DRV10975_REG_SYS_OPT2                      (0X24)
#define DRV10975_REG_SYS_OPT3                      (0X25)
#define DRV10975_REG_SYS_OPT4                      (0X26)
#define DRV10975_REG_SYS_OPT5                      (0X27)
#define DRV10975_REG_SYS_OPT6                      (0X28)
#define DRV10975_REG_SYS_OPT7                      (0X29)
#define DRV10975_REG_SYS_OPT8                      (0X2A)
#define DRV10975_REG_SYS_OPT9                      (0X2B)

// DRV10975 direction 
#define DRV10975_FORWARD_DIRECTION                 (0)
#define DRV10975_REVERSE_DIRECTION                 (1)

// DRV10975 direction 
#define DRV10975_MOTOR_MAX_SPEED                   (0x1FF)

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
static base_status_t m_drv10975_read_reg(drv10975_t *me, uint8_t reg, uint8_t *p_data, uint32_t len);
static base_status_t m_drv10975_write_reg(drv10975_t *me, uint8_t reg, uint8_t *p_data, uint32_t len);
static uint16_t m_drv10975_modifed_map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max);

/* Function definitions ----------------------------------------------- */
base_status_t drv10975_init(drv10975_t *me)
{
  if ((me == NULL) || (me->i2c_read == NULL) || (me->i2c_write == NULL) || (me->delay_ms == NULL))
    return BS_ERROR;

  CHECK_STATUS(m_drv10975_write_reg(me, DRV10975_REG_EE_CTRL, 0X40)); // Enable the writing to configuration register

  CHECK_STATUS(m_drv10975_write_reg(me, DRV10975_REG_MOTOR_PARAM1, 0x39)); // Set motor resistance

  CHECK_STATUS(m_drv10975_write_reg(me, DRV10975_REG_MOTOR_PARAM2, 0x1E)); // Set BEMF constant

  CHECK_STATUS(m_drv10975_write_reg(me, DRV10975_REG_MOTOR_PARAM3, 0x3A)); // Set LRTIME

  CHECK_STATUS(m_drv10975_write_reg(me, DRV10975_REG_SYS_OPT1, 0x08)); // ISD enable

  CHECK_STATUS(m_drv10975_write_reg(me, DRV10975_REG_SYS_OPT2, 0x50)); // Open loop current setting                               

  CHECK_STATUS(m_drv10975_write_reg(me, DRV10975_REG_SYS_OPT3, 0xDA)); // Open loop accelerate setting                              

  CHECK_STATUS(m_drv10975_write_reg(me, DRV10975_REG_SYS_OPT4, 0xB8)); // Open to closed loop threshold & Align time                                           

  CHECK_STATUS(m_drv10975_write_reg(me, DRV10975_REG_SYS_OPT5, 0x10)); // Lock detection current limit. Enabled when high

  CHECK_STATUS(m_drv10975_write_reg(me, DRV10975_REG_SYS_OPT6, 0x27)); // Acceleration current limit threshold

  CHECK_STATUS(m_drv10975_write_reg(me, DRV10975_REG_SYS_OPT7, 0x37)); // Closed loop accelerate                                              

  CHECK_STATUS(m_drv10975_write_reg(me, DRV10975_REG_SYS_OPT8, 0x04)); // No IPD function, Buck regulator voltage select = 3.3V

  CHECK_STATUS(m_drv10975_write_reg(me, DRV10975_REG_SYS_OPT9, 0x0C)); // Kt_high = 2Kt. Kt_low = 1/2Kt, Analog input expected at SPEED pin

  CHECK_STATUS(m_drv10975_write_reg(me, DRV10975_REG_DEV_CTRL, 0xB6)); //                                    

  CHECK_STATUS(m_drv10975_write_reg(me, DRV10975_REG_EE_CTRL, 0x50)); //  Enable program the EEPROM                     

  CHECK_STATUS(drv10975_set_motor_speed(me, 0)); // Set motor speed = 0 

  return BS_OK;
}

base_status_t drv10975_forward_direction(drv10975_t *me)
{
  me->gpio_write(IO_DRV_DIR, DRV10975_FORWARD_DIRECTION);

  return BS_OK;
}

base_status_t drv10975_reverse_direction(drv10975_t *me)
{
  me->gpio_write(IO_DRV_DIR, DRV10975_REVERSE_DIRECTION);

  return BS_OK;
}

base_status_t drv10975_set_motor_speed(drv10975_t *me, uint16_t percent_speed)
{
  uint8_t tmp;

  if(percent_speed > 100) percent_speed = 100;

  me->value.speed = m_drv10975_modifed_map(percent_speed, 0, 100, 0, DRV10975_MOTOR_MAX_SPEED);

  tmp = (uint8_t)(me->value.speed);
  CHECK_STATUS(m_drv10975_write_reg(me, DRV10975_REG_SPEED_CTRL1, tmp));
  me->delay_ms(1);
  
  tmp = (uint8_t)(((me->value.speed >> 8) & 0x01) | 0x80);
  CHECK_STATUS(m_drv10975_write_reg(me, DRV10975_REG_SPEED_CTRL2, tmp));

  return BS_OK;
}

base_status_t drv10975_get_motor_velocity(drv10975_t *me)
{
  uint8_t tmp[2];

  CHECK_STATUS(m_drv10975_read_reg(me, DRV10975_REG_MOTOR_SPEED1, &tmp, sizeof(tmp)));

  me->value.velocity = (float)((tmp[0] << 8 | tmp[1]) / 10.0);
  
  return BS_OK;
}

base_status_t drv10975_get_motor_period(drv10975_t *me)
{
  uint8_t tmp[2];

  CHECK_STATUS(m_drv10975_read_reg(me, DRV10975_REG_MOTOR_PERIOD1, &tmp, sizeof(tmp)));

  me->value.period = (float)((tmp[0] << 8 | tmp[1]) * 10);

  return BS_OK;
}

base_status_t drv10975_get_motor_supply_voltage(drv10975_t *me)
{
  uint8_t tmp;

  CHECK_STATUS(m_drv10975_read_reg(me, DRV10975_REG_SUPPLY_VOLTAGE, &tmp, 1);

  me->value.supply_voltage = (float)(tmp * 22.8 / 256.0);

  return BS_OK;
}

base_status_t drv10975_get_motor_current(drv10975_t *me)
{
  uint8_t tmp[2];
  uint16_t current;

  CHECK_STATUS(m_drv10975_read_reg(me, DRV10975_REG_MOTOR_CURRENT1, &tmp, sizeof(tmp)));

  current = (((tmp[0] & 0x07) << 8) | tmp[1]);

  if(current >= 0x3FF)
  {
    me->value.current = (float)((current - 0x3FF) * 170.67);
  }
  else
  {
    me->value.current = (float)(current * 170.67);
  }

  return BS_OK;
}

base_status_t drv10975_check_over_temp(drv10975_t *me)
{
  uint8_t tmp;

  CHECK_STATUS(m_drv10975_read_reg(me, DRV10975_REG_STATUS, &tmp, 1);

  me->status = tmp & 0x80;

  return BS_OK;
}

base_status_t drv10975_check_sleep_mode(drv10975_t *me)
{
  uint8_t tmp;

  CHECK_STATUS(m_drv10975_read_reg(me, DRV10975_REG_STATUS, &tmp, 1);

  me->status = tmp & 0x40;

  return BS_OK;
}

base_status_t drv10975_check_over_current(drv10975_t *me)
{
  uint8_t tmp;

  CHECK_STATUS(m_drv10975_read_reg(me, DRV10975_REG_STATUS, &tmp, 1);

  me->status = tmp & 0x20;

  return BS_OK;
}

base_status_t drv10975_check_motor_lock(drv10975_t *me)
{
  uint8_t tmp;

  CHECK_STATUS(m_drv10975_read_reg(me, DRV10975_REG_STATUS, &tmp, 1);

  me->status = tmp & 0x10;

  return BS_OK;
}

/* Private function definitions ---------------------------------------- */
/**
 * @brief         DRV10975 read register
 *
 * @param[in]     me      Pointer to handle of DRV10975 module.
 * @param[in]     reg     Register
 * @param[in]     p_data  Pointer to handle of data
 * @param[in]     len     Data length
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
static base_status_t m_drv10975_read_reg(drv10975_t *me, uint8_t reg, uint8_t *p_data, uint32_t len)
{
  CHECK(0 == me->i2c_read(me->device_address, reg, p_data, len), BS_ERROR);

  return BS_OK;
}

/**
 * @brief         DRV10975 read register
 *
 * @param[in]     me      Pointer to handle of DRV10975 module.
 * @param[in]     reg     Register
 * @param[in]     data    Data to write
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
static base_status_t m_drv10975_write_reg(drv10975_t *me, uint8_t reg, uint8_t data)
{
  CHECK(0 == me->i2c_write(me->device_address, reg, &data, 1), BS_ERROR);

  return BS_OK;
}

/**
 * @brief         DRV10975 map number
 *
 * @param[in]     me        Pointer to handle of DRV10975 module.
 * @param[in]     x         Number want to map
 * @param[in]     in_min    Input range min
 * @param[in]     in_max    Input range max
 * @param[in]     out_min   Output range min
 * @param[in]     out_max   Output range max
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
static uint16_t m_drv10975_modifed_map(uint16_t x, uint16_t in_min, uint16_t in_max,
                                   uint16_t out_min, uint16_t out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/* End of file -------------------------------------------------------- */