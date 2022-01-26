//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
RF24 radio(0, 1);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";
const int channel = 100;
const int ledPin = 2;
void setup()
{
  radio.begin();
  
  //set the address
  radio.openWritingPipe(address);
  //set the channel
  radio.setChannel(channel);
  //Set module as transmitter
  radio.stopListening();
  pinMode(ledPin, INPUT);
}
void loop()
{
  //Send message to receiver
  const char text[] = "Hello World";
  radio.write(&text, sizeof(text));
  
  delay(1000);
}
