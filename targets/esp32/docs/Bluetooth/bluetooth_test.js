function log(x){
  console.log(x + "\n");
}
function set(nr){
  var ble;
  switch(nr){
    case 1:
      ble = {0xBCDE : { 0xABCD : { value : "Hello", readable : true,description:"mydesc" } },
             0xCDEF : { 0xBCDE : { value : "Hallo", readable : true, writable:true },
                        0x1234 : { value : "Egon", readable : true  } } }; break;
    case 2:
      ble = {0xBCDE : { 0xABCD :{ value : "hello", readable : true } } }; break;
    case 3: ble = {0x1350:
                    {0x1352:{value:"1352",readable:true,
                             onRead:function(){log("r1352"); return "1353";}
                            },
                     0x1354:{value:"1354",readable:true,writable:true,
                             onWrite:function(){log("w1354");}}
                            }
                  }; break;
    case 4: ble = {0x1360:{ 0x1362:{value:"1362", readable:true, writable:true},
                            0x1364:{value:"1364", readable:true, writable:true},
                            0x1366:{value:"1377", readable:true, writable:true}
                  }
            };
    }
  NRF.setServices(ble,{uart:false});
  NRF.setAdvertising({}, {name: "My ESP32",showName: true,discoverable: true});

}
NRF.on("connect",function(data){console.log("connect:" + JSON.stringify(data));});
NRF.on("disconnect",function(data){console.log("disconnect:" + JSON.stringify(data));});
