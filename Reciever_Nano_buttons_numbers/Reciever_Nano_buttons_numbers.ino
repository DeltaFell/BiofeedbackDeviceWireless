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
const char msg[] = "yes";
int ledPin = 8;
const int buttonPin = 2;
const int buttonOut = 3;


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
  pinMode(buttonPin, INPUT);
  pinMode(buttonOut, OUTPUT);
}
void loop()
{

  //Read the data if available in buffer
  if (radio.available())
  {
    bool text[4] = {0,0,0};
    radio.read(&text, sizeof(text));
    //Serial.println(text);
    
    //digitalWrite(buttonOut, HIGH);
    if(text[1]){
      digitalWrite(buttonOut,HIGH);
      Serial.println("Signal 1");
      //delay(100);
            
      }if(text[2]){
        digitalWrite(buttonOut,LOW);
        Serial.println("Signal 2");
      }if(text[3]){
        Serial.println("Signal 3");
      }if(!text[1] && !text[2] && !text[3]){
        Serial.println("No Signal");
      }
  }
}
