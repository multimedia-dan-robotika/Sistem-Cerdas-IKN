/*
 * Serial Value 1 = AREA
 * Serial Value 2 = MOISTURE PERCENT
*/

String value1, value2;
String moist1, moist2, moist3, moist4;
String area1 = "L1";
String area2 = "L2";
String area3 = "L3";
String area4 = "L4";
String message = "";

void setup() 
{
  Serial3.begin (9600);
}

void loop() 
{
  if (Serial3.available())
  {
    while (Serial3.available() > 0)
    {
      value1 = Serial3.readStringUntil ('#');
      value2 = Serial3.readStringUntil ('#');
      sensorMap (value1, value2);
    }
  }
}

void sensorMap (String area, String sensor)
{
  if (area == area1)
  {
    moist1 = sensor;
  }
  else if (area == area2)
  {
    moist2 = sensor;
  }
  else if (area == area3)
  {
    moist3 = sensor;
  }
  else if (area == area4)
  {
    moist4 = sensor;
  }
}
