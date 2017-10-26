/*
 * This file is part of Espruino, a JavaScript interpreter for Microcontrollers
 *
 * Copyright (C) 2013 Gordon Williams <gw@pur3.co.uk>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * ----------------------------------------------------------------------------
 * ESP32 specific BLE exposed components.
 * ----------------------------------------------------------------------------
 */
#include <stdio.h>
 
#include "jswrap_esp32_BLE.h"
#include "BLE/gatts_func.h"

#include "jsparse.h"

/*JSON{
	"type":"class",
	"class":"BLE"
}
BLE Class first testing
*/

/*JSON{
	"class":"BLE",
	"name":"init_bt",
	"type"     : "staticmethod",
	"generate" : "jswrap_BLE_init_bt"	
}
inits and enables Bluetooth
*/
void jswrap_BLE_init_bt(){
	bt_init();
}

/*JSON{
	"class": "BLE",
	"name":"init_gatts",
	"type"     : "staticmethod",
	"generate" : "jswrap_BLE_init_gatts"
}
inits GAP, GATTS
*/
void jswrap_BLE_init_gatts() {
	gatts_init();
}

/*JSON{
	"class": "BLE",
	"name":"setDeviceName",
	"type"     : "staticmethod",
	"generate" : "jswrap_BLE_setDeviceName",
	"params"   : [
    ["jsDeviceName", "JsVar", "Name of BT device for scans"]
	]
}
set Devicename, set before calling init_gatts
*/
void jswrap_BLE_setDeviceName(JsVar *jsDeviceName) {
	bt_setDeviceName(jsDeviceName);
}

/*JSON{
	"class":"BLE",
	"name":"setServiceUUID",
	"type"     : "staticmethod",  
	"generate" : "jswrap_BLE_setServiceUUID",
	"params"   : [
    ["jsServiceUUID", "JsVar", "UUID for service"]
	]
}
set UUID for service, set before calling init_gatts
*/
void jswrap_BLE_setServiceUUID(JsVar *jsServiceUUID) {
	bt_setServiceUUID(jsServiceUUID);
}

/*JSON{
	"class":"BLE",
	"name":"setReadFunction",
	"type"     : "staticmethod",  
	"generate" : "jswrap_BLE_setReadFunction",
	"params" : [
    ["function","JsVar","A Function or String to be executed"]
	]
}
*/
void jswrap_BLE_setReadFunction(JsVar *func){
	if (!jsvIsFunction(func)) func=0;
	jsvObjectSetChild(execInfo.root, BLE_READ_EVENT, func);
}

/*JSON{
	"class": "BLE",
	"name":"notify",
	"type"     : "staticmethod",
	"generate" : "jswrap_BLE_notify",
	"params"   : [
    ["jsvalue", "JsVar", "Text for notification"]
	]
}
send notification
*/
void jswrap_BLE_notify(JsVar *jsvalue){
	bt_notify(jsvalue);
}

/*JSON{
	"class": "BLE",
	"name": "scan",
	"type"     : "staticmethod",
	"generate" : "jswrap_BLE_scan",
	"params"   : [
    ["duration", "int", "scan duration in secs"]
	]
}
scan for BLE devices
*/
void jswrap_BLE_scan(int duration){
  bt_scan(duration);	
}

/*JSON{
	"type" : "event",
	"class" : "BLE",
	"name" : "connect"
}
Called when a client connects
*/
 
/*JSON{
	"type":"event",
	"class":"BLE",
	"name" : "disconnect"
}
Called when a client disconnects
*/
 
/*JSON{
	"type":"event",
	"class":"BLE",
	"name":"data"
}
Called when a client sent data, param is data as string
 */
 
/*JSON{
	"type":"event",
	"class":"BLE",
	"name":"scan"
}
Called when scan finds a new device,param is device name
 */
 