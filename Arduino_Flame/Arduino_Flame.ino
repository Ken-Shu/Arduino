const int FLAME_PIN = 11;
const int BUZEER_PIN = 10;
void setup() {
  Serial.begin(9600);
  pinMode(FLAME_PIN , INPUT);
  pinMode(BUZEER_PIN , OUTPUT);
}

void loop() {
  boolean isFlame = digitalRead(FLAME_PIN);
  Serial.print("isFlame : ");
  Serial.println(isFlame);
  if(isFlame == 0){ // 0表示有火
    digitalWrite(BUZEER_PIN , HIGH);
  }else{
    digitalWrite(BUZEER_PIN , LOW);
  }
  delay(200);
  
  
}
