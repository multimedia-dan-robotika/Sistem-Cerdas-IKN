#define relay1 7

String dataReciver;
int datatransfer;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial3.begin(115200);
  pinMode(relay1, OUTPUT);
}
void loop() {
  Serial.println("Message Received: ");
  dataReciver = Serial3.readString();
  datatransfer = dataReciver.toInt();
  Serial.println(datatransfer);
  if (datatransfer < 120){
  digitalWrite(relay1, HIGH);
  Serial.println("HIGH");
} else {
  digitalWrite(relay1, LOW);
  Serial.println("LOW");
} delay(1000);

}
