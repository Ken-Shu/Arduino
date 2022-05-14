//控制LED燈
//輸入　0 LED_PIN_8 關燈
//輸入　1 LED_PIN_8 開燈
const int LED_PIN_13 = 13;
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN_13,OUTPUT);
}

void loop() {
  if(Serial.available()>0){
    int n = Serial.read();
    Serial.print("arduino: " );
    Serial.println(n);
    switch(n){
      case 48:
      digitalWrite(LED_PIN_13 , LOW);
      break;
      case 49:
      digitalWrite(LED_PIN_13 , HIGH);
      break;
    }
  }
}
