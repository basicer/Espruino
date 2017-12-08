# Bluetooth on ESP32
Since the ESP32 provides Bluetooth, it would be a big step to get it running under Espruino.
A lot of questions arrived to that, but nobody started with an implementation
Therefore I decided to give it at try, even knowing about my poor knowledge in this area.
Plan was to work on these topics:


* `ESP-IDF example` get the examples in ESP-IDF running
* `Test environment` create an testing environment
* `Convert to Espruino` Convert example to get it compiled with Espruino
* `Other changes` Other changes to get it flashed and running
* `Simple Wrapper` Create a first low level wrapper for Javascript

After getting this running in a very simple version, first contact to Gordon about this happened.
Result was a change in actual sources made by Gordon. The idea behind was to go away a step from NFR oriented sources and make calls more general.
For that we now have bluetooth.h file, similiar to jshardware.h.


# Test environment
It turned out, that this was more complicated than expected. My idea was to use one of the existing tools for windows. But there are only a few, and I never became familiar with one of them. If somebody knows better, please let me know.
For Linux the world looks better, but my Environment is Windows and a virtual server somewhere in a Center.
There is still my Android Cellphone, and Nordic Semiconductors supports some free tools. 
* `NRF connect`
* `NRF Toolbox`
* `NRF UART`

could be installed immediately. There are some more, most of them need a lot of permissions. Test by yourself.
After installation, I could test with all tools and connection examples worked as expected.

# Convert to Espruino
As expected, this step was a up and down including tons of problems.
First the example needed to be split into C-file and H-file. That was easy to do.
ESP-IDF is under heavy construction for next release, and my decision was to always use latest available version from Github. There are a lot of changes in ESP-IDF, and with Espruino Branch is based on V2.1
This step was more complex and costs a lot of digging trough sources and make files.
Some time later this was done and first binary was available. Sounds good, but the size of the binary was about 1500 kb. Espruno itself at that time had 800kb.
Based on some feedback from ESP32 forum this could be reduced.
All changes are in Component config-> Bluetooth-> Bluedroid Bluetooth stack enabled
* `Bluedriod memory debug` Set to disabled
* `Close the bluedroid bt stack log print` Set to enabled
* `Classic Bluetooth` Set to disabled
* `Include BLE Security module (SMP)` Set to disabled

All of this brings up some limitations. On of them, Classic Bluetooth is disabled. Its not only a problem because of binary size, its also needs a lot of heap. Later on you will get some more information.
Just forgot, there are some more changes during make menuconfig.
* `Bluetooth` set enabled
* `Bluetooth-> Bluedroid` set enabled

In this folder you will find sdkconfig file with all changes

# Other changes
First of all Make file needs some extensions. To switch Bluetooth on/off for compilation a new variable, named USE_BLUETOOTH is created. See ESP32.make in this folder.
Since binary does not fit anymore in partition for apps, a new partition file was written, see partitions_espruinoBLE.csv in this folder.
New size of partition causes a new location for save area in Espruino. See ESP32.py in this folder. There is one more change in this file. Number of JsVars is reduced to 2000. This is a big step back for Espruino on ESP32. But otherwise Espruino would not start anymore.
There is no way, I know about, to calculate memory consumption. Some hints are in ESP32 Forum, but all together they have not been helpful to me. During endless testing I got all kinds of errors, from message no heap to absolutely nothing.
At the end I could connect from my android cell phone using NRF UART

# Actual sources
As mentioned above we need a file called bluetooth.c. Thats the startingpoint.
I don't like these overwhelming source files with thousands of lines. Therefore Functions are splitted into :
* esp32_gap_func, for gap related functions
* esp32_gatts_func, for gatt server related functions
* esp32_bluetooth_utils, for general utils

# Actual status
What we have right now is a subset of functions. Mainly it is the gatt server.
We still have to work with NRF class. This will be changed sooner or later by Gordon. 
Anyway, its a good starting point. Actual supported functions are :
* jsble_init
* jsble_advertising_start
* jsble_advertising_stop
* jsble_set_scanning
* jsble_set_services

Some more changes needed to be done in jswrap_bluetooth.c which belongs to the core of Espruino. I'm pretty sure, this will be moved to bluetooth.h by Gordon in a 2nd step.
There are some restriction right now. There is a javascript for testing in this folder. This will give some ideas. Restrictions up to now are :
* serial uart service is not supported
* only 16 bit uuids are supported
* Espruino uses a function to create advertizing data, which is not(?) available in Esp-Idf. Therefore we bypass/ignore this. Sideeffect is, that NRF.getAdvertisingData is not used/supported.
* Advertizing data is not supported, we only use options from NRF.setadvertizing.
* There are a lot of restrictions, that I don't even know today
* in this testing version we have 2000 jsvars only. Based on a minor change to free some memory, 3000 jsvars should be possible, and may be 4000..... There is a wrover version of ESP32 having a lot of psram, may be this will be some more help.

# Actual Problems
Main problem is understanding of Bluetooth itself. Available documentation is a pdf with more than 2800 pages. Implementation on ESP32 also is a big collection of structs, definitions and functions. Mostly description is not more than a sentence.
Bluetooth uses a lot of UUIDS, descriptors etc. As a newbie in this area, my understanding is still poor.
Windows has a, let me say, special way to support Bluetooth. Available tools are only a few. All of my testing is done with NRF connect on my Android.
There is a lot of caching done on client.
Source is more or less alpha status. It needs a lot of rework to make sure its running. Error handling is poor. All together its more or less a test of implementation only.
Last not least there is BLE itself. To implement something for your own use, is something nice. But at the moment when you are starting a product, Bluetooth organization comes into the market. And this can be very expensive.
