#include <SPI.h>
#include <LoRa.h>

String data ;
 
void setup() 
{    
    Serial.begin(115200);
 
    if (!LoRa.begin(915E6)) 
    {
        Serial.println("Starting LoRa failed!");
        while (1);
    }
}
 
void loop() 
{
//    Humidity1 = String(Humidity) ;

    Serial.println("Sending packet: ");
    
    LoRa.beginPacket();
    LoRa.print("Lora 3 ");
    LoRa.print("#");
    LoRa.endPacket();
    
//    Serial Monitor
    Serial.print("Lora 3 ");
//    Serial.print(Humidity1);
//    Serial.println("%");

    delay (3000);
}
