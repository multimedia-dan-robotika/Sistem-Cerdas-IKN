const byte WL1=4;
const byte WL2=5;
int waterLevelBawah, waterLevelAtas;
const byte pump=6;
const byte strobe=7;

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(strobe, OUTPUT);
  pinMode(pump, OUTPUT);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  waterLevelBawah=digitalRead(WL1);
  waterLevelAtas=digitalRead(WL2);

  Serial.println(waterLevelAtas);
//   if (waterLevelAtas == 0)
//  {
//    //lampu & pompa mati
//    digitalWrite(strobe, LOW);
//    digitalWrite(pump, LOW);
//  }
//  
//  else if (waterLevelBawah == 1)
//  {
//    digitalWrite(strobe, HIGH);
//    digitalWrite(pump, HIGH);
//  }   
  if (waterLevelAtas == 1)
  {
    //lampu & pompa mati
    digitalWrite(strobe, LOW);
    digitalWrite(pump, LOW);
  }
  
  else 
  {
    digitalWrite(strobe, HIGH);
    digitalWrite(pump, HIGH);
  }   
}
