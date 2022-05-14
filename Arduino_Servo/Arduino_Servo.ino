/*
 * Servo 接線
 * GND : 棕色
 * 5V : 紅色
 * D6 : 橘色 (訊號線)
 */
#include <Servo.h>

#define SERVO_PIN 6

//建立Servo 物件
Servo myServo;
int initDegree = 90; //初始角度
int maxDegree = 0; //最大角度

void setup() {
  Serial.begin(9600);
  delay(2);
  myServo.attach(SERVO_PIN); //設定 Servo 訊號腳位
  myServo.write(initDegree); //設定初始角度位置
  

}

void loop() {
  //啟動柵欄
  for(int i = initDegree; i>=maxDegree ; i-=5 ){
    myServo.write(i);
    delay(100);
  }
  delay(5000); //柵欄全開
  //關閉柵欄
  for(int i = maxDegree; i<=initDegree ; i+=5 ){
    myServo.write(i);
    delay(100);
  }
  delay(5000);//柵欄全部放下
}
