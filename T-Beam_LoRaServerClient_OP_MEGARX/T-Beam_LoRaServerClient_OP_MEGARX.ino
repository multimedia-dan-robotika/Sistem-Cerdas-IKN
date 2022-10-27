/*
   Serial Value 1 = AREA
   Serial Value 2 = MOISTURE PERCENT
*/
#include <elapsedMillis.h>
#include <DS3231.h>

#define WLAtas A0
#define WLBawah 8

#define relayBawahIN1 2
#define relayBawahIN2 3
#define relayBawahIN3 4
#define relayBawahIN4 5
#define relayAtasIN1  10
#define relayAtasIN2  11

DS3231 rtc(SDA, SCL);
Time t;
elapsedMillis readSensorMillis;
elapsedMillis areaRelayOutputMillis;
elapsedMillis reservoirRelayOutputMillis;
elapsedMillis RTCMillis;

unsigned long readSensorInterval            = 3000;
unsigned long areaRelayOutputInterval       = 2000;
unsigned long reservoirRelayOutputInterval  = 2000;
unsigned long RTCInterval                   = 10000;

String value1, value2;
String moist1, moist2, moist3, moist4;
String area1    = "L1";
String area2    = "L2";
String area3    = "L3";
String area4    = "L4";
String message  = "";

int WLBawahRead, WLAtasRead;

const byte onHour   = 13;
const byte onMin    = 0;
const byte offHour  = 13;
const byte offMin   = 30;

void setup()
{
  Serial.begin (115200);
  Serial3.begin (9600);
  rtc.begin();

  pinMode(WLAtas, INPUT);
  pinMode(WLBawah, INPUT);

  pinMode(relayBawahIN1, OUTPUT);
  pinMode(relayBawahIN2, OUTPUT);
  pinMode(relayBawahIN3, OUTPUT);
  pinMode(relayBawahIN4, OUTPUT);
  pinMode(relayAtasIN1, OUTPUT);
  pinMode(relayAtasIN2, OUTPUT);

  digitalWrite (relayAtasIN1, HIGH);
  digitalWrite (relayAtasIN2, HIGH);

  //rtc.setTime(13, 27, 0);
  //rtc.setDate(25, 10, 2022);
}

void loop()
{
  if (Serial3.available())
  {
    while (Serial3.available() > 0)
    {
      value1 = Serial3.readStringUntil ('#');
      value2 = Serial3.readStringUntil ('#');
      sensorMap (value1, value2);
    }
  }

  if (readSensorMillis >= readSensorInterval)
  {
    waterLevelRead();
    readSensorMillis = 0;
  }

  if (areaRelayOutputMillis >= areaRelayOutputInterval)
  {
    areaRelayOutput (moist1, relayBawahIN1);
    areaRelayOutput (moist2, relayBawahIN2);
    areaRelayOutput (moist3, relayBawahIN3);
    areaRelayOutput (moist4, relayBawahIN4);
    areaRelayOutputMillis = 0;
  }

  if (reservoirRelayOutputMillis >= reservoirRelayOutputInterval)
  {
    reservoirRelayOutput();
    reservoirRelayOutputMillis = 0;
  }

  if (RTCMillis >= RTCInterval)
  {
    RTCRead (moist1, relayBawahIN1);
    RTCRead (moist2, relayBawahIN2);
    RTCRead (moist3, relayBawahIN3);
    RTCRead (moist4, relayBawahIN4);
    RTCMillis = 0;
  }
}

void sensorMap (String area, String sensor)
{
  if (area == area1)
  {
    moist1 = sensor;
  }
  else if (area == area2)
  {
    moist2 = sensor;
  }
  else if (area == area3)
  {
    moist3 = sensor;
  }
  else if (area == area4)
  {
    moist4 = sensor;
  }
}

void waterLevelRead()
{
  WLAtasRead    = analogRead (WLAtas);
  WLBawahRead   = digitalRead (WLBawah);
}

void areaRelayOutput (String moistValue, int relayArea)
{
  int moistPercentA = moistValue.toInt();
  if (moistPercentA >= 0 && moistPercentA <= 100)
  {
    if (moistPercentA >= 0 && moistPercentA <= 40)
    {
      //Turn ON Designated Area Relay
      digitalWrite(relayArea, HIGH);
    }
    else
    {
      //Turn OFF Designated Area Relay
      digitalWrite(relayArea, LOW);
    }
  }
}

void reservoirRelayOutput ()
{
  if (WLBawahRead == 1)
  {
    //Turn OFF Pump and Strobe
    digitalWrite(relayAtasIN1, HIGH);
    digitalWrite(relayAtasIN2, HIGH);
  }
  else
  {
    //Turn ON Pump and Strobe
    digitalWrite(relayAtasIN1, LOW);
    digitalWrite(relayAtasIN2, LOW);
  }
}

void RTCRead(String moistValue, int relayArea)
{
  t = rtc.getTime();
  int moistPercentB = moistValue.toInt();

  if (moistPercentB >= 0 && moistPercentB <= 40)
  {
    if (t.hour == onHour && t.min == onMin)
    {
      digitalWrite(relayArea, HIGH);
    }
    else if (t.hour == offHour && t.min == offMin)
    {
      digitalWrite(relayArea, LOW);
    }
  }
  else
  {
    digitalWrite(relayArea, LOW);
  }
}
