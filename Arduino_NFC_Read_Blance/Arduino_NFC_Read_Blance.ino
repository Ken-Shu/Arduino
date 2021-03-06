//讀取卡片餘額
#include <SPI.h>
#include <RFID.h>
#include <Timer.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>


#define SERVO_PIN 6
#define RST_PIN 9
#define SDA_PIN 10
#define BUZEER_PIN 8

Timer t;
LiquidCrystal_I2C lcd(0x27, 16, 2); // 0x27 or 0x3F
RFID rfid (SDA_PIN, RST_PIN);
Servo myServo;

// 驗證資料(block id: 11)
unsigned char keyA[16] {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xff, 0x07, 0x80, 0x69, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
// 寫入資料 $100 (block id: 9)
unsigned char writeData[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100};

int data_blockId = 9;
int key_blockId = 11;
String cardId = "";


void setup() {
  Serial.begin(9600);
  delay(2);
  SPI.begin();
  rfid.init();
  Serial.println("Ready");
}

void loop() {
  //讀卡
  if (rfid.isCard() && rfid.readCardSerial()) {
    tone(BUZEER_PIN, 976, 200)  ;
    Serial.println("Card found");
    cardId = "";
    for (int i = 0; i < 5; i++) {
      cardId += String(rfid.serNum[i], HEX);
    }
    Serial.print("CardId: ");
    Serial.println(cardId);
    //回傳卡片內容
    int card_size = rfid.SelectTag(rfid.serNum);
    Serial.print("CardSize: ");
    Serial.print(card_size);
    Serial.println("K bits");
    Serial.println();
  }
   //讀取餘額 100 --------------------------------------------------
    //授權驗證 若 status = 0 表示 驗證通過 status = 2 表示 keyA 錯誤
   unsigned char status = rfid.auth(PICC_AUTHENT1A, key_blockId, keyA, rfid.serNum);
  if (status == MI_OK) {
    Serial.println("Auth pass");
    // 讀取餘額
    unsigned char readData[16];
    status = rfid.read(data_blockId, readData); //將資料讀取到 readData 陣列
    if (status == MI_OK) {
      int balance = readData[15]; // 十六進位
      Serial.print("Read ok: $");
      Serial.println(balance , DEC); // DEC 轉成十進位印出
    } else {
      Serial.println("Read error");
    }
    Serial.println("-------------------------------");
  }
  rfid.halt(); // 進入休眠
  delay(500);
}
