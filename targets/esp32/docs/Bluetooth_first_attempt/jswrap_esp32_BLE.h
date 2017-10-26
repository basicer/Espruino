/*
 * This file is part of Espruino, a JavaScript interpreter for Microcontrollers
 *
 * Copyright (C) 2015 Gordon Williams <gw@pur3.co.uk>
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * ----------------------------------------------------------------------------
 * This file is designed to be parsed during the build process
 *
 * Contains ESP32 board specific function definitions.
 * ----------------------------------------------------------------------------
 */
#ifndef TARGETS_ESP32_JSWRAP_BLE_H_
#define TARGETS_ESP32_JSWRAP_BLE_H_
#include "jsvar.h"
#include "jspin.h"

//===== ESP32 BLE Library
void jswrap_BLE_init_bt();
void jswrap_BLE_init_gatts();
void jswrap_BLE_setDeviceName(JsVar *jsDeviceName);
void jswrap_BLE_setServiceUUID(JsVar *jsServiceUUID);
void jswrap_BLE_setReadFunction(JsVar *func);
void jswrap_BLE_notify(JsVar *jsvalue);
void jswrap_BLE_scan(int duration);

#endif /* TARGETS_ESP32_JSWRAP_BLE_H_ */
