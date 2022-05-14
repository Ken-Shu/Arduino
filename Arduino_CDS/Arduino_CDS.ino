//#define CDS_PIN A0; // const int CDS_PIN = 0;
const int CDS_PIN = 0;
const int LED_PIN = 11;
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN,OUTPUT);
}

void loop() {
  int value = analogRead(CDS_PIN);
  Serial.println(value);
  if(value < 300){
    digitalWrite(LED_PIN , 255);
  }else if(value<600){
    digitalWrite(LED_PIN , 50);
  }else{
    digitalWrite(LED_PIN , 0);
  }
  delay(200);

}
