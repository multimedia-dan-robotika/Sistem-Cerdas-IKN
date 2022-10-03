# Sistem-Cerdas-IKN

# Schematic
![Logo](https://github.com/multimedia-dan-robotika/Sistem-Cerdas-IKN/blob/main/skematikUpdate.png)

## Documentation

#### Lora TTGO T-Beam Pin Use to Logic Converter

| PIN Lora | Type     | Pin Logic Converter           |
| :-------- | :------- | :------------------------- |
| `RX` | `Communication Serial` |  `RX`|
| `TX` | `Communication Serial` | `TX` |
| `GND` | `Ground` | `GND` |
| `3.3V` | `VCC` | `LV` |


#### Arduino Mega 2560 Pin Use to Logic Converter
| PIN Lora | Type     | Pin Logic Converter           |
| :-------- | :------- | :------------------------- |
| `RX` | `Communication Serial` |  `TX`|
| `TX` | `Communication Serial` | `RX` |
| `GND` | `Ground` | `GND` |
| `5V` | `VCC` | `HV` |


#### Example Receiver arduino Mega -> Logic Converter <- Lora TTGO

```c++
  void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial3.begin(115200);
}
void loop() {
  Serial.println("Message Received: ");
  Serial.println(Serial3.readString());
```
