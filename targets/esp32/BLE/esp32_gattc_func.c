/*
 * This file is part of Espruino, a JavaScript interpreter for Microcontrollers
 *
 * Copyright (C) 2017 Gordon Williams <gw@pur3.co.uk>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * ----------------------------------------------------------------------------
 * ESP32 specific GATT client functions
 * ----------------------------------------------------------------------------
 */

#include <stdio.h>

#include "BLE/esp32_gattc_func.h"
#include "BLE/esp32_bluetooth_utils.h"

#include "bluetooth.h"
#include "bluetooth_utils.h"

#include "jsutils.h"
#include "jsparse.h"
#include "jsinteractive.h"

void gattc_event_handler(esp_gattc_cb_event_t event, esp_gatt_if_t gatts_if, esp_ble_gattc_cb_param_t *param) {
	jsWarnGattcEvent(event,gatts_if);
	JsVar *args[1];
	switch (event) {
      case ESP_GATTC_REG_EVT: break;
      case ESP_GATTC_UNREG_EVT: break;
      case ESP_GATTC_OPEN_EVT: break;
      case ESP_GATTC_READ_CHAR_EVT: break;
      case ESP_GATTC_WRITE_CHAR_EVT: break;
      case ESP_GATTC_CLOSE_EVT: break;
      case ESP_GATTC_SEARCH_CMPL_EVT: break;
      case ESP_GATTC_SEARCH_RES_EVT: break;
      case ESP_GATTC_READ_DESCR_EVT: break;
      case ESP_GATTC_WRITE_DESCR_EVT: break;
      case ESP_GATTC_NOTIFY_EVT: break;
      case ESP_GATTC_PREP_WRITE_EVT: break;
      case ESP_GATTC_EXEC_EVT: break;
      case ESP_GATTC_ACL_EVT: break;
      case ESP_GATTC_CANCEL_OPEN_EVT: break;
      case ESP_GATTC_SRVC_CHG_EVT: break;
      case ESP_GATTC_ENC_CMPL_CB_EVT: break;
      case ESP_GATTC_CFG_MTU_EVT: break;
      case ESP_GATTC_ADV_DATA_EVT: break;
      case ESP_GATTC_MULT_ADV_ENB_EVT: break;
      case ESP_GATTC_MULT_ADV_UPD_EVT: break;
      case ESP_GATTC_MULT_ADV_DATA_EVT: break;
      case ESP_GATTC_MULT_ADV_DIS_EVT: break;
      case ESP_GATTC_CONGEST_EVT: break;
      case ESP_GATTC_BTH_SCAN_ENB_EVT: break;
      case ESP_GATTC_BTH_SCAN_CFG_EVT: break;
      case ESP_GATTC_BTH_SCAN_RD_EVT: break;
      case ESP_GATTC_BTH_SCAN_THR_EVT: break;
      case ESP_GATTC_BTH_SCAN_PARAM_EVT: break;
      case ESP_GATTC_BTH_SCAN_DIS_EVT: break;
      case ESP_GATTC_SCAN_FLT_CFG_EVT: break;
      case ESP_GATTC_SCAN_FLT_PARAM_EVT: break;
      case ESP_GATTC_SCAN_FLT_STATUS_EVT: break;
      case ESP_GATTC_ADV_VSC_EVT: break;
      case ESP_GATTC_REG_FOR_NOTIFY_EVT: break;
      case ESP_GATTC_UNREG_FOR_NOTIFY_EVT: break;
      case ESP_GATTC_CONNECT_EVT: break;
      case ESP_GATTC_DISCONNECT_EVT: break;
	  default: break;
	}
}