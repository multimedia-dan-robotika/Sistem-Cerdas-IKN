#define IN4_Bawah 7
#define IN3_Bawah 6
#define IN2_Atas 5
#define IN1_Atas 4
#define IN2_Bawah 3
#define IN1_Bawah  2

// RTC Setup
#include <DS3231.h>
DS3231 rtc(SDA, SCL);

Time t;

const byte onHour = 13;
const byte onMin = 0;
const byte offHour = 13;
const byte offMin = 30;


// Water Level
#define WL1 A0
#define WL2 8
int waterLevelBawah, waterLevelAtas;

String dataReciver;
int datatransfer;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  rtc.begin();
    Serial3.begin(115200);
  pinMode(IN4_Bawah, OUTPUT);
  pinMode(IN3_Bawah, OUTPUT);
  pinMode(IN2_Atas, OUTPUT);
  pinMode(IN1_Atas, OUTPUT);
  pinMode(IN2_Bawah, OUTPUT);
  pinMode(IN1_Bawah, OUTPUT);
  pinMode(8, INPUT);
  pinMode(A0, INPUT);
  digitalWrite(IN1_Bawah, HIGH);
  digitalWrite(IN2_Bawah, HIGH);
  digitalWrite(IN3_Bawah, HIGH);
  digitalWrite(IN4_Bawah, HIGH);

//  rtc.setTime(13, 27, 0);         // Set the time to 12:00:00 (24hr format)
//  rtc.setDate(25, 10, 2022);      // Set the date to January 1st, 2014
//  Note : 1x upload abis itu comment

}
void loop() {
  

 Serial.println("Message Received: ");
  dataReciver = Serial3.readString();
  datatransfer =dataReciver.toInt();
  Serial.println(datatransfer);
  if (datatransfer >=  0 && datatransfer <= 40){
  digitalWrite(IN1_Bawah, LOW);
  Serial.println("Melakukan Penyiraman");
} else {
  digitalWrite(IN1_Bawah, HIGH);
  Serial.println("Tidak Melakukan Penyiraman ");
} 
delay(1000);

/*  Testing Sensor
 * waterlevel(); 
 * rtcSystem(); 
 *  
 */

}

void waterlevel() {
  waterLevelBawah = digitalRead(WL2);
//  waterLevelAtas = analogRead(WL1);

//  Serial.println(waterLevelAtas);
  Serial.println(waterLevelBawah);

  if (waterLevelBawah == 0 )
  {
    //lampu & pompa mati
    digitalWrite(IN2_Atas, HIGH);
    digitalWrite(IN1_Atas, HIGH);
    Serial.println("HIGH");
    delay(500);
  }
  else  {
    digitalWrite(IN2_Atas, LOW);
    digitalWrite(IN1_Atas, LOW);
    Serial.println("LOW");
    delay(500);
  }
}

void rtcSystem(){
  t = rtc.getTime();

  if (t.hour == onHour && t.min == onMin)
  {
    //Menyalakan Sistem
     digitalWrite(IN2_Bawah, HIGH);
  Serial.println("Melakukan Penyiraman");
  }
  else if (t.hour == offHour && t.min == offMin)
  {
    //Mematikan Sistem
     digitalWrite(IN2_Bawah, LOW);
  Serial.println("Tidak Melakukan Penyiraman ");
  }
  Serial.print(t.hour, DEC);
  Serial.print(" hour(s), ");
  Serial.print(t.min, DEC);
  Serial.println(" minute(s)");

  delay(100);
}
