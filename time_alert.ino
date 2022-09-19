/*
 *
 * Complete project details at https://randomnerdtutorials.com    
 * Based on TimeAlarmExample from TimeAlarms library created by Michael Margolis
 *
 */

#include <TimeLib.h>
#include <TimeAlarms.h>
#include <Wire.h>
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t
#include <LiquidCrystal.h>


const int led = 13; 


// LCD screen connection setup
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

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

  // create the alarms, to trigger functions at specific times
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

// functions to be called when an alarm triggers
void breakfastFeed() {
  // write here the task to perform every morning
  Serial.println("Tturn light off");
  digitalWrite(led, LOW);
}

void lunchFeed() {
  // write here the task to perform every evening
  Serial.println("Turn light on");
  digitalWrite(led, HIGH);
}

void dinnerFeed() {
  // write here the task to perform every evening
  Serial.println("Turn light on");
  digitalWrite(led, HIGH);
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
