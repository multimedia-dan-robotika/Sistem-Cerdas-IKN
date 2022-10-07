# Sistem-Cerdas-IKN

# Schematic
![Logo](https://github.com/multimedia-dan-robotika/Sistem-Cerdas-IKN/blob/main/updateskematik.png)

## Documentation

#### Lora TTGO T-Beam Pin Use to Logic Converter

| PIN Lora | Type     | Pin Logic Converter           | Pin Mega| 
| :-------- | :------- | :------------------------- |  :------- |
| `RX` | `Communication Serial` ||  `RX`|`TX` |
| `TX` | `Communication Serial` || `TX` |`RX`|
| `GND` | `Ground` | `GND` ||`GND`|
| `3.3V` | `VCC` | `LV` | `HV`|`5v`|


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
