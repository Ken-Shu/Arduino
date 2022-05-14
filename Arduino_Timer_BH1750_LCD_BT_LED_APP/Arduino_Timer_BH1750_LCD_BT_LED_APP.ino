//Arduino 模擬多執行緒
//BH1750 , LCD , BT_APP , LED
#include <Timer.h>
#include <BH1750.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h> //引用函式庫

//宣告 Timer 物件
Timer t;
LiquidCrystal_I2C lcd(0x27, 16, 2);
BH1750 lightMeter;
SoftwareSerial BT(10 , 11);

float lux = 0;
const int LED_PIN_13 = 13;
char val;

void setup() {
  Serial.begin(9600);
  delay(2);
  Wire.begin();
  BT.begin(9600);
  lightMeter.begin();
  
  pinMode(LED_PIN_13 , OUTPUT);
  lcd.begin();
  lcd.backlight();  
  //清空LCD
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("lux:");
  
  t.every(500 , bt1750);
  t.every(1000 , lcdprint);
  t.every(100 , bt_app_led);

  Serial.println("Ready...");
}

void loop() {
  //執行所註冊的工作內容
  t.update();
  delay(10);
}

void bt1750() {
  lux = lightMeter.readLightLevel();
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");
}
void lcdprint(){
  lcd.setCursor(4,0);
  lcd.print("              ");//14個空格
  lcd.setCursor(0,1);
  lcd.print(lux);
}
void bt_app_led(){
  //從主控台傳指令給BT
  if(Serial.available()){
    val = Serial.read(); //接到指令
    Serial.print("Serial : ");
    BT.print(val);//將指令給BT
      
  }
  //BT回應資料給主控台
  if(BT.available()){
    val = BT.read(); //讀取BT的回應資料
    Serial.print("BT : ");
    Serial.println(val); //將回應資料給主控台
    if(val == '1'){
      digitalWrite(LED_PIN_13,HIGH);
    }    
     if(val == '0'){
      digitalWrite(LED_PIN_13,LOW);
    }
  }
  delay(10);

}
