// Copyright 2015-2017 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/****************************************************************************
*
* This file is for gatt server. It can send adv data, be connected by clent.
* Run the gatt_client demo, the client demo will automatically connect to the gatt_server demo.
* Client demo will enable gatt_server's notify after connection. Then two devices will exchange
* data.
*
****************************************************************************/
#ifndef GATTS_FUNC_H_
#define GATTS_FUNC_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "jsvar.h"

#define BLE_READ_EVENT JS_EVENT_PREFIX"bler"

#define GATTS_TAG "GATTS_DEMO"

#define GATTS_SERVICE_UUID_TEST_A   0x00FF
#define GATTS_CHAR_UUID_TEST_A      0xFF01
#define GATTS_DESCR_UUID_TEST_A     0x3334
#define GATTS_NUM_HANDLE_TEST_A     4

#define TEST_DEVICE_NAME            "ESP32_SimpleBLE"
#define TEST_MANUFACTURER_DATA_LEN  17

#define GATTS_DEMO_CHAR_VAL_LEN_MAX 0x40

#define PREPARE_BUF_MAX_SIZE 1024

void bt_init();
void gatts_init();
void bt_setDeviceName(JsVar *jsDeviceName);
void bt_setServiceUUID(JsVar *jsServiceUUID);
void bt_notify(JsVar *data);
void bt_scan(int duration);

#endif /* GATTS_FUNC_H_ */
