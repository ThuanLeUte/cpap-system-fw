/**
 * @file       pac1934.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-10-07
 * @author     Hiep Le
 * @brief      Driver support PAC1934 (Multi Channel Power Monitor)
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "pac1934.h"

/* Private defines ---------------------------------------------------- */
// DEFINES PAC1934 REGISTERS
#define PAC1934_REG_REFRESH          (0x00)
#define PAC1934_REG_PAC_CTRL         (0x01)
#define PAC1934_REG_ACC_COUNT        (0x02)
#define PAC1934_REG_VPOWER1_ACC      (0x03)
#define PAC1934_REG_VPOWER2_ACC      (0x04)
#define PAC1934_REG_VPOWER3_ACC      (0x05)
#define PAC1934_REG_VPOWER4_ACC      (0x06)
#define PAC1934_REG_VBUS1            (0x07)
#define PAC1934_REG_VBUS2            (0x08)
#define PAC1934_REG_VBUS3            (0x09)
#define PAC1934_REG_VBUS4            (0x0A)
#define PAC1934_REG_VSENSE1          (0x0B)
#define PAC1934_REG_VSENSE2          (0x0C)
#define PAC1934_REG_VSENSE3          (0x0D)
#define PAC1934_REG_VSENSE4          (0x0E)
#define PAC1934_REG_VBUS1_AVG        (0x0F)
#define PAC1934_REG_VBUS2_AVG        (0x10)
#define PAC1934_REG_VBUS3_AVG        (0x11)
#define PAC1934_REG_VBUS4_AVG        (0x12)
#define PAC1934_REG_VSENSE1_AVG      (0x13)
#define PAC1934_REG_VSENSE2_AVG      (0x14)
#define PAC1934_REG_VSENSE3_AVG      (0x15)
#define PAC1934_REG_VSENSE4_AVG      (0x16)
#define PAC1934_REG_VPOWER1          (0x17)
#define PAC1934_REG_VPOWER2          (0x18)
#define PAC1934_REG_VPOWER3          (0x19)
#define PAC1934_REG_VPOWER4          (0x1A)
#define PAC1934_REG_CHANNEL_DIS      (0x1C)
#define PAC1934_REG_NEG_PWR          (0x1D)
#define PAC1934_REG_REFRESH_G        (0X1E)
#define PAC1934_REG_REFRESH_V        (0X1F)
#define PAC1934_REG_SLOW             (0X20)
#define PAC1934_REG_CTRL_ACT         (0X21)
#define PAC1934_REG_CHANNEL_DIS_ACT  (0X22)
#define PAC1934_REG_NEG_PWR_ACT      (0X23)
#define PAC1934_REG_CTRL_LAT         (0X24)
#define PAC1934_REG_CHANNEL_DIS_LAT  (0X25)
#define PAC1934_REG_NEG_PWR_LAT      (0X26)
#define PAC1934_REG_PID              (0XFD)
#define PAC1934_REG_MID              (0XFE)
#define PAC1934_REG_REV              (0XFF)

// DEFINES PAC1934 READ/WRITE I2C ADDRESS
#define PAC1934_I2C_ADDR_WRITE	     (0x22)
#define PAC1934_I2C_ADDR_READ        (0x23)

// DEFINES PAC1934 FULLSCALE RANGE
#define FULLSCALE_RANGE               0.1f

/* Private enumerate/structure ---------------------------------------- */
/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Private variables -------------------------------------------------- */
/* Private function prototypes ---------------------------------------- */
static base_status_t m_pac1934_read_reg(pac1934_t *me, uint8_t reg, uint8_t *p_data, uint32_t len);
static base_status_t m_pac1934_write_reg(pac1934_t *me, uint8_t reg, uint8_t *p_data, uint32_t len);

/* Function definitions ----------------------------------------------- */
base_status_t pac1934_init(pac1934_t *me)
{
  uint8_t tmp;

  if ((me == NULL) || (me->i2c_read == NULL) || (me->i2c_write == NULL))
    return BS_ERROR;

  tmp = NULL;
  CHECK_STATUS(m_pac1934_write_reg(me, PAC1934_REG_REFRESH, &tmp, 1));
  me->delay_ms(100);

  tmp = 0x00;
  CHECK_STATUS(m_pac1934_write_reg(me, PAC1934_REG_PAC_CTRL, &tmp, 1));
  
  tmp = 0xFF;
  CHECK_STATUS(m_pac1934_write_reg(me, PAC1934_REG_NEG_PWR, &tmp, 1));

  tmp = 0x00;
  CHECK_STATUS(m_pac1934_write_reg(me, PAC1934_REG_CHANNEL_DIS, &tmp, 1));

  tmp = 0x00;
  CHECK_STATUS(m_pac1934_write_reg(me, PAC1934_REG_SLOW, &tmp, 1));

  tmp = NULL;
  CHECK_STATUS(m_pac1934_write_reg(me, PAC1934_REG_REFRESH, &tmp, 1));
  me->delay_ms(100);

  return BS_OK;
}

base_status_t pac1934_voltage_measurement(pac1934_t *me, pac1934_data_t *data, uint8_t channel)
{
  uint8_t   register_addr;
  uint8_t   tmp_vbus[2];
  uint16_t  vbus;  

  if ((me == NULL) || (me->i2c_read == NULL) || (me->i2c_write == NULL))
    return BS_ERROR;

  register_addr = channel + 0x06;   // vpower registers addresses begin with 0x07.

  CHECK_STATUS(m_pac1934_read_reg(me, register_addr, &tmp_vbus[0], sizeof(tmp_vbus)));

  vbus   =   tmp_vbus[0];
  vbus   <<= 8;
  vbus   |=  tmp_vbus[1];

  if(vbus >= 0x8000)
  {
    vbus       = ((0xFFFF) - (vbus)) + 1;               //Two's complement 
    data->volt = (double)vbus;                          //Type casting must be done to convert the value into double initially.
    data->volt = (double)((data->volt * 32)/(0xFFFF));  // 0xFFFF is the biggest 28 bit-number to be written.
  }
  else
  { 
    data->volt = (double)vbus;
    data->volt = (double)((data->volt * 32)/(0x7FFF));  // 0x7FFF is the biggest 27 bit-number to be written.
  }

  return BS_OK;
}

base_status_t pac1934_current_measurement(pac1934_t *me, pac1934_data_t *data, uint8_t channel)
{
  uint8_t   register_addr;
  uint8_t   tmp_vsense[2];
  uint16_t  vsense;
  double    d_vsense;
  double    isense;
  double    imax;
  double    rsense;
  double    fullscalecurrent;  

  if ((me == NULL) || (me->i2c_read == NULL) || (me->i2c_write == NULL))
    return BS_ERROR;

  register_addr = channel + 0x0A;   // vpower registers addresses begin with 0x0B.

  CHECK_STATUS(m_pac1934_read_reg(me, register_addr, &tmp_vsense[0], sizeof(tmp_vsense)));

  vsense   =   tmp_vsense[0];
  vsense   <<= 8;
  vsense   |=  tmp_vsense[1];

  if(vsense >= 0x8000)  //0x8000 is the smallest negative number that could be written.
  {
    vsense           = ((0xFFFF) - (vsense)) + 1;                  //Two's complement
    d_vsense         = (double)vsense;
    imax             = (double)(FULLSCALE_RANGE) / (0.004);        // 0.004 :Rsense internal resistor value and 0.1 = 100mV full scale current value.
    rsense           = (FULLSCALE_RANGE) / (imax);                 // I max : maximum current to be measured.
    fullscalecurrent = (FULLSCALE_RANGE) / rsense;
    data->current    = (fullscalecurrent * d_vsense ) / (0xFFFF);
  }
  else
  {
    d_vsense         = (double)vsense;
    imax             = (double)(FULLSCALE_RANGE) / (0.004);
    rsense           = (FULLSCALE_RANGE) / (imax);
    fullscalecurrent = (FULLSCALE_RANGE) / rsense;
    data->current    = (fullscalecurrent * d_vsense ) / (0x7FFF);
  }

  return BS_OK;
}

base_status_t pac1934_power_measurement(pac1934_t *me, pac1934_data_t *data, uint8_t channel)
{
  uint8_t   register_addr;
  uint8_t   tmp_vpower[4];
  uint32_t  vpower;
  double    d_vpower;
  double    isense;
  double    imax;
  double    rsense;
  double    fullscalerangepower; 
  double    proppower;

  if ((me == NULL) || (me->i2c_read == NULL) || (me->i2c_write == NULL))
    return BS_ERROR;

  register_addr = channel + 0x16;   // vpower registers addresses begin with 0x17.

  CHECK_STATUS(m_pac1934_read_reg(me, register_addr, &tmp_vpower[0], sizeof(tmp_vpower)));

  vpower    =   tmp_vpower[0];
  vpower    <<= 8;
  vpower    |=  tmp_vpower[1];
  vpower    <<= 8;
  vpower    |=  tmp_vpower[2];
  vpower    <<= 8;
  vpower    |=  tmp_vpower[3];

  if(vpower >= 0x80000000)
  {
    vpower              = ((0xFFFFFFFF) - (vpower)) + 1;
    d_vpower            = (double)vpower;
    imax                = (double)(FULLSCALE_RANGE) / (0.004);
    rsense              = (FULLSCALE_RANGE) / (imax);
    fullscalerangepower = (double)(((FULLSCALE_RANGE) / (rsense)) * 32);
    proppower           = (d_vpower / (0xFFFFFFF0);
    data->power         = (fullscalerangepower * proppower);
  }
  else
  {
    d_vpower            = (double)vpower;
    imax                = (double)(FULLSCALE_RANGE) / (0.004);
    rsense              = (FULLSCALE_RANGE) / (imax);
    fullscalerangepower = (double)(( (FULLSCALE_RANGE) / (rsense)) * 32);
    proppower           = (d_vpower / 0x7FFFFFF0); 
    data->power         = (fullscalerangepower * proppower);
  }

  return BS_OK;
}

/* Private function definitions ---------------------------------------- */
/**
 * @brief         MIS2DH read register
 *
 * @param[in]     me      Pointer to handle of MIS2DH module.
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
static base_status_t m_pac1934_read_reg(pac1934_t *me, uint8_t reg, uint8_t *p_data, uint32_t len)
{
  CHECK(0 == me->i2c_read(me->device_address, reg, p_data, len), BS_ERROR);

  return BS_OK;
}

/**
 * @brief         MIS2DH read register
 *
 * @param[in]     me      Pointer to handle of MIS2DH module.
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
static base_status_t m_pac1934_write_reg(pac1934_t *me, uint8_t reg, uint8_t *p_data, uint32_t len)
{
  CHECK(0 == me->i2c_write(me->device_address, reg, p_data, len), BS_ERROR);

  return BS_OK;
}

/* End of file -------------------------------------------------------- */