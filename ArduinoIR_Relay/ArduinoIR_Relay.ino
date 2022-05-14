/*
 * IR 接線方式(凸面朝自己)
 * 左:D7
 * 中:GND
 * 右:5V
 * 
 */
#include <IRremote.h>

#define IR_RECV_PIN 7
#define RELAY_PIN 4

//IR 設備宣告
IRrecv irrecv(IR_RECV_PIN);

//IR 解碼資訊
decode_results results;

void setup() {
  Serial.begin(9600);
  delay(2);
  pinMode(RELAY_PIN , OUTPUT);
  Serial.println("Enable IR");
  irrecv.enableIRIn(); //啟動IR 接收
  Serial.println("Enable 接收");

}

void loop() {
  //將IR 所收到的內容進行解碼(&變數記憶體位置)
  if(irrecv.decode(&results)){
    //Serial.println(results.value , HEX); //HEX 16進位 DEC 10進位
    switch(results.value){
      case 0xFFA857: //按下+
        digitalWrite(RELAY_PIN,HIGH);
        break;
      case 0xFFE01F: //按下-
        digitalWrite(RELAY_PIN,LOW);
        break;
    }
    irrecv.resume(); //恢復 IR 狀態 讓IR能繼續接收下一個訊號   
  }
  delay(100);

}
