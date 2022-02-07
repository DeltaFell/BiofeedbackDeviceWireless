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
const char msg[] = "pressed";
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
    char text[32] = {0};
    radio.read(&text, sizeof(text));
    Serial.println(text);
    
    //digitalWrite(buttonOut, HIGH);
    if(!strcmp(text,msg)){
      digitalWrite(buttonOut,HIGH);
      Serial.println("yes please");
      //delay(100);
            
      }else{
        digitalWrite(buttonOut,LOW);
        Serial.println("no fuck you");
      }
  }
}
