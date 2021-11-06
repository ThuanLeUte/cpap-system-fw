/**
 * @file       ble.c
 * @copyright  Copyright (C) 2020 Hydratech. All rights reserved.
 * @license    This project is released under the Hydratech License.
 * @version    1.0.0
 * @date       2021-10-24
 * @author     Hiep Le
 * @brief      BLE service
 * @note       None
 * @example    None
 */

/* Includes ----------------------------------------------------------- */
#include "esp_log.h"

#include "esp_nimble_hci.h"
#include "nimble/nimble_port.h"
#include "nimble/nimble_port_freertos.h"
#include "host/ble_hs.h"
#include "services/gap/ble_svc_gap.h"
#include "services/gatt/ble_svc_gatt.h"
#include "ble.h"
#include "ble_dss.h"
#include "ble_uds.h"
#include "ble_bas.h"
#include "ble_tss.h"

/* Private variables -------------------------------------------------- */
static const char *tag = "BLE CPAP";
static uint16_t conn_handle;
static const char *device_name = "BLE_CPAP_1.0";
static uint8_t ble_addr_type;

/* Private function prototypes ---------------------------------------- */
static void ble_advertise(void);
static int ble_gap_event(struct ble_gap_event *event, void *arg);
static void ble_on_sync(void);
static void ble_on_reset(int reason);

/* Function definitions ----------------------------------------------- */
void print_addr(const void *addr)
{
  const uint8_t *u8p;

  u8p = addr;
  MODLOG_DFLT(INFO, "%02x:%02x:%02x:%02x:%02x:%02x", u8p[5], u8p[4], u8p[3], u8p[2], u8p[1], u8p[0]);
}

void ble_host_task(void *param)
{
  ESP_LOGI(tag, "BLE Host Task Started");
  
  nimble_port_run();  // This function will return only when nimble_port_stop() is executed

  nimble_port_freertos_deinit();
}

void ble_init(void)
{
  int rc;

  esp_err_t ret = nvs_flash_init(); // Initialize NVS — it is used to store PHY calibration data
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }
  ESP_ERROR_CHECK(ret);

  ESP_ERROR_CHECK(esp_nimble_hci_and_controller_init());

  nimble_port_init(); // Initialize the NimBLE host configuration

  ble_hs_cfg.sync_cb = ble_on_sync;
  ble_hs_cfg.reset_cb = ble_on_reset;

  ble_bas_init();
  ble_dss_init();
  ble_uds_init();
  ble_tss_init();

  ble_svc_gap_init();
  ble_svc_gatt_init();

  rc = ble_svc_gap_device_name_set(device_name);
  assert(rc == 0);

  nimble_port_freertos_init(ble_host_task);
}

/* Private function definitions ---------------------------------------- */
// Enables advertising with parameters:
// o General discoverable mode
// o Undirected connectable mode
static void ble_advertise(void)
{
  struct ble_gap_adv_params adv_params;
  struct ble_hs_adv_fields fields;
  int rc;

  // Set the advertisement data included in our advertisements:
  // o Flags (indicates advertisement type and other general info)
  // o Advertising tx power
  // o Device name
  memset(&fields, 0, sizeof(fields));

  // Advertise two flags:
  // o Discoverability in forthcoming advertisement (general)
  // o BLE-only (BR/EDR unsupported)
  fields.flags = BLE_HS_ADV_F_DISC_GEN | BLE_HS_ADV_F_BREDR_UNSUP;
  
  // Indicate that the TX power level field should be included; have the
  // stack fill this value automatically.  This is done by assigning the
  // special value BLE_HS_ADV_TX_PWR_LVL_AUTO.
  fields.tx_pwr_lvl_is_present = 1;
  fields.tx_pwr_lvl = BLE_HS_ADV_TX_PWR_LVL_AUTO;

  fields.name = (uint8_t *)device_name;
  fields.name_len = strlen(device_name);
  fields.name_is_complete = 1;

  rc = ble_gap_adv_set_fields(&fields);
  if (rc != 0)
  {
    MODLOG_DFLT(ERROR, "error setting advertisement data; rc=%d\n", rc);
    return;
  }

  // Begin advertising
  memset(&adv_params, 0, sizeof(adv_params));
  adv_params.conn_mode = BLE_GAP_CONN_MODE_UND;
  adv_params.disc_mode = BLE_GAP_DISC_MODE_GEN;
  rc = ble_gap_adv_start(ble_addr_type, NULL, BLE_HS_FOREVER,
                         &adv_params, ble_gap_event, NULL);
  if (rc != 0)
  {
    MODLOG_DFLT(ERROR, "error enabling advertisement; rc=%d\n", rc);
    return;
  }
}

static int ble_gap_event(struct ble_gap_event *event, void *arg)
{
  switch (event->type)
  {
  case BLE_GAP_EVENT_CONNECT:
    // A new connection was established or a connection attempt failed
    MODLOG_DFLT(INFO, "connection %s; status=%d\n",
                event->connect.status == 0 ? "established" : "failed",
                event->connect.status);

    if (event->connect.status != 0)
    {
      ble_advertise(); // Connection failed; resume advertising
    }
    conn_handle = event->connect.conn_handle;
    break;

  case BLE_GAP_EVENT_DISCONNECT:
    MODLOG_DFLT(INFO, "disconnect; reason=%d\n", event->disconnect.reason);

    ble_advertise(); // Connection terminated; resume advertising
    break;

  case BLE_GAP_EVENT_ADV_COMPLETE:
    MODLOG_DFLT(INFO, "adv complete\n");
    ble_advertise();
    break;

  case BLE_GAP_EVENT_MTU:
    MODLOG_DFLT(INFO, "mtu update event; conn_handle=%d mtu=%d\n",
                event->mtu.conn_handle,
                event->mtu.value);
    break;
  }

  return 0;
}

static void ble_on_sync(void)
{
  int rc;

  rc = ble_hs_id_infer_auto(0, &ble_addr_type);
  assert(rc == 0);

  uint8_t addr_val[6] = {0};
  rc = ble_hs_id_copy_addr(ble_addr_type, addr_val, NULL);

  MODLOG_DFLT(INFO, "Device Address: ");
  print_addr(addr_val);
  MODLOG_DFLT(INFO, "\n");

  ble_advertise();
}

static void ble_on_reset(int reason)
{
  MODLOG_DFLT(ERROR, "Resetting state; reason=%d\n", reason);
}

/* End of file -------------------------------------------------------- */
