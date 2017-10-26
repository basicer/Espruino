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
* `More complex..` 
* `Actual problems`

# ESP-IDF example
It turned out, that compiling an example and flash it to my board was easy solved.
All examples could be compiled without any problems. My choice for next steps was the GATT Server.

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
See gatts_func.h and gatts_func.c to see new files. There are also 2 more files, jswrapper_esp32_BLE.c and jswrapper_esp32_BLE.h in same folder.
Still at the end, size of binary is 1047KB

# Other changes
First of all Make file needs some extensions. To switch Bluetooth on/off for compilation a new variable, named BLE is created. See ESP32.make in this folder.
Since binary does not fit anymore in partition for apps, a new partition file was written, see partitions_espruinoBLE.csv in this folder.
New size of partition causes a new location for save area in Espruino. See ESP32.py in this folder. There is one more change in this file. Number of JsVars is reduced to 2000. This is a big step back for Espruino on ESP32. But otherwise Espruino would not start anymore.
There is no way, I know about, to calculate memory consumption. Some hints are in ESP32 Forum, but all together they have not been helpful to me. During endless testing I got all kinds of errors, from message no heap to absolutely nothing.
At the end I could connect from my android cell phone using NRF UART

# Simple Wrapper
During testing all functions have been started directly. Next step was to create a kind of javascript wrapper to start BLE server. Following functions are available:
* `BLE` BLE class
* `BLE.init_bt()` enables Bluetooth
* `BLE.init_gatts()` enables GAP, GATTS and starts gatts server
* `BLE.setDeviceName(name)` sets name of ESP32, shown if somebody scans for devices
* `BLE.setServieUUID(id)` sets Service UUID
* `BLE.scan(time)` starts scanning for BT devices
* `BLE.setReadFunction(fnc)` sets callback, called whenever a read is sent by client
* `conect` Event which is fired if somebody connects to the server, returns name of client
* `disconnect` Event is fired on disconnecting, returns name of client
* `data` Event is fired, whenever a client sends some data, returns data
* `scan` Event is fired for each device found during BLE.scan

# More complex
Plan was to create some more complex functions to match existing Blootooth implementation for Espruino. First of all a lot of problems appeared during testing up to the actual status, where I don't even get the status running, mentioned above.
Next my konwledge is far beyond whats needed to understand the bluetooth wrapper from Espruino.

# Actual Problems
Main problem is understanding of Bluetooth itself. Available documentation is a pdf with more than 2800 pages. Implementation on ESP32 also is a big collection of structs, definitions and functions. Mostly description is not more than a sentence.
Bluetooth uses a lot of UUIDS, descriptors etc. As a newbie in this area, my understanding is still poor.
Windows has a, let me say, special way to support Bluetooth. Available tools are only a few. All of my testing is done with NRF connect on my Android.
There is a lot of caching done on client. Did not find a way to tell
Espruino already has an implementation of Bluetooth. This includes much more functionality than in my test. Right now I've no idea how to marry my functions. Looks like beeing a large job, and I'm not sure yet where the benefit is.
Source is more or less alpha status. It needs a lot of rework to make sure its running. Error handling is poor and there is a lot of logging. All together its more or less a test of implementation only.
Last not least there is BLE itself. To implement something for your own use, is something nice. But at the moment when you are starting a product, Blurtooth organization comes into the market. And this can be very expensive.
