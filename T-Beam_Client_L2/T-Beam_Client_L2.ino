#include <SPI.h>
#include <LoRa.h>

#define BAND  915E6
#define SCK   5
#define MISO  19
#define MOSI  27
#define SS    18
#define RST   14
#define DIO0  26

String area = "L2";
String receivedArea, moist, pH, nitro, phos, kal;

void setup()
{
  Serial.begin(9600);
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(BAND))
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}
void loop() 
{
  int packetSize = LoRa.parsePacket();
  if (packetSize) 
  {
    while (LoRa.available()) 
    {
      receivedArea = LoRa.readStringUntil ('#');
      if (area == receivedArea)
      {
        onResponse(receivedArea, moist, pH, nitro, phos, kal);
      }
    }
  }
}

void onResponse(String field, String sensor1, String sensor2, String sensor3, String sensor4, String sensor5)
{
  LoRa.beginPacket ();
  LoRa.print (field);
  LoRa.print ("#");
  LoRa.print (sensor1);
  LoRa.print ("#");
  LoRa.print (sensor2);
  LoRa.print ("#");
  LoRa.print (sensor3);
  LoRa.print ("#");
  LoRa.print (sensor4);
  LoRa.print ("#");
  LoRa.print (sensor5);
  LoRa.print ("#");
  LoRa.endPacket ();
}
