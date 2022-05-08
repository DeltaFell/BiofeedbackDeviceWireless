//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>



//create an RF24 object
int CE = 1;
int CSN = 0;
RF24 radio(CE, CSN);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";
const int channel = 100;
const int buttonPin = 2;
const int buttonOut = 3;
const int buttonPin2 = 5;
const int buttonOut2 = 9;
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
  pinMode(buttonPin2, INPUT);
  pinMode(buttonOut2, OUTPUT);
  
}
void loop()
{
  text[0] = 1;
  //float text[4] = {0, 0, 0};
  //Send message to receiver
  analogWrite(buttonOut, 1023);
  analogWrite(buttonOut2, 16383);
  //Serial.println(analogRead(buttonPin2));
   Serial.println(analogRead(buttonPin));
  //const char text2[] = "yes";
 //buttonPressed = digitalRead(buttonPin);
 if(analogRead(buttonPin) > 14){
  text[1] = 1;
  //Serial.println(text);
 }else{
 text[1] = 0; 
 }
 if(analogRead(buttonPin2) > 1020){
  text[2] = 1;
  //Serial.print("pin 2 ");
  //Serial.println(analogRead(buttonPin2));
 }else{
  text[2] = 0;
 }
 radio.write( text, sizeof(text));
 //Serial.println(text[1]);
 //Serial.println(analogRead(buttonPin));
}
