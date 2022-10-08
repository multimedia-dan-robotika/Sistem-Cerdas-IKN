#include "SPIFFS.h"

#include <SPI.h>
#include <LoRa.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <WiFi.h>
#include <WiFiAP.h>
#include <Hash.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <Arduino_JSON.h>
#include <elapsedMillis.h>

IPAddress local_IP  (192, 168, 4, 22);
IPAddress gateway  (192, 168, 4, 9);
IPAddress subnet    (255, 255, 255, 0);

#define WIFI_SSID ""
#define WIFI_PASSWORD ""
#define HOTSPOT_SSID "Smart Monitor"
#define HOTSPOT_PASSWORD "PPURST"

#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

#define BAND 915E6

#define OLED_SDA 21
#define OLED_SCL 22
#define OLED_RST 16
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

AsyncWebServer server (80);
AsyncEventSource events ("/events");
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);
JSONVar readings;
elapsedMillis requestMillis;
elapsedMillis OLEDMillis;
elapsedMillis serialMillis;

unsigned int requestInterval = 3000;
unsigned int OLEDInterval = 1000;
unsigned int serialInterval = 1500;

int moisturePercent, rssiValue;

unsigned long lastTime = 0;
unsigned long timerDelay = 5000;

void initFS()
{
    if (!SPIFFS.begin())
    {
        Serial.println ("SPIFFS Gagal");    
    }

    Serial.println ("SPIFFS Sukses");
}

String getSensorReadings()
{
    readings ["moisture"] = String (moisturePercent);
    String jsonString = JSON.stringify (readings);
    return jsonString;
}

void setup() 
{
  Serial.begin(9600);
  
  Wire.begin(OLED_SDA, OLED_SCL);  
  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO0);

  pinMode (OLED_RST, OUTPUT);
  digitalWrite (OLED_RST, LOW)
  delay (20);
  digitalWrite (OLED_RST, HIGH);

  // Address 0x3C for 128x32
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  if (!LoRa.begin(BAND))
  {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("LORA Receiver");
  display.display();
  
  if (!WiFi.config(local_IP, gateway, subnet)) 
  {
    Serial.println("STA Failed to configure");
  }
  WiFi.softAP(HOTSPOT_SSID, HOTSPOT_PASSWORD);
  IPAddress IP = WiFi.softAPIP();
  
  initFS();

  server.on ("/", HTTP_GET, [] (AsyncWebServerRequest *request)
  {
    request -> send (SPIFFS, "/index.html", "text/html");
  });

  server.serveStatic ("/", SPIFFS, "/");

  server.on ("/readings", HTTP_GET, [] (AsyncWebServerRequest *request)
  {
    String json = getSensorReadings();
    request -> send (200, "application/json", json);
    json = String();   
  });

  events.onConnect ([] (AsyncEventSourceClient *client)
  {
    client -> send ("Hello", NULL, millis(), 3000);
  });

  server.addHandler (&events);

  server.begin();
    
  delay(1000);

  display.clearDisplay();
  display.setCursor(45, 0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("Soil");
  display.setCursor(20, 15);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("Moisture");
  display.setCursor(30, 60);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("RSSI = ");
  display.display();

  delay (2000);
}

void loop() 
{
  int packetSize = LoRa.parsePacket();
  if (packetSize) 
  {
    while (LoRa.available()) 
    {
      moisturePercent = LoRa.readStringUntil ('#');
      rssiValue = LoRa.rssi();     
    }
  }
  
  if (OLEDMillis >= OLEDInterval)
  {
    display.setCursor(30, 40);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print("     ");
    display.setCursor(30, 40);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.print(moisturePercent);
    display.setCursor(70, 40);
    display.setTextSize(2);
    display.print("%");
    display.setCursor(70, 60);
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.print(rssiValue);
    display.display();
    Serial.println(moisturePercent);
    OLEDMillis = 0;        
  }

  if (serialMillis >= serialInterval)
  {
    Serial.println(moisturePercent);      
    serialMillis = 0;    
  }

  if (requestMillis >= requestInterval)
  {
    events.send ("Ping", NULL, 3000);
    events.send (getSensorReadings().c_str(), "new_readings", 3000);
    requestMillis = 0;    
  }
}
