#include "SPIFFS.h"

#include <SPI.h>
#include <LoRa.h>
// Libraries for OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include <WiFiAP.h>
//#include <Hash.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Arduino_JSON.h>
#include <elapsedMillis.h>
IPAddress local_IP(192, 168, 4, 22);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0);

const char *ssid = "Smart Monitor";
const char *password = "PPURSTUG";

// define the pins used by the LoRa transceiver module
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

// 433E6 for Asia
// 866E6 for Europe
// 915E6 for North America
#define BAND 915E6

// OLED pins
#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_RST 16
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

/* LoRa to Nano interface
   VCC      3V3
   GND      GND
   MISO     D12
   MOSI     D11
   SCK      D13
   NSS/CS   D10
   RESET    D9
*/

AsyncWebServer server(80);
AsyncEventSource events("/events");
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

// variabel global
String humaditi;
String rssiRange;
JSONVar readings;
elapsedMillis requestMillis;
elapsedMillis OLEDMillis;
elapsedMillis serialMillis;

unsigned int requestInterval = 3000;
unsigned int OLEDInterval = 1000;
unsigned int serialInterval = 1500;

int rssiValue;
String moiseRecive;
int moisturePercent;
unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

void initFS()
{
  if (!SPIFFS.begin())
  {
    Serial.println("SPIFFS Gagal");
  }

  Serial.println("SPIFFS Sukses");
}

String getSensorReadings()
{
  readings["moisture"] = String(moisturePercent);
// readings["moisture_B"] = String(variableSensors); 
// readings["moisture_C"] = String(variableSensors); 
// readings["moisture_D"] = String(variableSensors); 
  String jsonString = JSON.stringify(readings);
  return jsonString;
}
void setup()
{
  Serial.begin(115200);
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);

  // initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false))
  { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("LORA Starting... ");
  display.display();

  // SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  // setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(BAND))
  {
    Serial.println("Starting LoRa failed!");
    while (1)
      ;
  }
  Serial.println("LoRa Initializing OK!");
  if (!WiFi.config(local_IP, gateway, subnet))
  {
    Serial.println("STA Failed to configure");
  }
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();

  Serial.println(IP);
  initFS();

  server.on("/", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    request->send(SPIFFS, "/index.html", "text/html");
  });

  server.serveStatic("/", SPIFFS, "/");

  server.on("/readings", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    String json = getSensorReadings();
    request -> send (200, "application/json", json);
    json = String();
  });

  events.onConnect([](AsyncEventSourceClient * client)
  {
    client->send("Request -> ", NULL, millis(), 10000);
  });

  server.addHandler(&events);

  server.begin();
}


void loop()
{

 display.setCursor(0, 0);
display.setTextSize(1);
display.println("Lora Server");
 display.setCursor(0, 10);
display.setTextSize(1);
display.println("IP : 192.168.4.1");
   
  int packetSize = LoRa.parsePacket();
  if (packetSize)
  {

    // read packet
    while (LoRa.available())
    {
      //      LoRaData = LoRa.readString();
      moiseRecive = LoRa.readStringUntil('#');
      rssiRange = LoRa.readStringUntil('#');
    }
    moisturePercent = moiseRecive.toInt();
  }
  if (OLEDMillis >= OLEDInterval)
  {

    area_A();
   

    //    end millis
    OLEDMillis = 0;
        display.clearDisplay();
  }

  if (serialMillis >= serialInterval)
  {
//    Serial.println(moisturePercent);
    serialMillis = 0;
  }

  if (requestMillis >= requestInterval)
  {
    events.send("Success", NULL, 3000);
    events.send(getSensorReadings().c_str(), "new_readings", 3000);
    requestMillis = 0;
  }
}


void area_A() {
  if (moisturePercent >= 0 && moisturePercent <= 100)
  {
  Serial.println(moisturePercent);

    if (moisturePercent >= 0 && moisturePercent <= 40) {
      display.setCursor(0, 20);
      display.setTextSize(1);
display.println("Lahan 1 : ");
      display.setCursor(50, 20);
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.println("Kering");


      display.display();
      display.clearDisplay();
    }
    else if (moisturePercent >= 40 && moisturePercent <= 50) {
      display.setCursor(0, 20);
      display.setTextSize(1);
display.println("Lahan 1 : ");
      display.setCursor(50, 20);
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.println("Normal");


      display.display();
      display.clearDisplay();
    }
    else if (moisturePercent >= 51 && moisturePercent <= 100) {
      display.setCursor(0, 20);
      display.setTextSize(1);
      display.println("Lahan 1 : ");
      display.setCursor(50, 20);
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.println("Basah");


      display.display();
      display.clearDisplay();
    }
  }
}

void area_B() {
  if (moisturePercent >= 0 && moisturePercent <= 100)
  {

    Serial.print(moisturePercent);
    Serial.println("%");
    if (moisturePercent >= 0 && moisturePercent <= 40) {
      display.setCursor(0, 30);
      display.setTextSize(1);
      display.println("Area B : ");
      display.setCursor(50, 30);
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.println("Kering");


      display.display();
      display.clearDisplay();
    }
    else if (moisturePercent >= 40 && moisturePercent <= 50) {
      display.setCursor(0, 30);
      display.setTextSize(1);
      display.println("Area B : ");
      display.setCursor(50, 30);
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.println("Normal");


      display.display();
      display.clearDisplay();
    }
    else if (moisturePercent >= 51 && moisturePercent <= 100) {
      display.setCursor(0, 30);
      display.setTextSize(1);
      display.println("Area B : ");
      display.setCursor(50, 30);
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.println("Basah");


      display.display();
      display.clearDisplay();
    }
  }
}
