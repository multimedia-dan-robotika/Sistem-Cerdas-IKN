#include <SPI.h>
#include <LoRa.h>
// Libraries for OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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

// Humidity
#define humidityPin 25
// int humidityValue;
// int humidityRead;
String humidityString;
// you need to replace this value with Value_2
const int SensorPin = A0;
int soilMoistureValue = 0;
int soilmoisturepercent = 0;

/* LoRa to Nano interface
   VCC      3V3
   GND      GND
   MISO     D12
   MOSI     D11
   SCK      D13
   NSS/CS   D10
   RESET    D9
*/
int x, minX;
char message[]="29M LstWyPt, 345M StPt, rec#89";
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

void setup()
{
  Serial.begin(115200);
  //  pinMode(humidityPin, INPUT_PULLUP);
  pinMode(OLED_RST, OUTPUT);
  pinMode(humidityPin, INPUT);
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
  display.print("LORA Area A");
  display.display();

  Serial.println("LoRa Sender Test");
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
   x = display.width();
  minX = -12 * strlen(message);  // 12 = 6 pixels/character * text size 2
 
}

void loop()
{
  int rssi = LoRa.rssi();
  soilMoistureValue = analogRead(humidityPin); // put Sensor insert into soil
  Serial.println(soilMoistureValue);
  soilmoisturepercent = map(soilMoistureValue,  0, 4095, 100, 0);
  LoRa.beginPacket();
  LoRa.print(soilmoisturepercent);
  LoRa.print('#');
  LoRa.print(rssi);
  LoRa.print('#');
  LoRa.endPacket();

//  oled display
// display.setCursor(0,0); 
//  display.setTextSize(1);
//  display.println("AREA A");
//  display.setCursor(0,20); 
//  display.setTextSize(1);
//  display.setTextColor(WHITE);
//  display.println("Kelembaban : ");
//  display.setCursor(80,20);
//  display.setTextSize(1);
//  display.setTextColor(WHITE);
//  display.println(soilmoisturepercent);
//    
//  display.setCursor(90,20);  //oled display
//  display.setTextSize(1);
//  display.setTextColor(WHITE);
//  display.println(" %");
//  display.setCursor(0,30);
//  display.setTextSize(1);
//  display.println("Tanah : Kering");
//  display.display();
//  display.clearDisplay();

  if (soilmoisturepercent >= 0 && soilmoisturepercent <= 100)
  {
   
    Serial.print(soilmoisturepercent);
    Serial.println("%");
    if (soilmoisturepercent >= 0 && soilmoisturepercent <= 40) {
        display.setCursor(32,0); 
  display.setTextSize(2);
  display.println("AREA C");
//  display.setCursor(0,20); 
//  display.setTextSize(1.1);
//  display.setTextColor(WHITE);
//  display.println("Kelembaban : ");
  display.setCursor(45,25);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println(soilmoisturepercent);
  display.setCursor(65,25);  //oled display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println(" %");
  display.setCursor(x,50);
  display.setTextSize(2);
  display.println("KONDISI TANAH KERING");
   x=x-4; // scroll speed, make more positive to slow down the scroll
   if(x < minX) x= display.width();
  display.display();
  display.clearDisplay();
    }
    else if (soilmoisturepercent >= 40 && soilmoisturepercent <= 50) {
        display.setCursor(32,0); 
  display.setTextSize(2);
  display.println("AREA C");
//  display.setCursor(0,20); 
//  display.setTextSize(1.1);
//  display.setTextColor(WHITE);
//  display.println("Kelembaban : ");
  display.setCursor(45,25);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println(soilmoisturepercent);
  display.setCursor(65,25);  //oled display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println(" %");
  display.setCursor(x,50);
  display.setTextSize(2);
  display.println("KONDISI TANAH NORMAL");
   x=x-4; // scroll speed, make more positive to slow down the scroll
   if(x < minX) x= display.width();
  display.display();
  display.clearDisplay();
    }
    else if (soilmoisturepercent >= 51 && soilmoisturepercent <= 100) {
     display.setCursor(32,0); 
  display.setTextSize(2);
  display.println("AREA C");
//  display.setCursor(0,20); 
//  display.setTextSize(1.1);
//  display.setTextColor(WHITE);
//  display.println("Kelembaban : ");
  display.setCursor(45,25);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println(soilmoisturepercent);
  display.setCursor(65,25);  //oled display
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println(" %");
  display.setCursor(x,50);
  display.setTextSize(2);
  display.println("KONDISI TANAH SEDANG BASAH");
   x=x-4; // scroll speed, make more positive to slow down the scroll
   if(x < minX) x= display.width();
  display.display();
  display.clearDisplay();
    }
  }
}
