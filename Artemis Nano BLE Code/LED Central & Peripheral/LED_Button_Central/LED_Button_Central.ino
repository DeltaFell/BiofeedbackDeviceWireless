#include <ArduinoBLE.h>

const String Uuid1 = "055908C9DADF0319A23643B6BB748976";
const String Uuid2 = "8B7F74CB4B273F3F27AB51FDDDBDEB1A";
const int ledPin = LED_BUILTIN;

void setup() {
  // put your setup code here, to run once:
BLE.scanForUuid(Uuid1);

}

void loop() {
  // put your main code here, to run repeatedly:
  BLEDevice peripheralOne = BLE.available();
  if(peripheralOne){
    if(peripheralOne.localName() != "button1"){
      return;
    }
    BLE.stopScan();
    BLE.scanForUuid(Uuid2);
    BLEDevice peripheralTwo = BLE.available();
    if(peripheralTwo){
      if(peripheralTwo.localName() != "button2"){
        return;
      }
      BLE.stopScan();
      
      cimputer(peripheralOne, peripheralTwo);
      
    }
  }

}

void cimputer(BLEDevice peripheralOne, BLEDevice peripheralTwo){
  BLECharacteristic button1Characteristic = peripheralOne.characteristic("055908C9DADF0319A23643B6BB748976");
  BLECharacteristic button2Characteristic = peripheralTwo.characteristic("8B7F74CB4B273F3F27AB51FDDDBDEB1A");
  while(peripheralOne.connected()){
    while(peripheralTwo.connected()){
      if(button1Characteristic && button2Characteristic){
        digitalWrite(ledPin, HIGH);
      }else{
        digitalWrite(ledPin, LOW);
      }
    }
  }
}
