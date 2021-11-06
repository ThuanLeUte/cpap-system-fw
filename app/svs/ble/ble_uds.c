/**
 * @file       ble_uds.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-10-20
 * @author     Hiep Le
 * @brief      User data service
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

#include "ble_uds.h"

/* Private defines ---------------------------------------------------- */
/* Private variables -------------------------------------------------- */
const uint8_t UDS_CHAR_UUID[][16] =
{
  { BLE_UUID_UDS_OPERATION_HOUR_CHARACTERISTIC      },
  { BLE_UUID_UDS_OPERATION_MINUTE_CHARACTERISTIC    },
  { BLE_UUID_UDS_SLEEP_POSITION_CHARACTERISTIC      }
};
/* Private function prototypes ---------------------------------------- */
static int m_ble_uds_access(uint16_t conn_handle, uint16_t attr_handle, 
                            struct ble_gatt_access_ctxt *ctxt, void *arg);

/* Private enumerate/structure ---------------------------------------- */
ble_uds_data_t ble_uds_data = {
  .operation_hour   = 100,
  .operation_minute = 20,
  .sleep_position   = 10
};

static const struct ble_gatt_svc_def ble_uds_defs[] = 
{
  { // Service: User data Service (UDS)
    .type = BLE_GATT_SVC_TYPE_PRIMARY,  
    .uuid = BLE_UUID128_DECLARE(BLE_UUID_UDS_SERVICE),
    .characteristics = (struct ble_gatt_chr_def[]) 
    { 
      {
        .uuid = BLE_UUID128_DECLARE(BLE_UUID_UDS_OPERATION_HOUR_CHARACTERISTIC),
        .access_cb = m_ble_uds_access,
        .flags = BLE_GATT_CHR_F_READ,
      }, 
      {
        .uuid = BLE_UUID128_DECLARE(BLE_UUID_UDS_OPERATION_MINUTE_CHARACTERISTIC),
        .access_cb = m_ble_uds_access,
        .flags = BLE_GATT_CHR_F_READ,
      }, 
      {
        .uuid = BLE_UUID128_DECLARE(BLE_UUID_UDS_SLEEP_POSITION_CHARACTERISTIC),
        .access_cb = m_ble_uds_access,
        .flags = BLE_GATT_CHR_F_READ,
      }, 
      {
        0, // No more characteristics in this service
      }, 
    }
  },
  {
      0, // No more services
  },
};

/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Function definitions ----------------------------------------------- */
void ble_uds_init(void)
{
  int rc;

  SYSINIT_ASSERT_ACTIVE(); // Ensure this function only gets called by sysinit

  rc = ble_gatts_count_cfg(ble_uds_defs);
  SYSINIT_PANIC_ASSERT(rc == 0);

  rc = ble_gatts_add_svcs(ble_uds_defs);
  SYSINIT_PANIC_ASSERT(rc == 0);
}

/* Private function definitions---------------------------------------- */
static int m_ble_uds_access(uint16_t conn_handle, uint16_t attr_handle,
                            struct ble_gatt_access_ctxt *ctxt, void *arg)
{
  int rc;

  if (memcmp(BLE_UUID128(ctxt->chr->uuid)->value, UDS_CHAR_UUID[UDS_OPERATION_HOUR_CHARACTERISTIC], 16) == 0)
  {
    assert(ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR);
    rc = os_mbuf_append(ctxt->om, &ble_uds_data.operation_hour, sizeof(ble_uds_data.operation_hour));
    ESP_LOGE("TAG", "Data 0: %d", ble_uds_data.operation_hour);

    return rc == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
  }
  else if (memcmp(BLE_UUID128(ctxt->chr->uuid)->value, UDS_CHAR_UUID[UDS_OPERATION_MINUTE_CHARACTERISTIC], 16) == 0)
  {
    assert(ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR);
    rc = os_mbuf_append(ctxt->om, &ble_uds_data.operation_minute, sizeof(ble_uds_data.operation_minute));
    ESP_LOGE("TAG", "Data 1: %d", ble_uds_data.operation_minute);

    return rc == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
  }
  else if (memcmp(BLE_UUID128(ctxt->chr->uuid)->value, UDS_CHAR_UUID[UDS_SLEEP_POSITION_CHARACTERISTIC], 16) == 0)
  {
    assert(ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR);
    rc = os_mbuf_append(ctxt->om, &ble_uds_data.sleep_position, sizeof(ble_uds_data.sleep_position));
    ESP_LOGE("TAG", "Data 2: %d", ble_uds_data.sleep_position);

    return rc == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;
  }

  return 0;
}

/* End of file -------------------------------------------------------- */
