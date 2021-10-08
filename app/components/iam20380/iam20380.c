/**
 * @file       iam20380.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-10-08
 * @author     Hiep Le
 * @brief      Driver support IAM20380 (Accelerometer)
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "iam20380.h"

/* Private defines ---------------------------------------------------- */

// DEFINES IAM20380 REGISTERS
#define IAM20380_REG_SELF_TEST_X_GYRO            (0X00)
#define IAM20380_REG_SELF_TEST_Y_GYRO            (0X01)
#define IAM20380_REG_SELF_TEST_Z_GYRO            (0X02)
#define IAM20380_REG_XG_OFFS_USRH                (0X13)
#define IAM20380_REG_XG_OFFS_USRL                (0X14)
#define IAM20380_REG_YG_OFFS_USRH                (0X15)
#define IAM20380_REG_YG_OFFS_USRL                (0X16)
#define IAM20380_REG_ZG_OFFS_USRH                (0X17)
#define IAM20380_REG_ZG_OFFS_USRL                (0X18)
#define IAM20380_REG_SMPLRT_DIV                  (0X19)
#define IAM20380_REG_CONFIG                      (0X1A)
#define IAM20380_REG_GYRO_CONFIG                 (0X1B)
#define IAM20380_REG_LP_MODE_CFG                 (0X1E)
#define IAM20380_REG_FIFO_EN                     (0X23)
#define IAM20380_REG_FSYNC_INT                   (0X36)
#define IAM20380_REG_INT_PIN_CFG                 (0X37)
#define IAM20380_REG_INT_ENABLE                  (0X38)
#define IAM20380_REG_INT_STATUS                  (0X3A)
#define IAM20380_REG_TEMP_OUT_H                  (0X41)
#define IAM20380_REG_TEMP_OUT_L                  (0X42)
#define IAM20380_REG_GYRO_XOUT_H                 (0X43)
#define IAM20380_REG_GYRO_XOUT_L                 (0X44)
#define IAM20380_REG_GYRO_YOUT_H                 (0X45)
#define IAM20380_REG_GYRO_YOUT_L                 (0X46)
#define IAM20380_REG_GYRO_ZOUT_H                 (0X47)
#define IAM20380_REG_GYRO_ZOUT_L                 (0X48)
#define IAM20380_REG_SIGNAL_PATH_RESET           (0X68)
#define IAM20380_REG_USER_CTRL                   (0X6A)
#define IAM20380_REG_PWR_MGMT_1                  (0X6B)
#define IAM20380_REG_PWR_MGMT_2                  (0X6C)
#define IAM20380_REG_FIFO_COUNTH                 (0X72)
#define IAM20380_REG_FIFO_COUNTL                 (0X73)
#define IAM20380_REG_FIFO_R_W                    (0X74)
#define IAM20380_REG_WHO_AM_I                    (0X75)

// DEFINES IAM20380 IDENTIFIER VALUE
#define IAM20380_VALUE_IDENTIFIER                (0xB5)

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
static base_status_t m_iam20380_read_reg(iam20380_t *me, uint8_t reg, uint8_t *p_data, uint32_t len);
static base_status_t m_iam20380_write_reg(iam20380_t *me, uint8_t reg, uint8_t *p_data, uint32_t len);

/* Function definitions ----------------------------------------------- */
base_status_t iam20380_init(iam20380_t *me)
{
  uint8_t identifier;
  uint8_t tmp;

  if ((me == NULL) || (me->i2c_read == NULL) || (me->i2c_write == NULL))
    return BS_ERROR;

  // CHECK IDENTITY
  CHECK_STATUS(m_iam20380_read_reg(me, IAM20380_REG_WHO_AM_I, &identifier, 1));
  CHECK(IAM20380_VALUE_IDENTIFIER == identifier, BS_ERROR);

  // FULL RESET CHIP
  tmp = 0x80;
  CHECK_STATUS(m_iam20380_write_reg(me, IAM20380_REG_PWR_MGMT_1, &tmp, 1));
  me->delay_ms(50);

  // ENABLE TEMP SENSOR - SET CLOCK TO INTERNAL PLL
  tmp = 0x01;
  CHECK_STATUS(m_iam20380_write_reg(me, IAM20380_REG_PWR_MGMT_1, &tmp, 1));
  me->delay_ms(50);

  // ENABLE GYRO X-Y-Z
  tmp = 0x00;
  CHECK_STATUS(m_iam20380_write_reg(me, IAM20380_REG_PWR_MGMT_2, &tmp, 1));
  me->delay_ms(50);

  // SET SAMPLE RATE AT 1000 HZ AND APLLY A SOFTWARE FILTER
  tmp = 0x00;
  CHECK_STATUS(m_iam20380_write_reg(me, IAM20380_REG_SMPLRT_DIV, &tmp, 1));
  me->delay_ms(50);

  // SET DLPF 20HZ AT SAMPLE RATE 1000 HZ
  tmp = 0x04;
  CHECK_STATUS(m_iam20380_write_reg(me, IAM20380_REG_CONFIG, &tmp, 1));
  me->delay_ms(50);

  // SET FULLSCALE = 2000 DPS
  tmp = 0x18;
  CHECK_STATUS(m_iam20380_write_reg(me, IAM20380_REG_GYRO_CONFIG, &tmp, 1));
  me->delay_ms(50);

  // ENABLE INTERRUPT WHEN DATA IS READY
  tmp = 0x01;
  CHECK_STATUS(m_iam20380_write_reg(me, IAM20380_REG_INT_ENABLE, &tmp, 1));
  me->delay_ms(50);

  return BS_OK;
}

base_status_t iam20380_reset(iam20380_t *me)
{
  uint8_t tmp;

  if ((me == NULL) || (me->i2c_read == NULL) || (me->i2c_write == NULL))
    return BS_ERROR;

  tmp = 0x80;
  
  CHECK_STATUS(m_iam20380_write_reg(me, IAM20380_REG_PWR_MGMT_1, &tmp, 1));

  return BS_OK;
}

base_status_t iam20380_get_raw_data(iam20380_t *me, iam20380_data_t *raw_data)
{
  uint8_t data[6];
  uint8_t status;

  if ((me == NULL) || (me->i2c_read == NULL) || (me->i2c_write == NULL))
    return BS_ERROR;

  CHECK_STATUS(m_iam20380_read_reg(me, IAM20380_REG_INT_STATUS, &status, 1));

  status &= 0x01;

  if (status)
  {
    CHECK_STATUS(m_iam20380_read_reg(me, IAM20380_REG_GYRO_XOUT_H, &data, sizeof(data)));

    raw_data->x = ((data[0] << 8) | data[1]);
    raw_data->y = ((data[2] << 8) | data[3]);
    raw_data->z = ((data[4] << 8) | data[5]);
  }
  else
  {
    return BS_ERROR;
  }

  return BS_OK;
}

base_status_t iam20380_get_gyro_angle(iam20380_t *me, iam20380_data_t *raw_data, iam20380_angle_t *angle)
{
  if ((me == NULL) || (me->i2c_read == NULL) || (me->i2c_write == NULL))
    return BS_ERROR;

  CHECK_STATUS(iam20380_get_sensitivity(me));

  angle->x_angle = (float)(raw_data->x) / me->sensitivity;
  angle->y_angle = (float)(raw_data->y) / me->sensitivity;
  angle->z_angle = (float)(raw_data->z) / me->sensitivity;

  return BS_OK;
}

base_status_t iam20380_get_sensitivity(iam20380_t *me)
{
  uint8_t data;

  if ((me == NULL) || (me->i2c_read == NULL) || (me->i2c_write == NULL))
    return BS_ERROR;

  CHECK_STATUS(m_iam20380_read_reg(me, IAM20380_REG_GYRO_CONFIG, &data, 1);

  data &= (0x03 << 3);
  data >>= 3;

  switch (data)
  {
    case 0x00:
      me->sensitivity = 131.0;
      break;

    case 0x01:
      me->sensitivity = 65.5;
      break;

    case 0x02:
      me->sensitivity = 32.8;  
      break;

    case 0x03:
      me->sensitivity = 16.4;
      break;

    default:
      break;
  }

  return BS_OK;
}

base_status_t iam20380_set_fullscale(iam20380_t *me, iam20380_fullscale_t scale)
{
  uint8_t tmp;

  if ((me == NULL) || (me->i2c_read == NULL) || (me->i2c_write == NULL))
    return BS_ERROR;

  switch (scale)
  {
    case IAM20380_GYRO_RANGE_250_DPS:
      CHECK_STATUS(m_iam20380_read_reg(me, IAM20380_REG_GYRO_CONFIG, &tmp, 1));
      tmp &= ~((0x03) << 3);
      CHECK_STATUS(m_iam20380_write_reg(me, IAM20380_REG_GYRO_CONFIG, &tmp, 1));
      break;

    case IAM20380_GYRO_RANGE_500_DPS:
      CHECK_STATUS(m_iam20380_read_reg(me, IAM20380_REG_GYRO_CONFIG, &tmp, 1));
      tmp &= ~((0x03) << 3);
      tmp |= (0x01 << 3);
      CHECK_STATUS(m_iam20380_write_reg(me, IAM20380_REG_GYRO_CONFIG, &tmp, 1));
      break;

    case IAM20380_GYRO_RANGE_1000_DPS:
      CHECK_STATUS(m_iam20380_read_reg(me, IAM20380_REG_GYRO_CONFIG, &tmp, 1));
      tmp &= ~((0x03) << 3);
      tmp |= (0x02 << 3);
      CHECK_STATUS(m_iam20380_write_reg(me, IAM20380_REG_GYRO_CONFIG, &tmp, 1));
      break;

    case IAM20380_GYRO_RANGE_2000_DPS:
      CHECK_STATUS(m_iam20380_read_reg(me, IAM20380_REG_GYRO_CONFIG, &tmp, 1));
      tmp |= (0x03 << 3);
      CHECK_STATUS(m_iam20380_write_reg(me, IAM20380_REG_GYRO_CONFIG, &tmp, 1));
      break;

    default:
      break;
  }

  return BS_OK;
}

/* Private function definitions ---------------------------------------- */
/**
 * @brief         IAM20380 read register
 *
 * @param[in]     me      Pointer to handle of IAM20380 module.
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
static base_status_t m_iam20380_read_reg(iam20380_t *me, uint8_t reg, uint8_t *p_data, uint32_t len)
{
  CHECK(0 == me->i2c_read(me->device_address, reg, p_data, len), BS_ERROR);

  return BS_OK;
}

/**
 * @brief         IAM20380 read register
 *
 * @param[in]     me      Pointer to handle of IAM20380 module.
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
static base_status_t m_iam20380_write_reg(iam20380_t *me, uint8_t reg, uint8_t *p_data, uint32_t len)
{
  CHECK(0 == me->i2c_write(me->device_address, reg, p_data, len), BS_ERROR);

  return BS_OK;
}

/* End of file -------------------------------------------------------- */