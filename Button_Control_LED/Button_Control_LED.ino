const int BUTTON_PIN_7 = 7;
const int LED_PIN_13 = 13;
int on = 0; //開關狀態
void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN_7,INPUT); //設定按鈕的接腳為輸入 ,因為要讀取狀態值
  pinMode(LED_PIN_13 , OUTPUT);
}

void loop() {
  int buttonState = digitalRead(BUTTON_PIN_7);
  //Serial.print("Button : ");
  //Serial.println(buttonState);
  if(buttonState == 0){
    on = !on;
    Serial.print("on : ");
    Serial.println(on);
  }
  runLED();
  delay(200);
}
void runLED(){
  switch(on){
    case 0 :
      digitalWrite(LED_PIN_13,LOW);
    break;
    case 1 :
      digitalWrite(LED_PIN_13,HIGH);
    break;
  }
}
