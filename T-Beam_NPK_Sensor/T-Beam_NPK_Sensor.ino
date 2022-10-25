/*
  * LORA32 to Soil Moisture Sensor
  * VCC = 3.3V
  * Data = 25
  * GND = GND
*/

/*
  * LORA32 to pH Sensor
  * Data = 4
  * GND = GND
*/

/*
  * LORA32 to MAX485 
  * VCC = 5V
  * GND = GND
  * (Through Logic-Level Converter)
  * DI (HRX CH1) = TX (LTX CH1)
  * DE (HRX CH2) = 32 (LRX CH2)
  * RE (HTX CH2) = 33 (LTX CH2)
  * RO (HTX CH1) = RX (LRX CH1)
*/

/*
  * MAX485 to NPK Sensor
  * VCC = 9 V (Diff)
  * GND = GND
  * A = A
  * B = B
*/

#define soil 25
#define pH 4
#define DE_MAX485 32
#define RE_MAX485 33

//const byte code[]= {0x01, 0x03, 0x00, 0x1e, 0x00, 0x03, 0x65, 0xCD};
const byte nitro[] = {0x01,0x03, 0x00, 0x1e, 0x00, 0x01, 0xe4, 0x0c};
const byte phos[] = {0x01,0x03, 0x00, 0x1f, 0x00, 0x01, 0xb5, 0xcc};
const byte pota[] = {0x01,0x03, 0x00, 0x20, 0x00, 0x01, 0x85, 0xc0};

byte values[11];

int soilRaw, soilPercent;
int phRaw, phValue;

void setup() 
{
  Serial.begin (9600);
  pinMode (soil, INPUT);
  pinMode (pH, INPUT);
  pinMode (DE_MAX485, OUTPUT);
  pinMode (RE_MAX485, OUTPUT);
}

void loop() 
{
  byte nValue, pValue, kValue;
  nValue = nitrogen();
  delay (250);
  pValue = phosphor();
  delay (250);
  kValue = potas();
  delay (250);
}

byte nitrogen()
{
  digitalWrite (DE_MAX485, HIGH);
  digitalWrite (RE_MAX485, HIGH);
  delay (10);
  if (Serial.write (nitro, sizeof (nitro)) == 8);
  {
    digitalWrite (DE_MAX485, LOW);
    digitalWrite (RE_MAX485, LOW);
    for (byte i=0; i<7; i++)
    {
      values[i] = Serial.read();
    }
  }
  return values[4];
}

byte phosphor()
{
  digitalWrite (DE_MAX485, HIGH);
  digitalWrite (RE_MAX485, HIGH);
  delay (10);
  if (Serial.write (phos, sizeof (phos)) == 8);
  {
    digitalWrite (DE_MAX485, LOW);
    digitalWrite (RE_MAX485, LOW);
    for (byte i=0; i<7; i++)
    {
      values[i] = Serial.read();
    }
  }
  return values[4];
}

byte potas()
{
  digitalWrite (DE_MAX485, HIGH);
  digitalWrite (RE_MAX485, HIGH);
  delay (10);
  if (Serial.write (pota, sizeof (pota)) == 8);
  {
    digitalWrite (DE_MAX485, LOW);
    digitalWrite (RE_MAX485, LOW);
    for (byte i=0; i<7; i++)
    {
      values[i] = Serial.read();
    }
  }
  return values[4];
}
