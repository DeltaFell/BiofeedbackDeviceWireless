#include <ArduinoBLE.h>

BLEService buttonService("055908C9DADF0319A23643B6BB748976");
BLEByteCharacteristic buttonCharacteristic("055908C9DADF0319A23643B6BB748976", BLERead | BLEWrite | BLENotify | BLEIndicate);

const int buttonPin = 2;
int buttonState = LOW;
int oldButtonState = LOW;
void setup() {
  // put your setup code here, to run once:
pinMode(buttonPin, INPUT);
//if(!BLE.begin()){
  
//}
BLE.setLocalName("button1");
BLE.setAdvertisedService(buttonService);
buttonService.addCharacteristic(buttonCharacteristic);
BLE.addService(buttonService);
buttonCharacteristic.writeValue(0);
BLE.advertise();
}

void loop() {
  // put your main code here, to run repeatedly:
  BLEDevice central = BLE.central();
  buttonState = digitalRead(buttonPin);
  if(oldButtonState != buttonState){
    oldButtonState = buttonState;
  }
  if(buttonState){
    buttonCharacteristic.writeValue((byte)0x01);
  }else{
    buttonCharacteristic.writeValue((byte)0x00);
  }

}
