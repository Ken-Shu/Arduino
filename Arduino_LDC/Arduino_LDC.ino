#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
// OR LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup() {
  // initialize the LCD
  lcd.begin();

  // Turn on the blacklight and print a message.
  lcd.backlight();
  //lcd.setBacklight(true); //關閉背光
  //清空LCD
  lcd.clear();
  //設定cusor
  lcd.setCursor(5,1); //欄位(0~15) 列(0~1)
  lcd.print("Hello");
  lcd.setCursor(2,0);
  lcd.print("World");
}

void loop() {
  // 跑馬燈
  for(int i = 5 ; i<=11; i++){
    //第二列整列清空
    lcd.setCursor(0,1); //指向第二列
    lcd.print("                "); //16個空白
    
    lcd.setCursor(i,1);
    lcd.print("Hello");
    delay(1000);
  }
  for(int i = 11 ; i>=5; i--){
    lcd.setCursor(0,1);
    lcd.print("                ");
    
    lcd.setCursor(i,1);
    lcd.print("Hello");
    delay(1000);
  }


}
