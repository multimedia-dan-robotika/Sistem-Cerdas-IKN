#define IN4_Bawah 7
#define IN3_Bawah 6
#define IN2_Atas 5
#define IN1_Atas 4
#define IN2_Bawah 3
#define IN1_Bawah  2
///////////////////////////////////////////

const byte WL1=8;
const byte WL2=9;
int waterLevelBawah, waterLevelAtas;

String dataReciver;
int datatransfer;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
    Serial3.begin(115200);
  pinMode(IN4_Bawah, OUTPUT);
  pinMode(IN3_Bawah, OUTPUT);
  pinMode(IN2_Atas, OUTPUT);
  pinMode(IN1_Atas, OUTPUT);
  pinMode(IN2_Bawah, OUTPUT);
  pinMode(IN1_Bawah, OUTPUT);
/////////////////input water level///////////////
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  

}
void loop() {
//    Serial.println("Message Received: ");
//    dataReciver = Serial3.readString();
//    Serial.println(dataReciver);
//    datatransfer = dataReciver.toInt();
//    Serial.println(datatransfer);
//    if (datatransfer > 51){
//    digitalWrite(IN4_Bawah, LOW);
//    Serial.println("LOW");
//  } else {
//    digitalWrite(IN4_Bawah, HIGH);
//    Serial.println("HIGH");
  //////////////////////////////////water level///////////////

  waterLevelBawah=digitalRead(WL1);
  waterLevelAtas=digitalRead(WL2);
  Serial.println(waterLevelAtas);
   
   if (waterLevelAtas == 1)
  {
    //lampu & pompa mati
    digitalWrite(IN2_Atas, LOW);
    digitalWrite(IN1_Atas, LOW);
  }
  
  else 
  {
    digitalWrite(IN2_Atas, HIGH);
    digitalWrite(IN1_Atas, HIGH);
  }   
  
   delay(1000);

 
}
