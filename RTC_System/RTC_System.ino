// Arduino Mega:
// ----------------------
// DS3231:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA pin
//          SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL pin

#include <DS3231.h>

DS3231 rtc(SDA, SCL);

Time t;

const byte onHour = 16;
const byte onMin = 0;
const byte offHour = 16;
const byte offMin = 30;

void setup() 
{
  Serial.begin(115200);

  rtc.begin();

  //The following lines can be uncommented to set the date and time
  //rtc.setDOW(FRIDAY);             // Set Day-of-Week to SUNDAY
  //rtc.setTime(12, 31, 0);         // Set the time to 12:00:00 (24hr format)
  //rtc.setDate(21, 10, 2022);      // Set the date to January 1st, 2014
}

void loop() 
{
  t = rtc.getTime();

  if (t.hour == onHour && t.min == onMin) 
  {
    //Menyalakan Sistem 
  } 
  else if (t.hour == offHour && t.min == offMin) 
  {
    //Mematikan Sistem
  }
  
  Serial.print(t.hour, DEC);
  Serial.print(" hour(s), ");
  Serial.print(t.min, DEC);
  Serial.println(" minute(s)");

  delay(1000);
}