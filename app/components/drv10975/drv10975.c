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
// DEFINES DRV10975 REGISTERS
#define DRV10975_REG_SPEEDCTRL1                   (0X00)
#define DRV10975_REG_SPEEDCTRL2                   (0X01)
#define DRV10975_REG_DEVCTRL                      (0X02)
#define DRV10975_REG_EECTRL                       (0X03)
#define DRV10975_REG_STATUS                       (0X10)
#define DRV10975_REG_MOTORSPEED1                  (0X11)
#define DRV10975_REG_MOTORSPEED2                  (0X12)
#define DRV10975_REG_MOTORPERIOD1                 (0X13)
#define DRV10975_REG_MOTORPERIOD2                 (0X14)
#define DRV10975_REG_MOTORKT1                     (0X15)
#define DRV10975_REG_MOTORKT2                     (0X16)
#define DRV10975_REG_MOTORCURRENT1                (0X17)
#define DRV10975_REG_MOTORCURRENT2                (0X18)
#define DRV10975_REG_IPDPOSITION                  (0X19)
#define DRV10975_REG_SUPPLYVOLTAGE                (0X1A)
#define DRV10975_REG_SPEEDCMD                     (0X1B)
#define DRV10975_REG_SPDCMDBUFFER                 (0X1C)
#define DRV10975_REG_FAULTCODE                    (0X1E)
#define DRV10975_REG_MOTORPARAM1                  (0X20)
#define DRV10975_REG_MOTORPARAM2                  (0X21)
#define DRV10975_REG_MOTORPARAM3                  (0X22)
#define DRV10975_REG_SYSOPT1                      (0X23)
#define DRV10975_REG_SYSOPT2                      (0X24)
#define DRV10975_REG_SYSOPT3                      (0X25)
#define DRV10975_REG_SYSOPT4                      (0X26)
#define DRV10975_REG_SYSOPT5                      (0X27)
#define DRV10975_REG_SYSOPT6                      (0X28)
#define DRV10975_REG_SYSOPT7                      (0X29)
#define DRV10975_REG_SYSOPT8                      (0X2A)
#define DRV10975_REG_SYSOPT9                      (0X2B)

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
static base_status_t m_drv10975_read_reg(drv10975_t *me, uint8_t reg, uint8_t *p_data, uint32_t len);
static base_status_t m_drv10975_write_reg(drv10975_t *me, uint8_t reg, uint8_t *p_data, uint32_t len);

/* Function definitions ----------------------------------------------- */
base_status_t drv10975_init(drv10975_t *me)
{
  uint8_t tmp;

  if ((me == NULL) || (me->i2c_read == NULL) || (me->i2c_write == NULL))
    return BS_ERROR;

  

  return BS_OK;
}

base_status_t drv10975_enable_i2c_mode(drv10975_t *me)
{
  uint8_t tmp;

  if ((me == NULL) || (me->i2c_read == NULL) || (me->i2c_write == NULL))
    return BS_ERROR;

  CHECK_STATUS(m_drv10975_read_reg(me, DRV10975_REG_SPEEDCTRL2, &tmp, 1));
  tmp |= 0x80;
  CHECK_STATUS(m_drv10975_write_reg(me, DRV10975_REG_SPEEDCTRL2, &tmp, 1));

  return BS_OK;
}

base_status_t drv10975_set_speed(drv10975_t *me)
{
  uint8_t tmp;

  if ((me == NULL) || (me->i2c_read == NULL) || (me->i2c_write == NULL))
    return BS_ERROR;

  CHECK_STATUS(m_drv10975_read_reg(me, DRV10975_REG_SPEEDCTRL2, &tmp, 1));
  tmp &= 0x80;

  if(tmp)
  {
    if(me->motor_speed > 0x01FF) me->motor_speed = 0x01FF;

    tmp = ((me->motor_speed) >> 8) | 0x80;
    CHECK_STATUS(m_drv10975_write_reg(me, DRV10975_REG_SPEEDCTRL2, &tmp, 1));

    tmp = me->motor_speed;
    CHECK_STATUS(m_drv10975_write_reg(me, DRV10975_REG_SPEEDCTRL1, &tmp, 1));
  }
  else 
  {
    return BS_ERROR;
  }

  return BS_OK;
}

base_status_t drv10975_get_motor_frequency(drv10975_t *me, drv10975_data_t data)
{
  uint8_t tmp[2];

  if ((me == NULL) || (me->i2c_read == NULL) || (me->i2c_write == NULL))
    return BS_ERROR;

  CHECK_STATUS(m_drv10975_read_reg(me, DRV10975_REG_MOTORSPEED1, &tmp, sizeof(tmp)));

  data->motor_frequency = (tmp[0] << 8 | tmp[1]) / 10;
  
  return BS_OK;
}

base_status_t drv10975_get_motor_period(drv10975_t *me, drv10975_data_t data)
{
  uint8_t tmp[2];

  if ((me == NULL) || (me->i2c_read == NULL) || (me->i2c_write == NULL))
    return BS_ERROR;

  CHECK_STATUS(m_drv10975_read_reg(me, DRV10975_REG_MOTORPERIOD1, &tmp, sizeof(tmp)));

  data->motor_period = (tmp[0] << 8 | tmp[1]) * 10;

  return BS_OK;
}

base_status_t drv10975_get_motor_current(drv10975_t *me, drv10975_data_t data)
{
  uint8_t tmp[2];

  if ((me == NULL) || (me->i2c_read == NULL) || (me->i2c_write == NULL))
    return BS_ERROR;

  CHECK_STATUS(m_drv10975_read_reg(me, DRV10975_REG_MOTORCURRENT1, &tmp, sizeof(tmp)));

  data->motor_current = (((tmp[0] << 8) & 0x07) | tmp[1]);

  if(data->motor_current >= 1023)
  {
    data->motor_current = 3 * ((data->motor_current - 1023) / 512);
  }
  else
  {
    data->motor_current = 3 * ((data->motor_current) / 512);
  }

  return BS_OK;
}

base_status_t drv10975_get_supply_voltage(drv10975_t *me, drv10975_data_t data)
{
  uint8_t tmp;

  if ((me == NULL) || (me->i2c_read == NULL) || (me->i2c_write == NULL))
    return BS_ERROR;

  CHECK_STATUS(m_drv10975_read_reg(me, DRV10975_REG_SUPPLYVOLTAGE, &tmp, 1);

  data->motor_supply_voltage = tmp * 22.8 / 256;

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
 * @param[in]     p_data  Pointer to handle of data
 * @param[in]     len     Data length
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
static base_status_t m_drv10975_write_reg(drv10975_t *me, uint8_t reg, uint8_t *p_data, uint32_t len)
{
  CHECK(0 == me->i2c_write(me->device_address, reg, p_data, len), BS_ERROR);

  return BS_OK;
}

/* End of file -------------------------------------------------------- */