#include<SD.h>
#include"RTClib.h"
#include"pitches.h"

#define SD_CARD 4
#define LED_1 A3
#define LED_2 8
#define LED_3 A5
#define BUZZER 10
#define FLEX A0
#define PRESS_1 A1
#define PRESS_2 A2

bool knee_lift = false;
bool heel_strike = false;
bool toe_hit = false;
bool toe_lift = false;

int counter = 0;
int num_knee_bends = 0;
int num_heel_strikes = 0;
int num_toe_lifts = 0;
int num_gaits = 0;

File data_file;

RTC_PCF8523 rtc;

void setup() {
  Serial.begin(9600);

  //Set up the pins, for the leds and buzzer
  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  //Turning off all LEDs
  digitalWrite(LED_1, HIGH);
  digitalWrite(LED_2, HIGH);
  digitalWrite(LED_3, HIGH);

  //Setting Up real time clock
  if (!rtc.initialized() || rtc.lostPower()){
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }

  //Start RTC
  rtc.start();



  //Setting up SD Card
  pinMode(SD_CARD, OUTPUT);

  if (!SD.begin(SD_CARD)){
    Serial.println("Initialization failed!");
    return;
  }
  Serial.println("Initialization complete!");

  data_file = SD.open("data_file.txt", FILE_WRITE);

  //(NOT DONE) Write to the SD card starting up time to the sd card
  DateTime now = rtc.now();

  //If the sd card opened fine write to it
  if (data_file){
      data_file.println("Start Up Time: " + String(now.month()) + "/" + String(now.day()) + "/" + String(now.year()) + ", " + String(now.hour()) + ":" + String(now.minute()));
      data_file.close();
  } else {
    Serial.println("Error opening the SD Card");
  }
  
}

void loop() {
  
  //Knee Bend While loop
  while (!knee_lift){
    delay (100);

    //Write to SD Card
    print_status();
    
    if (analogRead(FLEX) == 200){
      knee_lift = true;
    }
  }
  knee_lift = false;
  
  //Write to the SD Card (Write the date and time, and number of completed cycles)
  DateTime now = rtc.now();

  //Write to SD Card
  print_status();
  
  
  //Turn on the first LED for one second
  //Turn on the Buzzer
  //Turn of the first LED
  //Turn of the Buzzer
  //Knee Bend While loop
  while (!knee_lift){
    delay (10);
    if (analogRead(FLEX) < 300){
      knee_lift = true;
    }
    Serial.println(analogRead(FLEX));

    //Write to SD Card
    print_status();
  }

  //Reset Variables
  knee_lift = false;

  //Increase numbers
  num_knee_bends++;

  //Write to SD Card
  print_status();
    
  //Turn on the first LED for one second
  Serial.println("LED ON");
  digitalWrite(LED_1, LOW);
  tone (BUZZER, NOTE_B5, 1000);
  delay(1000);
  
  //Turn off the first LED
  digitalWrite(LED_1, HIGH);

  
  //Heel Strike While loop
  //Write to the SD Card
  //Turn on the first LED for one second
  //Turn on the Buzzer
  //Turn of the first LED
  //Turn of the Buzzer
  while(!heel_strike){
    if (counter == 3000){
      counter = 0;
      return;
    }

    if (analogRead(PRESS_1) > 300){
      heel_strike = true;
    }
    Serial.println(analogRead(PRESS_1));

    //Write to SD Card
    print_status();
    
    counter++;
    delay(1);
  }

  //Reset Variables
  counter = 0;
  heel_strike = false;

  //Increment numbers
  num_heel_strikes++;
  
  //Write to SD Card
  print_status();

  //Turn on the second LED for one second
  digitalWrite(LED_2, HIGH);
  tone (BUZZER, NOTE_B5, 1000);
  delay(1000);
  
  //Turn of the second LED
  digitalWrite(LED_2, LOW);

  
  //Toe Lift while loop
  //Write to the SD Card
  //Turn on the first LED for one second
  //Turn on the Buzzer
  //Turn of the first LED
  //Turn of the Buzzer
  while(!toe_lift){
    if(counter == 3000){
      counter = 0;
      return;
    }

    //If the pressure sensor has been pressed, start
    //looking for the release
    if (analogRead(PRESS_2) > 300){
      toe_hit = true;
    }

    if (toe_hit) {
      if (analogRead(PRESS_2) < 100) toe_lift = true;
    }

    //Write to SD Card
    print_status();
    
    counter++;
    delay(1);
  }

  //Reset Variables
  toe_hit = false;
  toe_lift = false;
  counter = 0;

  //Increase numbers
  num_gaits++;
  num_toe_lifts++;

  //Write to SD Card
  print_status();

  //Turn on the third LED for one second
  digitalWrite(LED_3, HIGH);
  tone (BUZZER, NOTE_B5, 1000);
  delay(1000);
  
  //Turn of the third LED
  digitalWrite(LED_3, LOW);
}

//Prints the amount of complete cycles that there have been
//and prints out the number of knee bends, heel strikes, 
// and the number of toe lifts
void print_status(){

  //Open SD Card
  data_file = SD.open("data_file.txt", FILE_WRITE);

  //If SD Card is fine, write to it
  if (data_file){
    //NOT DONE: Needs the information to be written to the SD Card
  }else {
    Serial.println("Error opening the SD Card");
  }
}
