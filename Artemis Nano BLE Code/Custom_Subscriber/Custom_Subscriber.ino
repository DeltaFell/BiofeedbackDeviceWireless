#include <ArduinoBLE.h>

const char* deviceServiceUuid = "180F";
const char* deviceServiceCharacteristicUuid = "2A19";

void setup() {
  // put your setup code here, to run once:
Serial.begin(19200);
if(!BLE.begin()){
  Serial.println("starting BLE failed");
}
}

void loop() {
  // put your main code here, to run repeatedly:
  connectToPeripheral();
}

void connectToPeripheral(){
  BLEDevice peripheral;
  do
  {
    BLE.scanForUuid();
    peripheral = BLE.available();
    delay(100);
  } while(!peripheral);
   if(peripheral){
    //prints out the address, local name and advertised service of found peripherals
    Serial.print("Found  ");
    Serial.print(peripheral.address());
    Serial.print(" '");
    Serial.print(peripheral.localName());
    Serial.print("' ");
    Serial.print(peripheral.advertisedServiceUuid());
    Serial.println();
    //stop scanning
    BLE.stopScan();
    getDataPeripheral(peripheral);
   }
}
void getDataPeripheral (BLEDevice peripheral){
  Serial.println("Connecting");
  if(peripheral.connect()){
    Serial.println("Connected");
  }else{
    Serial.println("Failed to connect.");
    return;
  }
  Serial.println("Discovering Attributes");
  if(peripheral.discoverAttributes()){
    Serial.println("Attributes discovered");
  }else{
    Serial.println("Attribute discovery failed.")
    peripheral.disconnect();
    return;
  }
  BLECharacteristic batCharacteristic = peripheral.characteristic(deviceServiceCharacteristicUuid);
  //subscribe to the simple key characteristic
  Serial.println("Subscribing to simple key characteristic ...");
  if(!batCharacteristic){
    Serial.println("no gesture characteristic found!");
    peripheral.disconnect();
    return;
  }else if(!batCharacteristic.canSubscribe()0{
    Serial.println("subscription failed!");
    peripheral.disconnect();
    return;
  }else{
    Serial.println("Subscribed");
  }
  byte val;
  batCharacteristic.readValue(val);
  Serial.println(val);
}
