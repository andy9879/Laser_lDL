/*
  Sleep RTC Alarm for Arduino Zero

  Demonstrates the use an alarm to wake up an Arduino zero from Standby mode

  This example code is in the public domain

  http://arduino.cc/en/Tutorial/SleepRTCAlarm

  created by Arturo Guadalupi
  17 Nov 2015
  modified 
  01 Mar 2016
  
  NOTE:
  If you use this sketch with a MKR1000 you will see no output on the serial monitor.
  This happens because the USB clock is stopped so it the USB connection is stopped too.
  **To see again the USB port you have to double tap on the reset button!**
*/

#include <RTCZero.h>
#include <SPI.h>
#include <SD.h>


/* Create an rtc object */
RTCZero rtc;


const int sensor = A0;
/* Change these values to set the current initial time */
const byte seconds = 0;
const byte minutes = 00;
const byte hours = 17;

/* Change these values to set the current initial date */
const byte day = 17;
const byte month = 11;
const byte year = 15;


const int chipSelect = SDCARD_SS_PIN;
 
 byte currentAlarm = 1;

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  pinMode(A0, INPUT);
  
  SD.begin(chipSelect);


  
  rtc.begin();

  rtc.setTime(hours, minutes, seconds);
  rtc.setDate(day, month, year);

  rtc.setAlarmMinutes(1);
  rtc.enableAlarm(rtc.MATCH_MMSS);

  rtc.attachInterrupt(alarmMatch);

  rtc.standbyMode();
}

void loop()
{
  rtc.standbyMode();    // Sleep until next alarm match
}

void alarmMatch()
{
  String dataString = "";//String(rtc.getYear()) + "/" +  String(rtc.getMonth()) + "/" + String(rtc.getDay()) + "_" + String(rtc.getHours()) +":"+ String(rtc.getMinutes()) +":"+ String(rtc.getSeconds) + "|" ;

  for(int i = 0;i<10;i++){
      dataString += String(analogRead(sensor)) + ",";
      delay(1);
      }

  dataString += " ";
  digitalWrite(13, HIGH);
  delay(500000);
  

  for(int i = 0;i<10;i++){
      dataString += String(analogRead(sensor)) + ",";
      delay(1);
      }

    currentAlarm += 1;
    if(currentAlarm >= 60){
      currentAlarm = 0;  
      }
    
    dataString += "|" + String(currentAlarm);

    File dataFile = SD.open("datalog.txt", FILE_WRITE);
    
    dataFile.println(dataString);
    dataFile.close();
    digitalWrite(13, LOW);

    rtc.setAlarmMinutes(currentAlarm);
    rtc.enableAlarm(rtc.MATCH_MMSS);


    

}
