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

const byte onHour = 16;
const byte onMin = 0;
const byte offHour = 16;
const byte offMin = 30;


// Water Level
#define WL1 8
#define WL2 9
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
  pinMode(9, INPUT);
}
void loop() {
  

 Serial.println("Message Received: ");
  dataReciver = Serial3.readString();
  datatransfer = dataReciver.toInt();
  Serial.println(datatransfer);
  if (datatransfer >=  0 && datatransfer <= 40){
  digitalWrite(IN1_Bawah, LOW);
  Serial.println("Melakukan Penyiraman");
} else {
  digitalWrite(IN1_Bawah, LOW);
  Serial.println("Tidak Melakukan Penyiraman ");
} delay(1000);

waterlevel();

}

void waterlevel() {
  waterLevelBawah = digitalRead(WL2);
  waterLevelAtas = digitalRead(WL1);

  Serial.println(waterLevelAtas);
  Serial.println(waterLevelBawah);

  if (waterLevelAtas == 1)
  {
    //lampu & pompa mati
    digitalWrite(IN2_Atas, HIGH);
    digitalWrite(IN1_Atas, HIGH);
    Serial.println("HIGH");
    delay(1000);
  }
  else {
    digitalWrite(IN2_Atas, LOW);
    digitalWrite(IN1_Atas, LOW);
    Serial.println("HIGH");
    delay(1000);
  }
}

void rtcSystem(){
  t = rtc.getTime();

  if (t.hour == onHour && t.min == onMin)
  {
    //Menyalakan Sistem
     digitalWrite(IN1_Bawah, LOW);
  Serial.println("Melakukan Penyiraman");
  }
  else if (t.hour == offHour && t.min == offMin)
  {
    //Mematikan Sistem
     digitalWrite(IN1_Bawah, LOW);
  Serial.println("Tidak Melakukan Penyiraman ");
  }
  Serial.print(t.hour, DEC);
  Serial.print(" hour(s), ");
  Serial.print(t.min, DEC);
  Serial.println(" minute(s)");

  delay(1000);
}