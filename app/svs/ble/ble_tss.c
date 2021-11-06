/**
 * @file       ble_tss.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-11-06
 * @author     Hiep Le
 * @brief      Time synchronize service
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include <assert.h>
#include <string.h>
#include "sys_damos_ram.h"

#include "sysinit/sysinit.h"
#include "syscfg/syscfg.h"
#include "host/ble_hs.h"
#include "host/ble_gap.h"

#include "ble_tss.h"

/* Private defines ---------------------------------------------------- */
static const char *TAG = "BSP_TSS";

/* Private macros ----------------------------------------------------------- */
#define BLE_TSS_LOAD_EPOCH_TIME()   g_epoch_time = ble_tss_epoch_time

/* Private variables -------------------------------------------------- */
int32_t ble_tss_epoch_time = 0;

const uint8_t TSS_CHAR_UUID[][16] =
{
  { BLE_UUID_TSS_EPOCH_TIME_CHARACTERISTIC },
};

/* Private function prototypes ---------------------------------------- */
static int m_ble_tss_access(uint16_t conn_handle, uint16_t attr_handle, 
                            struct ble_gatt_access_ctxt *ctxt, void *arg);

static int m_ble_tss_chr_write(struct os_mbuf *om, uint16_t min_len,
                               uint16_t max_len, void *dst,
                               uint16_t *len);

/* Private enumerate/structure ---------------------------------------- */
static const struct ble_gatt_svc_def ble_tss_defs[] = 
{
  { // Service: Device Setting Service (TSS)
    .type = BLE_GATT_SVC_TYPE_PRIMARY,  
    .uuid = BLE_UUID128_DECLARE(BLE_UUID_TSS_SERVICE),
    .characteristics = (struct ble_gatt_chr_def[]) 
    { 
      {
        .uuid = BLE_UUID128_DECLARE(BLE_UUID_TSS_EPOCH_TIME_CHARACTERISTIC),
        .access_cb = m_ble_tss_access,
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
void ble_tss_init(void)
{
  int rc;

  SYSINIT_ASSERT_ACTIVE(); // Ensure this function only gets called by sysinit

  rc = ble_gatts_count_cfg(ble_tss_defs);
  SYSINIT_PANIC_ASSERT(rc == 0);

  rc = ble_gatts_add_svcs(ble_tss_defs);
  SYSINIT_PANIC_ASSERT(rc == 0);
}

/* Private function definitions---------------------------------------- */
static int m_ble_tss_access(uint16_t conn_handle, uint16_t attr_handle,
                            struct ble_gatt_access_ctxt *ctxt, void *arg)
{
  int rc = 0;

  if (memcmp(BLE_UUID128(ctxt->chr->uuid)->value, TSS_CHAR_UUID, 16) == 0)
  {
    if (ctxt->op == BLE_GATT_ACCESS_OP_WRITE_CHR)
    {
      rc = m_ble_tss_chr_write(ctxt->om, 0, 4, &ble_tss_epoch_time, NULL);
      
      BLE_TSS_LOAD_EPOCH_TIME();

      ESP_LOGE(TAG, "Epoch Time: %li", (long int) ble_tss_epoch_time);
    }
  }

  return rc;
}

/**
 * Writes the received value from a characteristic write to
 * the given destination.
 */
static int m_ble_tss_chr_write(struct os_mbuf *om, uint16_t min_len,
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
