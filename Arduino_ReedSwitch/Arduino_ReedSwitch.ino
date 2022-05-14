#define REEDSWITCH_PIN 7
#define BUZZER_PIN 8

void setup() {
  Serial.begin(9600);
  delay(2);
  pinMode(REEDSWITCH_PIN , INPUT_PULLUP);

}

void loop() {
  int sensorValue = digitalRead
  (REEDSWITCH_PIN);
  Serial.println(sensorValue);
  if(sensorValue == 0){
    tone(BUZZER_PIN , 1000,100);
  }
  delay(500);
}
