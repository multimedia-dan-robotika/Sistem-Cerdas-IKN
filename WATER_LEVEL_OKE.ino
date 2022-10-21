const byte WL1=8;
const byte WL2=9;
int waterLevelBawah, waterLevelAtas;
#define strobe 5
#define pump 4  


void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(strobe, OUTPUT);
  pinMode(pump , OUTPUT);
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
