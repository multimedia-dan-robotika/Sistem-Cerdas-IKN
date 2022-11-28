/*
   Serial Value 1 = AREA
   Serial Value 2 = MOISTURE PERCENT
*/
#include <elapsedMillis.h>
#include <DS3231.h>

#define WLAtas 9
#define WLBawah 8

#define relayBawahIN1 7 // 2
#define relayBawahIN2 6 // 3
#define relayBawahIN3 3 // 6
#define relayBawahIN4 2 // 7
#define relayAtasIN1  4 // 4
#define relayAtasIN2  5 // 5

DS3231 rtc(SDA, SCL);
Time t;
elapsedMillis readSensorMillis;
elapsedMillis areaRelayOutputMillis;
elapsedMillis reservoirRelayOutputMillis;
elapsedMillis RTCMillis;

unsigned long readSensorInterval            = 3000; // 3000
unsigned long areaRelayOutputInterval       = 2000; // 2000
unsigned long reservoirRelayOutputInterval  = 2000; // 2000
unsigned long RTCInterval                   = 10000; // 10000

String value1, value2;
String moist1, moist2, moist3, moist4;
String area1    = "L1";
String area2    = "L2";
String area3    = "L3";
String area4    = "L4";
String message  = "";
//String statusSensorsOn = "1";
//String statusSensorsOff = "2";
//String statusAllSensors = "";

int WLBawahRead, WLAtasRead;
unsigned char data[4] = {};
float distance, distances;
String dataReciver;

const byte onHour   = 00;
const byte onMin    = 00;
const byte offHour  = 00;
const byte offMin   = 00;

const byte onHour2   = 00;
const byte onMin2    = 00;
const byte offHour2  = 00;
const byte offMin2   = 00;

void setup()
{
  Serial2.begin(9600);
  Serial.begin (115200);
  Serial3.begin (9600); // 9600
  rtc.begin();

  pinMode(WLAtas, INPUT);
  pinMode(WLBawah, INPUT);

  pinMode(relayBawahIN1, OUTPUT);
  pinMode(relayBawahIN2, OUTPUT);
  pinMode(relayBawahIN3, OUTPUT);
  pinMode(relayBawahIN4, OUTPUT);
  pinMode(relayAtasIN1, OUTPUT);
  pinMode(relayAtasIN2, OUTPUT);

  //
  //    rtc.setTime(14, 35, 0);
  //    rtc.setDate(18, 11, 2022);
}

void loop()
{
  /* ================= CAUTION ===============
      THIS IS EXPERIMENTAL  FEATURE!, CHECK THIS SCRIPT IF FIND SOME PROBLEM OR ERROR */
  //Serial.println(statusSensorsOn);
  //Serial.print('#');
  //Serial.println(statusSensorsOff);
  //Serial.print('#');



  ultrasonikSensor();
  //  Serial.println("data Receiver :");
  //  dataReciver = Serial3.readString();
  if (Serial3.available())
  {
    while (Serial3.available() > 0)
    {
      value1 = Serial3.readStringUntil ('#');
      value2 = Serial3.readStringUntil ('#');
      sensorMap (value1, value2);
    }

  }

  //  if (readSensorMillis >= readSensorInterval)
  //  {
  //    reservoirRelayOutput();
  //    readSensorMillis = 0;
  //  }

  if (areaRelayOutputMillis >= areaRelayOutputInterval)
  {
    areaRelayOutput (moist1, relayBawahIN1, area1);
    areaRelayOutput (moist2, relayBawahIN2, area2);
    areaRelayOutput (moist3, relayBawahIN3, area3);
    areaRelayOutput (moist4, relayBawahIN4, area4);
    areaRelayOutputMillis = 0;
  }

  //  if (reservoirRelayOutputMillis >= reservoirRelayOutputInterval)
  //  {
  //    reservoirRelayOutput();
  //    reservoirRelayOutputMillis = 0;
  //  }

  //  if (RTCMillis >= RTCInterval)
  //  {
  //
  //    RTCRead (moist1, relayBawahIN1);
  //    RTCRead (moist2, relayBawahIN2);
  //    RTCRead (moist3, relayBawahIN3);
  //    RTCRead (moist4, relayBawahIN4);
  //    RTCMillis = 0;
  //  }

  rtcTesting();
}
void rtcTesting() {
  RTCRead (moist1, relayBawahIN1);
  RTCRead (moist2, relayBawahIN2);
  RTCRead (moist3, relayBawahIN3);
  RTCRead (moist4, relayBawahIN4);
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

void ultrasonikSensor() {
  int tAir,tToren;
  do {
    for (int i = 0; i < 4; i++)
    {
      data[i] = Serial2.read();
    }
  } while (Serial2.read() == 0xff);

  Serial2.flush();

  if (data[0] == 0xff)
  {
    int sum;
    sum = (data[0] + data[1] + data[2]) & 0x00FF;
    if (sum == data[3])
    {
      distance = (data[1] << 8) + data[2];

      if (distance > 3)
      {
        distances = distance / 10; // convert to CM
        tAir = tToren - distances; // rumus 
        if (tAir > 10) {
          digitalWrite(relayAtasIN2, HIGH);
          digitalWrite(relayAtasIN1, LOW);
          Serial.println("Jarak : ");
          Serial.println(distances);
          Serial.println(tAir);
          Serial.println("Penuh");
        }
        else if (tAir =< 180) {
          digitalWrite(relayAtasIN2, LOW);
          digitalWrite(relayAtasIN1, HIGH);
          Serial.println("Jarak : ");
          Serial.println(distances);
                    Serial.println(tAir);
          Serial.println("KOSONG");
        }
      }
      else
      {
        Serial.println("Not Detected!");
      }
    } else Serial.println("ERROR");
  }
  delay(100);

}

void areaRelayOutput (String moistValue, int relayArea, String area)
{
  int moistPercentA = moistValue.toInt();
  Serial.print(area + " = ");
  Serial.println(moistPercentA);

  if (moistPercentA >= 1 && moistPercentA <= 40)
  {
    //Turn ON Designated Area Relay
    digitalWrite(relayArea, LOW); //high
    //    Serial.println(statusSensorsOn);
  }
  else if (moistPercentA >= 41) {
    digitalWrite(relayArea, HIGH); // low

  }
}

//void reservoirRelayOutput ()
//{
//  WLAtasRead    = digitalRead (WLAtas);
//  WLBawahRead   = digitalRead (WLBawah);
//    if (WLBawahRead == 0)
//    {
//      //Turn OFF Pump and Strobe
//      Serial.println("Status : Pompa Nyala");
//      digitalWrite(relayAtasIN2, HIGH);
//      digitalWrite(relayAtasIN1, LOW);
//    }
//    else if (WLAtasRead == 1) {
//      Serial.println("Status : Pompa Mati");
//      digitalWrite(relayAtasIN2, LOW);
//      digitalWrite(relayAtasIN1, HIGH);
//    }
//    else {
//      //Turn ON Pump and Strobe
//      digitalWrite(relayAtasIN1, LOW);
//      Serial.println("Value WLBawah : HIGH");
//      digitalWrite(relayAtasIN2, HIGH);
//    }

//WaterPump
//  if (WLBawahRead == 0 || WLAtasRead == 0) {
//    Serial.println("Status : Proses Pengisian");
//    digitalWrite(relayAtasIN2, LOW);
//    digitalWrite(relayAtasIN1, LOW);
//  } else if (WLBawahRead == 1 || WLAtasRead == 0) {
//    Serial.println("Status : Proses Pengisian1");
//    digitalWrite(relayAtasIN2, LOW);
//    digitalWrite(relayAtasIN1, LOW);
//  } else if (WLAtasRead == 1 || WLBawahRead == 1) {
//    Serial.println("Status : Pengisian Full");
//    digitalWrite(relayAtasIN2, HIGH);
//    digitalWrite(relayAtasIN1, HIGH);
//  }

//}
void RTCRead(String moistValue, int relayArea)
{
  t = rtc.getTime();

  int jam = t.hour;
  int menit =  t.min;
  Serial.println(jam);
  Serial.println(menit);

  int jamPenyiraman1 = t.hour == onHour;
  int menitPenyiraman1 = t.min == onMin;
  int jamPenyiraman2  =t.hour == onHour2;
  int menitPenyiraman2 = t.min == onHour2;

  int moistPercentB = moistValue.toInt(); // use if need soil value
  if (jamPenyiraman1 && menitPenyiraman1) {
    if (moistPercentB == 0) {
      digitalWrite(relayArea, HIGH);
      Serial.println("RTC ON");
      Serial.println("Penyiraman Ke 1");
      //Turn ON Designated Area Relay
      //    Serial.println(statusSensorsOn);
    }

  }
  else if (t.hour == offHour && t.min == offMin)
  {
    //Turn ON Designated Area Relay
    digitalWrite(relayArea, LOW); //high
    Serial.println("RTC OFF");
    Serial.println("Penyiraman Ke 1");
    //    Serial.println(statusSensorsOn);
  }

  if (jamPenyiraman2 && menitPenyiraman2)
  {
   if (moistPercentB == 0) {
      digitalWrite(relayArea, HIGH);
      Serial.println("RTC ON");
      Serial.println("Penyiraman Ke 2 ON");
  
  }
  }
  else if (t.hour == offHour2 && t.min == offMin2) {
    digitalWrite(relayArea, LOW);
    Serial.println("RTC OFF");
    Serial.println("Penyiraman Ke 2 Mati");
  
  }



}
