/**
 * This file is part of Espruino, a JavaScript interpreter for Microcontrollers
 *
 * Copyright (C) 2013 Gordon Williams <gw@pur3.co.uk>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * ----------------------------------------------------------------------------
 * Utilities for converting Nordic datastructures to Espruino and vice versa
 * ----------------------------------------------------------------------------
 */
#include <stdio.h>

#include "bt.h"
#include "esp_bt_main.h"
#include "esp_gatt_common_api.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"

#include "bluetooth.h"
#include "jsutils.h"

#include "BLE/esp32_gap_func.h"
#include "BLE/esp32_gatts_func.h"

#define UNUSED(x) (void)(x)
 
volatile BLEStatus bleStatus;
uint16_t bleAdvertisingInterval;           /**< The advertising interval (in units of 0.625 ms). */
volatile uint16_t                         m_conn_handle;    /**< Handle of the current connection. */

/** Initialise the BLE stack */
void jsble_init(){
	esp_err_t ret;
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    ret = esp_bt_controller_init(&bt_cfg);
    if(ret) {jsWarn("initialize controller failed:%x\n",ret); return;}

	ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);
	if(ret) {jsWarn("enable controller failed:%x\n",ret); return;}
	
	ret = esp_bt_controller_mem_release(ESP_BT_MODE_BTDM);
	if(ret) {jsWarn("mem release failed:%x\n",ret); return;}
	
	ret = esp_bluedroid_init();
	if (ret) {jsWarn("init bluetooth failed:%x\n",ret);return;}
    
	ret = esp_bluedroid_enable();
    if (ret) {jsWarn("enable bluetooth failed:%x\n",ret);return;}
	
	ret = esp_ble_gap_register_callback(gap_event_handler);
    if (ret){jsWarn("gap register error:%x\n", ret);return;}

	ret = esp_ble_gatts_register_callback(gatts_event_handler);
	if(ret){jsWarn("gatts register error:%x\n", ret);return;}
	
	ret = esp_ble_gatt_set_local_mtu(500);
	if(ret){jsWarn("set local MTU failed:%x\n",ret);return;}
}
/** Completely deinitialise the BLE stack */
void jsble_kill(){
	jsWarn("kill not implemented yet\n");
}

void jsble_restart_softdevice(){
	jsWarn("restart softdevice not implemented yet\n");
}

void jsble_advertising_start(){
//jsWarn("advertising start\n");
	esp_err_t status;
	if (bleStatus & BLE_IS_ADVERTISING) return;
	status = bluetooth_gap_startAdvertizing(true);
	if(status) jsWarn("advertizing start problem:0X%x\n",status);
}
void jsble_advertising_stop(){
	esp_err_t status;
	status = bluetooth_gap_startAdvertizing(false);
	if(status) jsWarn("error in stop advertising:0X%x\n",status);
}
/** Is BLE connected to any device at all? */
bool jsble_has_connection(){
	jsWarn("has connected not implemented yet\n");
	return false;
}

/** Is BLE connected to a central device at all? */
bool jsble_has_central_connection(){
	jsWarn("has central connection not implemented yet\n");
	return false;
}
/** Is BLE connected to a server device at all (eg, the simple, 'slave' mode)? */
bool jsble_has_simple_connection(){
	jsWarn("has simple connection not implemented yet\n");
	return false;
}

/// Checks for error and reports an exception if there was one. Return true on error
bool jsble_check_error(uint32_t err_code){
	jsWarn("check error not implemented yet:%x\n",err_code);
	UNUSED(err_code);
	return false;
}
/// Scanning for advertisign packets
uint32_t jsble_set_scanning(bool enabled){
	bluetooth_gap_setScan(enabled);
	return 0;
}

/// returning RSSI values for current connection
uint32_t jsble_set_rssi_scan(bool enabled){
	jsWarn("set rssi scan not implemeted yet\n");
	UNUSED(enabled);
	return 0;
}

/** Actually set the services defined in the 'data' object. Note: we can
 * only do this *once* - so to change it we must reset the softdevice and
 * then call this again */
void jsble_set_services(JsVar *data){
	gatts_set_services(data);
}

/// Disconnect from the given connection
uint32_t jsble_disconnect(uint16_t conn_handle){
	jsWarn("disconnect not implemented yet\n");
	UNUSED(conn_handle);
	return 0;
}

/// For BLE HID, send an input report to the receiver. Must be <= HID_KEYS_MAX_LEN
void jsble_send_hid_input_report(uint8_t *data, int length){
	jsWarn("send hid input report not implemented yet\n");
	UNUSED(data);
	UNUSED(length);
}
