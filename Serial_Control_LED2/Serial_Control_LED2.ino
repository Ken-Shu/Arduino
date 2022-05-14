//輸入 1 13開 12關
//    2 13關 12開
//    3 全開
//    4 全關
//    5 交替閃爍 (200ms)
const int LED_PIN_13 = 13;
const int LED_PIN_12 = 12;
int n = 0;
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN_13,OUTPUT);
  pinMode(LED_PIN_12,OUTPUT);
}

void loop() {
  if(Serial.available()>0){
    n = Serial.read();
    Serial.print("arduino : ");
    Serial.println(n);   
  }
  runLED();
  delay(10);
}

  void runLED(){
    switch (n) {
      case 49:
       digitalWrite(LED_PIN_13 , HIGH);
       digitalWrite(LED_PIN_12 , LOW);
        break;
      case 50:
       digitalWrite(LED_PIN_13 , LOW);
       digitalWrite(LED_PIN_12 , HIGH);
        break;
      case 51:
       digitalWrite(LED_PIN_13 , HIGH);
       digitalWrite(LED_PIN_12 , HIGH);
        break;
      case 52:
       digitalWrite(LED_PIN_13 , LOW);
       digitalWrite(LED_PIN_12 , LOW);
      break;
      case 53:
        int value = !digitalRead(LED_PIN_13);
        digitalWrite(LED_PIN_13,value);
        digitalWrite(LED_PIN_12,!value);
        delay(200);
      break;
//          digitalWrite(LED_PIN_13 , LOW);
//          digitalWrite(LED_PIN_12 , HIGH);
//          delay(200);
//          digitalWrite(LED_PIN_13 , HIGH);
//          digitalWrite(LED_PIN_12 , LOW);
//          delay(200);          
    }
  
}
