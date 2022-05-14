boolean po = 0;
byte l = !po;
byte o = po;

byte seven_seg_digits [10][7] = {
  { l, l, l, l, l, l, o }, // = 0
  { o, l, l, o, o, o, o }, // = 1
  { l, l, o, l, l, o, l }, // = 2
  { l, l, l, l, o, o, l }, // = 3
  { o, l, l, o, o, l, l }, // = 4
  { l, o, l, l, o, l, l }, // = 5
  { l, o, l, l, l, l, l }, // = 6
  { l, l, l, o, o, o, o }, // = 7
  { l, l, l, l, l, l, l }, // = 8
  { l, l, l, o, o, l, l }  // = 9
};
//燈
#define LED_PIN 13

//蜂鳴器(Buzeer)
#define BUZEER_PIN 9

#include <IRremote.h>
#define IR_RECV_PIN 10
//IR 設備宣告
IRrecv irrecv(IR_RECV_PIN);
//IR 解碼資訊
decode_results results;

void setup() {
  Serial.begin(9600);
  delay(2);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(LED_PIN,OUTPUT);
  pinMode(BUZEER_PIN,OUTPUT); //蜂鳴器
  Serial.println("Enable IR");
  irrecv.enableIRIn(); //啟動IR 接收
  Serial.println("Enable 接收");
 delay(2000);
}

void loop() {
  byte pin = 2;
  digitalWrite(LED_PIN ,LOW);
  if(irrecv.decode(&results)){
    Serial.println(results.value , HEX);
    switch(results.value){
    case 0xFF6897: // 0 
      sevenSegWrite(0);
      delay(1000);
    break;
    case 0xFF30CF: // 1
      sevenSegWrite(1);
      delay(1000);
    break;
    case 0xFF18E7: // 2
      sevenSegWrite(2);
      delay(1000);
    break;
    case 0xFF7A85: // 3
      sevenSegWrite(3);
      delay(1000);
    break;
    case 0xFF10EF: // 4
    sevenSegWrite(4);
      delay(1000);
    break;
    case 0xFF38C7: // 5
    sevenSegWrite(5);
      delay(1000);
    break;
    case 0xFF5AA5: // 6
    sevenSegWrite(6);
      delay(1000);
    break;
    case 0xFF42BD: // 7
    sevenSegWrite(7);
      delay(1000);
    break;
   case 0xFF4AB5: // 8
    sevenSegWrite(8);
      delay(1000);
    break;
    case 0xFF52AD: // 9
    sevenSegWrite(9);
      delay(1000);
    break;
  }
 }
  irrecv.resume(); //恢復 IR 狀態 讓IR能繼續接收下一個訊號   
  digitalWrite(LED_PIN,HIGH);
  delay(1000);
}

void sevenSegWrite(byte i){
  
  byte pin = 2;
  for(byte seg = 0 ; seg<7 ; seg++){
    digitalWrite(pin ,seven_seg_digits[i][seg] );
    ++pin;
  }
  sound(200);
  delay(500);  
}
void sound(int delaytime){
  digitalWrite(BUZEER_PIN,HIGH);
  delay(delaytime);
  digitalWrite(BUZEER_PIN,LOW);
}
