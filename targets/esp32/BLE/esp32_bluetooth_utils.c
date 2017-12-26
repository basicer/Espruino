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
 * ESP32 specific Bluetooth utils
 * ----------------------------------------------------------------------------
 */

#include "BLE/esp32_bluetooth_utils.h"

int bleEventDebug = 0;

typedef enum{
	ESP_BLE_DEBUG_GAP = 1,
	ESP_BLE_DEBUG_GATTS = 2,
	ESP_BLE_DEBUG_GATTC = 4
} esp_ble_debug_t;
 
JsVar *bda2JsVarString(esp_bd_addr_t bda){
	JsVar *s = jsvVarPrintf("%02x:%02x:%02x:%02x:%02x:%02x",bda[0],bda[1],bda[2],bda[3],bda[4],bda[5]);
	return s;
}

void ESP32_setBLE_Debug(int level){
	bleEventDebug = level;
}
static char *gattsEvent2String(esp_gatts_cb_event_t event){
	switch(event){
		case 0: return "REG";
		case 1: return "READ";
		case 2: return "WRITE";
		case 3: return "EXEC_WRITE";
		case 4: return "MTU";
		case 5: return "CONF";
		case 6: return "UNREG";
		case 7: return "CREATE";
		case 8: return "ADD_INCL_SRVC";
		case 9: return "ADD_CHAR";
		case 10: return "ADD_CHAR_DESCR";
		case 11: return "DELETE";
		case 12: return "START";
		case 13: return "STOP";
		case 14: return "CONNECT";
		case 15: return "DISCONNECT";
		case 16: return "OPEN";
		case 17: return "CANCEL_OPEN";
		case 18: return "CLOSE";
		case 19: return "LISTEN";
		case 20: return "CONGEST";
		case 21: return "RESPONSE";
		case 22: return "CREAT_ATTR_TAB";
		case 23: return "CREAT_ATTR_TAB";
	}
	return "unknown GattsEvent";
}
static char *gattcEvent2String(esp_gattc_cb_event_t event){
	switch(event){
		case 0: return"REG";
		case 1: return"UNREG";
		case 2: return"OPEN";
		case 3: return"READ_CHAR";
		case 4: return"WRITE_CHAR";
		case 5: return"CLOSE";
		case 6: return"SEARCH_CMPL";
		case 7: return"SEARCH_RES";
		case 8: return"READ_DESCR";
		case 9: return"WRITE_DESCR";
		case 10: return"NOTIFY";
		case 11: return"PREP_WRITE";
		case 12: return"EXEC";
		case 13: return"ACL";
		case 14: return"CANCEL_OPEN";
		case 15: return"SRVC_CHG";
		case 17: return"ENC_CMPL_CB";
		case 18: return"CFG_MTU";
		case 19: return"ADV_DATA";
		case 20: return"MULT_ADV_ENB";
		case 21: return"ADV_ADV_UPD";
		case 22: return"MULT_ADV_DATA";
		case 23: return"MULT_ADV_DIS";
		case 24: return"CONGEST";
		case 25: return"BTH_SCAN_ENB";
		case 26: return"BTH_SCAN_CFG";
		case 27: return"BTH_SCAN_RD";
		case 28: return"BTH_SCAN_THR";
		case 29: return"BTH_SCAN_PARAM";
		case 30: return"BTH_SCAN_DIS";
		case 31: return"SCAN_FLT_CFG";
		case 32: return"^SCAN_FLT_PARAM";
		case 33: return"SCAN_FLT_STATUS";
		case 34: return"ADV_VSC";
		case 38: return"REG_FOR_NOTIFY";
		case 39: return"UNREG_FOR_NOTIFY";
		case 40: return"CONNECT";
		case 41: return"DISCONNECT";
	}
	return "unknown GattcEvent";
}
static char *gapEvent2String(esp_gap_ble_cb_event_t event){
	switch(event){
		case 0: return "ADV_DATA_SET_COMPLETE";
		case 1: return "SCAN_RSP_DATA_SET_COMPLETE";
		case 2: return "SCAN_PARAM_SET_COMPLETE";
		case 3: return "SCAN_RESULT";
		case 4: return "ADV_DATA_RAW_SET_COMPLETE";
		case 5: return "SCAN_RSP_DATA_RAW_SET_COMPLETE";
		case 6: return "ADV_START_COMPLETE";
		case 7: return "SCAN_START_COMPLETE";
		case 8: return "AUTH_CMPL";
		case 9: return "KEY";
		case 10: return "SEC_REQ";
		case 11: return "PASSKEY_NOTIF";
		case 12: return "PASSKEY_REQ";
		case 13: return "OOB_REQ";
		case 14: return "LOCAL_IR";
		case 15: return "LOCAL_ER";
		case 16: return "NC_REQ";
		case 17: return "ADV_STOP_COMPLETE";
		case 18: return "SCAN_STOP_COMPLETE";
		case 19: return "SET_STATIC_RAND_ADDR";
		case 20: return "UPDATE_CONN_PARAMS";
		case 21: return "SET_PKT_LENGTH_COMPLETE";
		case 22: return "SET_LOCAL_PRIVACY_COMPLETE";
		case 23: return "REMOVE_BOND_DEV_COMPLETE";
		case 24: return "CLEAR_BOND_DEV_COMPLETE";
		case 25: return "GET_BOND_DEV_COMPLETE_EVT";
		case 26: return "READ_RSSI_COMPLETE";
	}
	return "unknown GapEvent";
}
void jsWarnGattsEvent(esp_gatts_cb_event_t event,esp_gatt_if_t gatts_if){
	if(bleEventDebug & ESP_BLE_DEBUG_GATTS)
		jsWarn("Event:ESP_GATTS_%s_EVT gatts_if:%d\n",gattsEvent2String(event), gatts_if);
}
void jsWarnGattcEvent(esp_gattc_cb_event_t event,esp_gatt_if_t gattc_if){
	if(bleEventDebug & ESP_BLE_DEBUG_GATTC)
		jsWarn("Event:ESP_GATTC_%s_EVT gattc_if:%d\n",gattcEvent2String(event), gattc_if);
}
void jsWarnGapEvent(esp_gap_ble_cb_event_t event){
	if(bleEventDebug & ESP_BLE_DEBUG_GAP)
		jsWarn("Event:ESP_GAP_BLE_%s_EVT\n",gapEvent2String(event));
}

void jsWarnUUID(esp_bt_uuid_t char_uuid){
	if (char_uuid.len == ESP_UUID_LEN_16) {
		jsWarn("- - - Char UUID16: %x", char_uuid.uuid.uuid16);
	} else if (char_uuid.len == ESP_UUID_LEN_32) {
		jsWarn("- - - Char UUID32: %x", char_uuid.uuid.uuid32);
	} else if (char_uuid.len == ESP_UUID_LEN_128) {
		jsWarn("- - - Char UUID128: %x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x,%x", char_uuid.uuid.uuid128[0],
			char_uuid.uuid.uuid128[1], char_uuid.uuid.uuid128[2], char_uuid.uuid.uuid128[3],
			char_uuid.uuid.uuid128[4], char_uuid.uuid.uuid128[5], char_uuid.uuid.uuid128[6],
			char_uuid.uuid.uuid128[7], char_uuid.uuid.uuid128[8], char_uuid.uuid.uuid128[9],
			char_uuid.uuid.uuid128[10], char_uuid.uuid.uuid128[11], char_uuid.uuid.uuid128[12],
			char_uuid.uuid.uuid128[13], char_uuid.uuid.uuid128[14], char_uuid.uuid.uuid128[15]);
	} else {
		jsWarn("- - - Char UNKNOWN LEN %d\n", char_uuid.len);
	}
}

void bleGetHiddenName(char *eventName, char *hiddenName, uint16_t pos){
	strcpy(eventName,hiddenName);
	itostr(pos,&eventName[strlen(eventName)],16);
}