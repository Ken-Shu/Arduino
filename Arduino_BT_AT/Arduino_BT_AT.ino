#include <SoftwareSerial.h> //引用函式庫
//利用AT指令來管理藍芽配置
//定義BT序列阜
/*
 * HC-05 接線方式
  VCC : 5V
  GND : GND
  TXD : 10
  RXD : 11
  ADDR : 0022:01:0017E3
*/
SoftwareSerial BT(10 , 11); //RX (對應 BT 的 TXD) TX(對應 BT 的 RXD)
char val; //儲存接收到的資料

void setup() {
  Serial.begin(9600);
  delay(2);
  // 進入 BT AT 模式 設定 baund
  // HC-05 設定 38400 HC-06 設定 9600
  BT.begin(38400);
  Serial.println("BT Ready...");
}

void loop() {
  //從主控台傳指令給BT
  if(Serial.available()){
    val = Serial.read(); //接到指令
    BT.print(val);//將指令給BT
  }
  //BT回應資料給主控台
  if(BT.available()){
    val = BT.read(); //讀取BT的回應資料
    Serial.print(val); //將回應資料給主控台
  }
  delay(10);

}
