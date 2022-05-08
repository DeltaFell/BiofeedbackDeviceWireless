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
const int ledOut2 = 4;
const int ledOut3 = 5;
const int buzz = 9;
const int A4 = 440;
const int B4 = 494;
const int C5 = 523;
int note = 0;
bool text[4] = {0,0,0,0};
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
    digitalWrite(LED_BUILTIN, LOW);
    bool beans[4] = {0,0,0,0};
    radio.read(&beans, sizeof(beans));
    if(beans[0]){
      text[1] = beans[1];
      text[2] = beans[2];
    } else{
      text[3] = beans[3];
    }
    Serial.println(text[2]);
    note = 0;
    //digitalWrite(buttonOut, HIGH);
    if(text[1]){
      digitalWrite(buttonOut,HIGH);
      //tone(buzz, B5);
      //digitalWrite(buzz,HIGH);
      note = A4;
      Serial.println("Signal 1"); 
      }else {
        digitalWrite(buttonOut,LOW);
        //digitalWrite(buzz,LOW);
        //noTone(buzz);
      }
      
      if(text[2]){
        digitalWrite(ledOut2,HIGH);
         //tone(buzz, B5);
         //digitalWrite(buzz,HIGH);
         note = B4;
        Serial.println("Signal 2");
      }else {
        digitalWrite(ledOut2,LOW);
        //digitalWrite(buzz,LOW);
        //noTone(buzz);
      }
      
      if(text[3]){
        digitalWrite(ledOut3,HIGH);
         //tone(buzz, B5);
         //digitalWrite(buzz,HIGH);
         note = C5;
        Serial.println("Signal 3");
      }else {
        digitalWrite(ledOut3,LOW);
        //digitalWrite(buzz,LOW);
        //noTone(buzz);
      }
      if(!text[1] && !text[2] && !text[3]){
        Serial.println("No Signal");
        note = 0;
        //noTone(buzz);
      }
      tone(buzz,880,100);
      delay(100);
  }
  if(!radio.available()){
    digitalWrite(buttonOut,LOW);
    digitalWrite(ledOut2,LOW);
    digitalWrite(ledOut3,LOW);
    Serial.println("No Radio Detected");
    digitalWrite(LED_BUILTIN, HIGH);
    tone(buzz,880,4000);
    tone(8,880,4000);
    delay(4000);
    
  }
 
}
