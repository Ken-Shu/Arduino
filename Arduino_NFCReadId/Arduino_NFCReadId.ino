#include <SPI.h>
#include <RFID.h>
#define RST_PIN 9
#define SDA_PIN 10
#define BUZEER_PIN 8

RFID rfid (SDA_PIN ,RST_PIN );

/*
 * 白卡 : ad5b6437a5
 * 磁扣 : b39e4c91f0
 */

void setup() {
  Serial.begin(9600);
  delay(2);
  pinMode(BUZEER_PIN,OUTPUT);
  SPI.begin();
  rfid.init();
  Serial.println("Ready");

}

void loop() {
  if(rfid.isCard() && rfid.readCardSerial()){
    tone(BUZEER_PIN , 976 , 200);
    Serial.println("Card found");
    String cardId = "";
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
