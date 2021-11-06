/**
 * @file       ble_bas.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-10-20
 * @author     Hiep Le
 * @brief      BLE Battery service
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
#include "ble_bas.h"

/* Private defines ---------------------------------------------------- */
/* Private variables -------------------------------------------------- */
static uint8_t m_ble_bas_battery_level;
static uint16_t m_ble_bas_battery_handle;

/* Private function prototypes ---------------------------------------- */
static int m_ble_bas_access(uint16_t conn_handle, uint16_t attr_handle, 
                          struct ble_gatt_access_ctxt *ctxt, void *arg);

/* Private enumerate/structure ---------------------------------------- */
static const struct ble_gatt_svc_def ble_bas_defs[] =
{
  {
    // Battery Service
    .type = BLE_GATT_SVC_TYPE_PRIMARY,
    .uuid = BLE_UUID16_DECLARE(BLE_BAS_UUID16),
    .characteristics = (struct ble_gatt_chr_def[])
    {
      {
        // Battery level characteristic
        .uuid = BLE_UUID16_DECLARE(BLE_BAS_CHR_UUID16_BATTERY_LEVEL),
        .access_cb = m_ble_bas_access,
        .val_handle = &m_ble_bas_battery_handle,
        .flags = BLE_GATT_CHR_F_READ | BLE_GATT_CHR_F_NOTIFY,
      },

      {
        0, // No more characteristics in this service.
      }
    },
  },

  {
    0, // No more services.
  },
};

/* Private macros ----------------------------------------------------- */
/* Public variables --------------------------------------------------- */
/* Function definitions ----------------------------------------------- */
void ble_bas_init(void)
{
  int rc;

  // Ensure this function only gets called by sysinit.
  SYSINIT_ASSERT_ACTIVE();

  rc = ble_gatts_count_cfg(ble_bas_defs);
  SYSINIT_PANIC_ASSERT(rc == 0);

  rc = ble_gatts_add_svcs(ble_bas_defs);
  SYSINIT_PANIC_ASSERT(rc == 0);
}

void ble_bas_battery_level_set(uint8_t level)
{
  if (level > 100)
    level = 100;
  
  if (m_ble_bas_battery_level != level)
  {
    m_ble_bas_battery_level = level;
    ble_gatts_chr_updated(m_ble_bas_battery_handle);
  }
}

/* Private function definitions---------------------------------------- */
static int m_ble_bas_access(uint16_t conn_handle, uint16_t attr_handle,
                          struct ble_gatt_access_ctxt *ctxt, void *arg)
{
  uint16_t uuid16 = ble_uuid_u16(ctxt->chr->uuid);
  int rc;

  switch (uuid16)
  {
    case BLE_BAS_CHR_UUID16_BATTERY_LEVEL:
      assert(ctxt->op == BLE_GATT_ACCESS_OP_READ_CHR);
      rc = os_mbuf_append(ctxt->om, &m_ble_bas_battery_level, sizeof(m_ble_bas_battery_level));
      return rc == 0 ? 0 : BLE_ATT_ERR_INSUFFICIENT_RES;

    default:
      assert(0);
      return BLE_ATT_ERR_UNLIKELY;
  }
}

/* End of file -------------------------------------------------------- */
