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
 * ESP32 specific GAP functions
 * ----------------------------------------------------------------------------
 */

#include <stdio.h>

#include "BLE/esp32_gap_func.h"
#include "BLE/esp32_gatts_func.h"
#include "BLE/esp32_bluetooth_utils.h"

#include "jsutils.h"
#include "jsparse.h"
#include "jsinteractive.h"
#include "bluetooth_utils.h"

#define adv_config_flag      (1 << 0)
#define scan_rsp_config_flag (1 << 1)
#define BT_BD_ADDR_HEX(addr)   addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]
#define GAP_SCAN_FUNC "gap_scan_func"

static uint8_t adv_config_done = 0;

static esp_ble_adv_params_t adv_params = {
    .adv_int_min        = 0x20,
    .adv_int_max        = 0x40,
    .adv_type           = ADV_TYPE_IND,
    .own_addr_type      = BLE_ADDR_TYPE_PUBLIC,
    //.peer_addr            =
    //.peer_addr_type       =
    .channel_map        = ADV_CHNL_ALL,
    .adv_filter_policy = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
};

static esp_ble_scan_params_t ble_scan_params = 	{	
	.scan_type              = BLE_SCAN_TYPE_ACTIVE,
	.own_addr_type          = BLE_ADDR_TYPE_PUBLIC,
	.scan_filter_policy     = BLE_SCAN_FILTER_ALLOW_ALL,
	.scan_interval          = 0x50,
	.scan_window            = 0x30		
};

static esp_ble_adv_data_t adv_data = {
    .set_scan_rsp = false,
    .include_name = true,
    .include_txpower = true,
    .min_interval = 0x20,
    .max_interval = 0x40,
    .appearance = 0x00,
    .manufacturer_len = 0, //TEST_MANUFACTURER_DATA_LEN,
    .p_manufacturer_data =  NULL, //&test_manufacturer[0],
    .service_data_len = 0,
    .p_service_data = NULL,
    .service_uuid_len = 0,  //needs to be set before used
    .p_service_uuid = &adv_service_uuid128,
    .flag = (ESP_BLE_ADV_FLAG_GEN_DISC | ESP_BLE_ADV_FLAG_BREDR_NOT_SPT),
};

static void execScanFunc(esp_ble_gap_cb_param_t *p){
	JsVar *evt = jsvNewObject();
	jsvObjectSetChildAndUnLock(evt, "id", bda2JsVarString(p->scan_rst.bda));
	jsvObjectSetChildAndUnLock(evt, "rssi",jsvNewFromInteger(p->scan_rst.rssi));
    JsVar *data = jsvNewStringOfLength(p->scan_rst.adv_data_len, (char*)p->scan_rst.ble_adv);
	if(data){
		JsVar *ab = jsvNewArrayBufferFromString(data,p->scan_rst.adv_data_len);
		jsvUnLock(data);
		jsvObjectSetChildAndUnLock(evt,"data",ab);
	}
    jsiQueueObjectCallbacks(execInfo.root, BLE_SCAN_EVENT, &evt,1);
	jsvUnLock(evt);
	jshHadEvent();
}

void gap_event_scan_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param){
    uint8_t *adv_name = NULL;
    uint8_t adv_name_len = 0;
	esp_ble_gap_cb_param_t *p = (esp_ble_gap_cb_param_t *)param;
	switch(event){
		case ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT:		{
		}
		break;
		case ESP_GAP_BLE_SCAN_START_COMPLETE_EVT:{
			if (param->scan_start_cmpl.status != ESP_BT_STATUS_SUCCESS)	{jsWarn("Scan start failed:d\n",param->scan_start_cmpl.status);}
		}
		break;		
		case ESP_GAP_BLE_SCAN_RESULT_EVT:{
			execScanFunc(param);
		}
		break;
		case ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT:{
			if (param->scan_stop_cmpl.status != ESP_BT_STATUS_SUCCESS){jsWarn("Scan stop failed");}
			else {jsWarn("Stop scan successfully");}
		}
		break;		
		default:
        break;
	}
}

void gap_event_handler(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param){
//	jsWarnGapEvent(event);
    switch (event) {
    case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:{
        adv_config_done &= (~adv_config_flag);
        if (adv_config_done == 0){
            esp_ble_gap_start_advertising(&adv_params);
        }
	}
    break;
    case ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT:{
        adv_config_done &= (~scan_rsp_config_flag);
        if (adv_config_done == 0){
            esp_ble_gap_start_advertising(&adv_params);
        }
	}
    break;

    case ESP_GAP_BLE_ADV_START_COMPLETE_EVT:{
        if (param->adv_start_cmpl.status != ESP_BT_STATUS_SUCCESS) {
            jsWarn("Advertising start failed\n");
        }
	}
    break;
    case ESP_GAP_BLE_ADV_STOP_COMPLETE_EVT:{
        if (param->adv_stop_cmpl.status != ESP_BT_STATUS_SUCCESS) {
            jsWarn("Advertising stop failed\n");
        }
        else {
            jsWarn("Stop adv successfully\n");
        }
	}
    break;
    case ESP_GAP_BLE_UPDATE_CONN_PARAMS_EVT:{
         jsWarn("update connetion params status = %d, min_int = %d, max_int = %d,conn_int = %d,latency = %d, timeout = %d",
                  param->update_conn_params.status,
                  param->update_conn_params.min_int,
                  param->update_conn_params.max_int,
                  param->update_conn_params.conn_int,
                  param->update_conn_params.latency,
                  param->update_conn_params.timeout);
	}
    break;
    default:
		gap_event_scan_handler(event,param);
    break;
    }
}

void bluetooth_gap_setScan(bool enable){
	esp_err_t status;
	status = esp_ble_gap_set_scan_params(&ble_scan_params);
	if (status){ jsWarn("gap set scan error code = %x", status);return;}
	if(enable == true){
	  status = esp_ble_gap_start_scanning(30); 
	  if (status != ESP_OK) jsWarn("esp_ble_gap_start_scanning: rc=%d", status);
	}
	else{
	  status = esp_ble_gap_stop_scanning();
	}
}

esp_err_t bluetooth_gap_startAdvertizing(bool enable){
	if(enable){
		return esp_ble_gap_start_advertising(&adv_params);
	}
	else{
		return esp_ble_gap_stop_advertising();
	}
}

esp_err_t bluetooth_gap_setAdvertizing(){
  adv_data.service_uuid_len = ble_service_cnt * 16;
  esp_err_t ret = esp_ble_gap_config_adv_data(&adv_data);
  if (ret){
    jsWarn("config adv data failed, error code = %x", ret);
  }
  return ret;  
}

esp_err_t bluetooth_setDeviceName(uint8_t *deviceName){
  return esp_ble_gap_set_device_name(deviceName);	
}

