#include <Wire.h>

#include <ThreeWire.h>
#include <RtcDS1302.h>

//LCD 面板
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


// DS1302接線指示: 可依需求修改
// DS1302 CLK/SCLK --> 13
// DS1302 DAT/IO --> 12
// DS1302 RST/CE --> 11
// DS1302 VCC --> 3.3v - 5v
// DS1302 GND --> GND

ThreeWire myWire(12, 13, 11); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);
//LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup () {
  Serial.begin(9600);

  Serial.print("compiled: ");
  Serial.print(__DATE__);
  Serial.println(__TIME__);

  lcd.begin();
  lcd.backlight();
  lcd.clear();
  
  Rtc.Begin();

  //__DATE__，__TIME__，是程式碼編譯時的日期和時間
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  printDateTime(compiled);
  Serial.println();

  //判斷DS1302是否接好
  if (!Rtc.IsDateTimeValid()) {
    // Common Causes:
    //    1) first time you ran and the device wasn't running yet
    //    2) the battery on the device is low or even missing

    Serial.println("RTC lost confidence in the DateTime!");
    Rtc.SetDateTime(compiled);
  }

  if (Rtc.GetIsWriteProtected()) {
    Serial.println("RTC was write protected, enabling writing now");
    Rtc.SetIsWriteProtected(false);
  }

  if (!Rtc.GetIsRunning()) {
    Serial.println("RTC was not actively running, starting now");
    Rtc.SetIsRunning(true);
  }

  //判斷DS1302上紀綠的時間和編譯時的時間，哪個比較新
  //如果編譯時間比較新，就進行設定，把DS1302上的時間改成新的時間
  //now：DS1302上紀綠的時間，compiled：編譯時的時間
  RtcDateTime now = Rtc.GetDateTime();
  if (now < compiled) {
    Serial.println("RTC is older than compile time!  (Updating DateTime)");
    //編譯時間比較新，把DS1302上的時間改成編譯的時間
    Rtc.SetDateTime(compiled);
  }
  else if (now > compiled) {
    Serial.println("RTC is newer than compile time. (this is expected)");
  }
  else if (now == compiled) {
    Serial.println("RTC is the same as compile time! (not expected but all is fine)");
  }

}

void loop () {
  RtcDateTime now = Rtc.GetDateTime();

  printDateTime(now);
  Serial.println();

  //判斷DS1302是否正常，如果不正常，一般是線沒接好，或是電池沒電了
  if (!now.IsValid()) {
    Serial.println("RTC lost confidence in the DateTime!");
  }

  delay(1000); // 1秒更新一次
}

#define countof(a) (sizeof(a) / sizeof(a[0]))

//顯示完整年月日時間的副程式
void printDateTime(const RtcDateTime& dt) {
  char datestring[22];

  // %u格式：以無符號十進制形式輸出整數。
  snprintf_P(datestring,
             countof(datestring),
             PSTR("%04u/%02u/%02u %02u:%02u:%02u %u"),
             dt.Year(),
             dt.Month(),
             dt.Day(),
             dt.Hour(),
             dt.Minute(),
             dt.Second(),
             dt.DayOfWeek());
  Serial.print(datestring);
  lcd.setCursor( 0,0);
  lcd.print(dt.Year());
  lcd.setCursor(4,0);
  lcd.print("/");
  lcd.setCursor(5,0);
  lcd.print(dt.Month());
  lcd.setCursor(7,0);
  lcd.print("/");
  lcd.setCursor(8,0);
  lcd.print(dt.Day());
  //時間
  lcd.setCursor( 0,1);
  lcd.print(dt.Hour());
  lcd.setCursor(2,1);
  lcd.print(":");
  lcd.setCursor(3,1);
  lcd.print(dt.Minute());
  lcd.setCursor(5,1);
  lcd.print(":");
  lcd.setCursor(6,1);
  lcd.print(dt.Second());
  lcd.setCursor(10,1);
  lcd.print(dt.DayOfWeek());
}
