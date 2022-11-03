#include <Arduino.h>

#include <Wire.h>  
#include "RTClib.h"  
RTC_DS1307 rtc;  
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}; 


void setup() 
{
  while (!Serial); // for Leonardo/Micro/Zero  
  Serial.begin(9600);

  //Piscar LED
  pinMode(LED_BUILTIN, OUTPUT);

  //Módulo RTC - Relógio  
  if (!rtc.begin()) 
  {  
    Serial.println("Couldn't find RTC");  
    while (1);  
  }
  if (!rtc.isrunning()) 
  {  
    Serial.println("RTC is NOT running!");  
    // following line sets the RTC to the date & time this sketch was compiled  
    // rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  
    // This line sets the RTC with an explicit date & time, for example to set  
    // January 21, 2014 at 3am you would call:  
    //rtc.adjust(DateTime(2019, 3, 3, 20, 0, 0));  
  }  
  //rtc.adjust(DateTime(2019, 3, 3, 20, 0, 0));  
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__))); 

  pinMode(LED_BUILTIN, OUTPUT);
  
}

void loop() 
{
  //Módulo RTC - Relógio
  DateTime now = rtc.now();  
  Serial.print(now.year(), DEC);  
  Serial.print('/');  
  Serial.print(now.month(), DEC);  
  Serial.print('/');  
  Serial.print(now.day(), DEC);  
  Serial.print(" (");  
  Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);  
  Serial.print(") ");  
  Serial.print(now.hour(), DEC);  
  Serial.print(':');  
  Serial.print(now.minute(), DEC);  
  Serial.print(':');  
  Serial.print(now.second(), DEC);  
  Serial.println();  
  Serial.print(" since midnight 1/1/1970 = ");  
  Serial.print(now.unixtime());  
  Serial.print("s = ");  
  Serial.print(now.unixtime() / 86400L);  
  Serial.println("d");  
  // calculate a date which is 7 days and 30 seconds into the future  
  DateTime future (now + TimeSpan(7,12,30,6));  
  Serial.print(" now + 7d + 30s: ");  
  Serial.print(future.year(), DEC);  
  Serial.print('/');  
  Serial.print(future.month(), DEC);  
  Serial.print('/');  
  Serial.print(future.day(), DEC);  
  Serial.print(' ');  
  Serial.print(future.hour(), DEC);  
  Serial.print(':');  
  Serial.print(future.minute(), DEC);  
  Serial.print(':');  
  Serial.print(future.second(), DEC);  
  Serial.println();  
  Serial.println();  
  delay(3000);  

  // Piscar LED 
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}

  
 
