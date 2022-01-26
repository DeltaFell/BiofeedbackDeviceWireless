//Include Libraries
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

//create an RF24 object
int CE = 0;
int CSN =1;
RF24 radio(CE, CSN);  // CE, CSN

//address through which two modules communicate.
const byte address[6] = "00001";
const int channel = 100;
const char msg[] = "Hello World";
int ledPin = 8;
void setup()
{
  while (!Serial);
    Serial.begin(9600);
  
  radio.begin();
  
  //set the address
  radio.openReadingPipe(0, address);
  //set the channel
  radio.setChannel(channel);
  //Set module as receiver
  radio.startListening();
}

void loop()
{
  //Read the data if available in buffer
  if (radio.available())
  {
    char text[32] = {0};
    radio.read(&text, sizeof(text));
    Serial.println(text);
    //if(!strcmp(text,msg)){
      //digitalWrite(ledPin,HIGH);
      //delay(100);
      //digitalWrite(ledPin,LOW);      
      //}
  }
}
