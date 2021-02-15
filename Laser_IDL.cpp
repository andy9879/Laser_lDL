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
 
 byte currentAlarm = 10;

 int Rpin = 10;

int laser = 13;
void setup()
{
  digitalWrite(Rpin,HIGH);
  pinMode(Rpin,OUTPUT);
  
  pinMode(laser, OUTPUT);
  digitalWrite(13, LOW);

  pinMode(A0, INPUT);
  
  SD.begin(chipSelect);








  String dataString = "";//String(rtc.getYear()) + "/" +  String(rtc.getMonth()) + "/" + String(rtc.getDay()) + "_" + String(rtc.getHours()) +":"+ String(rtc.getMinutes()) +":"+ String(rtc.getSeconds) + "|";

  for(int i = 0;i<10;i++){
      dataString += String(analogRead(sensor)) + ",";
      delay(10);
      }

  dataString += " ";
  digitalWrite(laser, HIGH);
  delay(3000);

 dataString += "|";

  for(int i = 0;i<10;i++){
      dataString += String(analogRead(sensor)) + ",";
      delay(10);
      }

  File dataFile = SD.open("datalog.txt", FILE_WRITE);
  
  rtc.begin();

  rtc.setTime(hours, minutes, seconds);
  rtc.setDate(day, month, year);

  rtc.setAlarmMinutes(20);
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
  digitalWrite(Rpin,LOW);
}
