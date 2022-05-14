#include <SPI.h>
#include <RFID.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Timer.h>

#define RST_PIN 9
#define SDA_PIN 10
#define BUZEER_PIN 8

Timer t;
LiquidCrystal_I2C lcd(0x27, 16, 2);
RFID rfid (SDA_PIN ,RST_PIN );
String cardId = "";

void setup() {
  Serial.begin(9600);
  delay(2);
  SPI.begin();
  rfid.init();
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  t.every(1000 , getcardid);
  t.every(1000 , lcdprint);
  
  Serial.print("Ready");
}

void loop() {
  t.update();
  delay(10);
}
void lcdprint(){  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Id:");
  lcd.setCursor(3,0);
  lcd.print(cardId);
  delay(2000);
  
}
void getcardid(){
  if(rfid.isCard() && rfid.readCardSerial()){
    tone(BUZEER_PIN , 976 , 200);
    Serial.println("Card found");
    cardId = "";
    for(int i = 0 ;i<5 ; i++){
      cardId += String(rfid.serNum[i],HEX);
    }
    Serial.print("CardId : ");
    Serial.println(cardId);
    Serial.println();
    delay(1000);
  }
  rfid.halt(); // 進入休眠 等待下次的激活
  delay(10);
}
