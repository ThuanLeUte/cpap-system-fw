/**
 * @file       ble_dss.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-10-20
 * @author     Hiep Le
 * @brief      Device setting service
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include <assert.h>
#include <string.h>

#include "sysinit/sysinit.h"
#include "syscfg/syscfg.h"
#include "host/ble_hs.h"
#include "host/ble_gap.h"

#include "ble_dss.h"

/* Private defines ---------------------------------------------------- */
/* Private variables -------------------------------------------------- */
const uint8_t DSS_CHAR_UUID[][16] =
{
  { BLE_UUID_DSS_PRESSURE_CHARACTERISTIC      },
  { BLE_UUID_DSS_RAMP_TIME_CHARACTERISTIC     },
  { BLE_UUID_DSS_ALARM_HOUR_CHARACTERISTIC    },
  { BLE_UUID_DSS_ALARM_MINUTE_CHARACTERISTIC  }
};

/* Private function prototypes ---------------------------------------- */
static int m_ble_dss_access(uint16_t conn_handle, uint16_t attr_handle, 
                            struct ble_gatt_access_ctxt *ctxt, void *arg);

static int m_ble_dss_chr_write(struct os_mbuf *om, uint16_t min_len,
                               uint16_t max_len, void *dst,
                               uint16_t *len);

/* Private enumerate/structure ---------------------------------------- */
ble_dss_data_t ble_dss_data = { 0 };

static const struct ble_gatt_svc_def ble_dss_defs[] = 
{
  { // Service: Device Setting Service (DSS)
    .type = BLE_GATT_SVC_TYPE_PRIMARY,  
    .uuid = BLE_UUID128_DECLARE(BLE_UUID_DSS_SERVICE),
    .characteristics = (struct ble_gatt_chr_def[]) 
    { 
      {
        .uuid = BLE_UUID128_DECLARE(BLE_UUID_DSS_PRESSURE_CHARACTERISTIC),
        .access_cb = m_ble_dss_access,
        .flags = BLE_GATT_CHR_F_WRITE,
      }, 
      {
        .uuid = BLE_UUID128_DECLARE(BLE_UUID_DSS_RAMP_TIME_CHARACTERISTIC),
        .access_cb = m_ble_dss_access,
        .flags = BLE_GATT_CHR_F_WRITE,
      }, 
      {
        .uuid = BLE_UUID128_DECLARE(BLE_UUID_DSS_ALARM_HOUR_CHARACTERISTIC),
        .access_cb = m_ble_dss_access,
        .flags = BLE_GATT_CHR_F_WRITE,
      }, 
      {
        .uuid = BLE_UUID128_DECLARE(BLE_UUID_DSS_ALARM_MINUTE_CHARACTERISTIC),
        .access_cb = m_ble_dss_access,
        .flags = BLE_GATT_CHR_F_WRITE,
      }, 
      {
        0, // No more characteristics in this service
      }
    }
  },
  {
      0, // No more services
  }
};

/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Function definitions ----------------------------------------------- */
void ble_dss_init(void)
{
  int rc;

  SYSINIT_ASSERT_ACTIVE(); // Ensure this function only gets called by sysinit

  rc = ble_gatts_count_cfg(ble_dss_defs);
  SYSINIT_PANIC_ASSERT(rc == 0);

  rc = ble_gatts_add_svcs(ble_dss_defs);
  SYSINIT_PANIC_ASSERT(rc == 0);
}

/* Private function definitions---------------------------------------- */
static int m_ble_dss_access(uint16_t conn_handle, uint16_t attr_handle,
                            struct ble_gatt_access_ctxt *ctxt, void *arg)
{
  int rc = 0;

  if (memcmp(BLE_UUID128(ctxt->chr->uuid)->value, DSS_CHAR_UUID[DSS_PRESSURE_CHARACTERISTIC], 16) == 0)
  {
    if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR)
    {
      rc = m_ble_dss_chr_write(ctxt->om, 0,
                               sizeof(ble_dss_data.pressure),
                               &ble_dss_data.pressure,
                               NULL);
      ESP_LOGE("TAG", "Data: %d", ble_dss_data.pressure);
    }
  }
  else if (memcmp(BLE_UUID128(ctxt->chr->uuid)->value , DSS_CHAR_UUID[DSS_RAMP_TIME_CHARACTERISTIC], 16) == 0)
  {
    if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR)
    {
      rc = m_ble_dss_chr_write(ctxt->om, 0,
                               sizeof(ble_dss_data.ramp_time),
                               &ble_dss_data.ramp_time,
                               NULL);
      ESP_LOGE("TAG", "Data 0: %d", ble_dss_data.ramp_time);
    }
  }
  else if (memcmp(BLE_UUID128(ctxt->chr->uuid)->value, DSS_CHAR_UUID[DSS_ALARM_HOUR_CHARACTERISTIC], 16) == 0)
  {
    if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR)
    {
      rc = m_ble_dss_chr_write(ctxt->om, 0,
                               sizeof(ble_dss_data.alarm_hour),
                               &ble_dss_data.alarm_hour,
                               NULL);
      ESP_LOGE("TAG", "Data 1: %d", ble_dss_data.alarm_hour);
    }
  }
  else if (memcmp(BLE_UUID128(ctxt->chr->uuid)->value, DSS_CHAR_UUID[DSS_ALARM_MINUTE_CHARACTERISTIC], 16) == 0)
  {
    if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR)
    {
      rc = m_ble_dss_chr_write(ctxt->om, 0,
                               sizeof(ble_dss_data.alarm_minute),
                               &ble_dss_data.alarm_minute,
                               NULL);
      ESP_LOGE("TAG", "Data 2: %d", ble_dss_data.alarm_minute);
    }
  }

  return rc;
}

/**
 * Writes the received value from a characteristic write to
 * the given destination.
 */
static int m_ble_dss_chr_write(struct os_mbuf *om, uint16_t min_len,
                               uint16_t max_len, void *dst,
                               uint16_t *len)
{
  uint16_t om_len;
  int rc;

  om_len = OS_MBUF_PKTLEN(om);
  if (om_len < min_len || om_len > max_len)
  {
    return BLE_ATT_ERR_INVALID_ATTR_VALUE_LEN;
  }

  rc = ble_hs_mbuf_to_flat(om, dst, max_len, len);
  if (rc != 0)
  {
    return BLE_ATT_ERR_UNLIKELY;
  }

  return 0;
}

/* End of file -------------------------------------------------------- */
