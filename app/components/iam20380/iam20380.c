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
// IAM20380 registers
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

// IAM20380 identifier value
#define IAM20380_VALUE_IDENTIFIER                (0xB5)

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
static base_status_t m_iam20380_read_reg(iam20380_t *me, uint8_t reg, uint8_t *p_data, uint32_t len);
static base_status_t m_iam20380_write_reg(iam20380_t *me, uint8_t reg, uint8_t *p_data, uint32_t len);
static base_status_t m_iam20380_write_one_byte(iam20380_t *me, uint8_t reg, uint8_t data);

/* Function definitions ----------------------------------------------- */
base_status_t iam20380_init(iam20380_t *me)
{
  uint8_t identifier;
  uint8_t tmp;

  if ((me == NULL) || (me->i2c_read == NULL) || (me->i2c_write == NULL || (me->delay_ms == NULL))
    return BS_ERROR_PARAMS;

  CHECK_STATUS(m_iam20380_read_reg(me, IAM20380_REG_WHO_AM_I, &identifier, 1)); // IAM20380 check identity
  CHECK(IAM20380_VALUE_IDENTIFIER == identifier, BS_ERROR); 

  CHECK_STATUS(iam20380_config(me)); // IAM20380 config
  return BS_OK;
}

base_status_t iam20380_config(iam20380_t *me)
{
  uint8_t tmp;
  
  tmp = 0x80;
  CHECK_STATUS(m_iam20380_write_reg(me, IAM20380_REG_PWR_MGMT_1, &tmp, 1)); // reset chip, disable sleep mode, disable low power mode
  me->delay_ms(50);

  tmp = 0x01;
  CHECK_STATUS(m_iam20380_write_reg(me, IAM20380_REG_PWR_MGMT_1, &tmp, 1)); // enable temp sensor - set clock to internal PLL
  me->delay_ms(50);
  
  tmp = 0x00;
  CHECK_STATUS(m_iam20380_write_reg(me, IAM20380_REG_PWR_MGMT_2, &tmp, 1)); // enable x - y - z axis
  me->delay_ms(50);

  tmp = me->config.sample_rate;
  CHECK_STATUS(m_iam20380_write_reg(me, IAM20380_REG_SMPLRT_DIV, &tmp, 1)); // set sample rate 
  me->delay_ms(50);

  tmp = me->config.digi_low_pass_filter;
  CHECK_STATUS(m_iam20380_write_reg(me, IAM20380_REG_CONFIG, &tmp, 1)); // set digital low pass filter
  me->delay_ms(50);

  tmp = (me->config.fullscale << 3) & 0x18;
  CHECK_STATUS(m_iam20380_write_reg(me, IAM20380_REG_GYRO_CONFIG, &tmp, 1)); // set fulscale 
  me->delay_ms(50);

  tmp = 0x01;
  CHECK_STATUS(m_iam20380_write_reg(me, IAM20380_REG_INT_ENABLE, &tmp, 1));  // enable interrupt when data is ready
  me->delay_ms(50);

  return BS_OK;
}

base_status_t iam20380_get_raw_data(iam20380_t *me)
{ 
  uint8_t data[6];
  uint8_t status;

  CHECK_STATUS(m_iam20380_read_reg(me, IAM20380_REG_INT_STATUS, &status, 1));

  if (status & 0x01)
  {
    CHECK_STATUS(m_iam20380_read_reg(me, IAM20380_REG_GYRO_XOUT_H, data, sizeof(data)));

    me->data.raw_data.x = ((data[0] << 8) | data[1]);
    me->data.raw_data.y = ((data[2] << 8) | data[3]);
    me->data.raw_data.z = ((data[4] << 8) | data[5]);
  }
  else
  {
    return BS_ERROR;
  }

  return BS_OK;
}

base_status_t iam20380_get_gyro_angle(iam20380_t *me)
{
  CHECK_STATUS(iam20380_get_sensitivity(me));
  CHECK_STATUS(iam20380_get_raw_data(me);

  me->data.angle.x = (float)(me->data.raw_data.x) / me->data.sensitivity;
  me->data.angle.y = (float)(me->data.raw_data.y) / me->data.sensitivity;
  me->data.angle.z = (float)(me->data.raw_data.z) / me->data.sensitivity;

  return BS_OK;
}

base_status_t iam20380_get_sensitivity(iam20380_t *me)
{
  switch (me->config.fullscale)
  {
    case IAM20380_FULLSCALE_250_DPS : me->data.sensitivity = 131.0; break;
    case IAM20380_FULLSCALE_500_DPS : me->data.sensitivity = 65.5;  break;
    case IAM20380_FULLSCALE_1000_DPS: me->data.sensitivity = 32.8;  break;
    case IAM20380_FULLSCALE_2000_DPS: me->data.sensitivity = 16.4;  break;
    default : break;
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
 * @brief         IAM20380 write register
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

/**
 * @brief         IAM20380 write one byte
 *
 * @param[in]     me      Pointer to handle of IAM20380 module.
 * @param[in]     reg     Register
 * @param[in]     data    Data
 *
 * @attention     None
 *
 * @return
 * - BS_OK
 * - BS_ERROR
 */
static base_status_t m_iam20380_write_one_byte(iam20380_t *me, uint8_t reg, uint8_t data)
{
  CHECK(0 == me->i2c_write(me->device_address, reg, data, 1), BS_ERROR);

  return BS_OK;
}

/* End of file -------------------------------------------------------- */