/*
 *
 * Complete project details at
 * Feed your cat created by Ruizhe Shang
 * 
 * 
The circuit:
 
DS1307 RTC 
 * RTC SCL to analog pin 5
 * RTC SDA to analog pin 4

Stepper Motor
 * IN1 to digital pin 2
 * IN2 to digital pin 3
 * IN3 to digital pin 4
 * IN4 to digital pin 5
 
Servo
 * 
 
1602 LCD
 * 
 */

#include <TimeLib.h>
#include <TimeAlarms.h>
#include <Wire.h>
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t
#include <Unistep2.h>
#include <LiquidCrystal.h>


const int led = 13; 

// stepper motor setup
Unistep2 stepperX(2, 3, 4, 5, 4096, 1000); // pins for IN1, IN2, IN3, IN4, steps per rev, step delay(in micros)

// LCD screen connection setup
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int timesToFeed = 0; // circles stepper motor should run to feed that cat

int feedBreakfast = 10; 
int feedLunch = 12; 
int feedDinner = 11;

void setup() {
  // prepare pin as output
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
  
  Serial.begin(9600);
  // wait for Arduino Serial Monitor
  while (!Serial) ; 
  
  // get and set the time from the RTC
  setSyncProvider(RTC.get);   
  if (timeStatus() != timeSet) 
     Serial.println("Unable to sync with the RTC");
  else
     Serial.println("RTC has set the system time");     
  // to test your project, you can set the time manually 
  //setTime(8,29,0,1,1,11); // set time to Saturday 8:29:00am Jan 1 2011

  // init LCD screen
  lcd.begin(16, 2);

  // create the alarms, to feed your cats food
  Alarm.alarmRepeat(7, 0, 0, breakfastFeed);  // feed breakfast at 7:45 am
  Alarm.alarmRepeat(12, 0, 0, lunchFeed);      // feed lunch at 12:00 am
  Alarm.alarmRepeat(18, 0, 0, dinnerFeed);    // feed dinner at 17:45 am
}

void loop() {
  digitalClockDisplay();
  displayNextFeed();
  // wait one second between each clock display in serial monitor
  Alarm.delay(1000); 
}

// functions to be called when feed your cat breakfast
void breakfastFeed() {
  // write here the task to perform every morning
  Serial.println("Start to feed breakfast");
  // todo: need to add some LCD codes
  while (timesToFeed < feedBreakfast) {
    stepperX.run();
    if ( stepperX.stepsToGo() == 0 ){ // If stepsToGo returns 0 the stepper is not moving
      stepperX.move(4096);
      Serial.print("this is the movement: ");
      Serial.println(timesToFeed);
      timesToFeed++;
    }
  }
  stepperX.stop();
}

void lunchFeed() {
  // write here the task to perform every noon
  Serial.println("Start to feed lunch");
  // todo: need to add some LCD codes
  while (timesToFeed < feedLunch) {
    stepperX.run();
    if ( stepperX.stepsToGo() == 0 ){ // If stepsToGo returns 0 the stepper is not moving
      stepperX.move(4096);
      Serial.print("this is the movement: ");
      Serial.println(timesToFeed);
      timesToFeed++;
    }
  }
  stepperX.stop();
}

void dinnerFeed() {
  // write here the task to perform every evening
  Serial.println("Start to feed dinner");
  // todo: need to add some LCD codes
  while (timesToFeed < feedDinner) {
    stepperX.run();
    if ( stepperX.stepsToGo() == 0 ){ // If stepsToGo returns 0 the stepper is not moving
      stepperX.move(4096);
      Serial.print("this is the movement: ");
      Serial.println(timesToFeed);
      timesToFeed++;
    }
  }
  stepperX.stop();
}

void digitalClockDisplay() {
  // digital clock display of the time
  Serial.print("Current time: ");
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
}

void printDigits(int digits) {
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void displayNextFeed() {
  if (hour() < 7) {
    Serial.println("Next feed is at 7:00 AM");
  }
  else if (hour() > 7 && hour() <12) {
    Serial.println("Next feed time is at 12:00 AM");
  }
  else if (hour() > 12 && hour() <18) {
    Serial.println("Next feed time is at 18:00 PM");
  }
  else {
    Serial.println("Next feed is at 7:00 AM");
  }
}
