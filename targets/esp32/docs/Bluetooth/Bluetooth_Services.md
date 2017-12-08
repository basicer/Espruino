# Bluetooth Services on ESP32
In this part you will find a short explanation, how services are implemented.

##Bluetooth Initialization
General init for Bluetooth is to init and enable the hardware.During this a lot of memory ia allocated. Since we don't support Classic Bluetooth, we can release a part of this.
Next we init and enable bluedroid, which is the BLE implementation of ESP-idf.
Last not least we register callbacks for GAP and for GATT.
Up to today, only services are implemented. May be, we will get more callbacks once we support ESP being a client. At that time we will get the BluetoothRemote-classes
BTW, local MTU is set and I've no idea why. But its done in all samples and you never know ;-)
##GAP
Main part of actual GAP implemetation is scanning of other Bluetooth devices and advertizing, so that others Bluetooth devices will see.
Most important part of the implementaion is the GAP handler registered during initialization. The handler has 2 parts, first one handles events scanning.
For each device found during scanning, a callback with some information like name and signal strength is sent.
Second one works for advertizing of itself. Here we tell our name and some other data. 
##GATTS
Once again, important part is the handler registered during initialization. Today we only support GATTS, which is for services. GATTC will follow later, once we implement client functions.
##Services
If somebody wants to read more about BLE, there is a technical description available. This has close to 3000 pages. Let me try to give a short introduction first.
* service is a tool that delivers data. For Bluetooth we have a lot of predefined services. If you want to support a service like a clinic Thermometer, you will find a unique number, UUID, for that. These UUIDS can be 16bit, 32bit or 128bit.
* characteristic is a value given by the service. In our example it is the temperature. And oviously we once again have a UUID.
* descriptors give some more information about the characteristic, like a description or permissions.
For all of these parts a structure is available. Actually we statically allocated memory for that. Means we are restricted to 4 services with 3 characteristics and 6 descriptions each.
From Espruino wrapper we get an object, which is copied. Have in mind, only 16 bit UUIDS are supported right now. Espruino itself supports all types but conversion to ESP-idf is complex. There is a lot of room for optimization. If somebody wants to work on this, please contact me.
Now lets got to tell ESP32 about the new service.
1. register an application, or if no more, start advertizing
2. we get a REG-Event with a Interface id and start the service. At this time we need to know, how many handles are used for this service. Easy to do for static services, but for Espruino we need to calculate this.
3. we get a START-Event and
4. add characteristic, if no more goto 1.
5. we get a ADD_CHAR-Event with a handle
6. store this handle
7. add description, if no more goto 4.
8. we get a ADD_CHAR_DESCR-Event with a handle
9. store this handle
10. goto 7.

##Service events
* CONNECT-Event is called whenever a client connects to a service. For Espruino we create an event on("connect",function.......) Stopping of advertizing is automatically done in the background, since only on connection at a time is possible.
* DISCONNECT-Event is called if a connected client disconnects. For Espruino we create an event on("disconnect",function .......) and start advertizing, to give other client the chance to connect.
* READ-Event is called, whenever a client reads a charcteristic. This happens for values and for descriptions. In a response the value is sent back to the client. Something like this event is not supported by NRF, therefore we will not create an event for Espruino
* WRITE-Event is called, whenever a client sends a new value for a characteristic. Generally it would be possible to write description too, but we don't support this in Espruino. An event for Espruino is created so we get to know in our application
