//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(0, 1);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";
const int channel = 100;
const int buttonPin = 2;
const int buttonOut = 3;
const int buttonPin2 = 4;
const int buttonOut2 = 5;
bool text[4] = {0, 0, 0};

void setup()
{
  radio.begin();
    while (!Serial);
    Serial.begin(9600);
  //set the address
  radio.openWritingPipe(address);
  //set the channel
  radio.setChannel(channel);
  //Set module as transmitter
  radio.stopListening();
  pinMode(buttonPin, INPUT);
  pinMode(buttonOut, OUTPUT);
  
}
void loop()
{
  //text[0] = 333;
  //float text[4] = {0, 0, 0};
  //Send message to receiver
  analogWrite(buttonOut, 1023);
  //const char text2[] = "yes";
 //buttonPressed = digitalRead(buttonPin);
 if(analogRead(buttonPin) < 1020){
  text[1] = 1;
  //Serial.println(text);
 }else if(analogRead(buttonPin2) < 1020){
  text[2] = 1;
 }else{
  text[1] = 0;
  text[2] = 0;
 }
 radio.write( text, sizeof(text));
 Serial.println(analogRead(buttonPin));
}
