#define IN4_Bawah 7
#define IN3_Bawah 6
#define IN2_Atas 5
#define IN1_Atas 4
#define IN2_Bawah 3
#define IN1_Bawah  2

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
}
void loop() {
    Serial.println("Message Received: ");
    dataReciver = Serial3.readString();
    Serial.println(dataReciver);
    datatransfer = dataReciver.toInt();
    Serial.println(datatransfer);
    if (datatransfer > 51){
    digitalWrite(IN4_Bawah, LOW);
    Serial.println("LOW");
  } else {
    digitalWrite(IN4_Bawah, HIGH);
    Serial.println("HIGH");
  
  
  } delay(1000);

 
}