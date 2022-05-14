// 4*4 keypad 薄膜鍵盤
#include "Adafruit_Keypad.h"
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

//在鍵盤上按下 2+3=5 <--自動算出 5
//並顯示在LCD面板
char x = ' ';
char y = ' ';
char z = ' ';
int count = 0;

//定義鍵盤的行列
const byte ROWS = 4; //定義列數(橫向)
const byte COLS = 4; //定義行數(縱向)

//定義鍵盤上每一個按鈕名稱
//C 表示清除
char keys[ROWS][COLS] = {
  {'1' , '2' , '3' , '/'},
  {'4' , '5' , '6' , '*'},
  {'7' , '8' , '9' , '-'},
  {'C' , '0' , '=' , '+'},
};

//定義腳位(列)
byte rows_Pin[ROWS] = {11 ,10 ,9 ,8 };
//定義腳位(行)
byte cols_Pin[COLS] ={7 ,6 ,5 ,4 };

//鍵盤自製初始化
Adafruit_Keypad customKeypad = Adafruit_Keypad(makeKeymap(keys) , rows_Pin ,cols_Pin ,ROWS ,COLS);

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  delay(2);
  lcd.clear();
  lcd.print("Keypad ready...");
  customKeypad.begin();
  Serial.println("customKeypad ready ...");
  delay(2000);
  lcd.clear();

}

void loop() {
  //開始偵測使用者的按鍵狀態
  customKeypad.tick(); //判斷按下哪一個鍵
  while(customKeypad.available()){   
    keypadEvent e = customKeypad.read();//讀取
    //KEY_JUST_RELEASED 放開事件
    //KEY_JUST_PRESSED 按下事件
    if(e.bit.EVENT == KEY_JUST_PRESSED){
    Serial.println((char)e.bit.KEY);
    if(e.bit.KEY == 'C'){
        lcd.setCursor(0 , 0);
        lcd.print("                ");
        x = ' ';
        y = ' ';
        z = ' ';
        count = 0;   
        break;     
      }
    switch(count){
      case 0:
        x = e.bit.KEY;
        lcd.setCursor(2 , 0);
        lcd.print(x);
        count++;
        break;
      case 1:
        z = e.bit.KEY;
        lcd.setCursor(4 , 0);
        lcd.print(z);
        count++;
        break;
      case 2:
        y = e.bit.KEY;
        lcd.setCursor(6 , 0);
        lcd.print(y);
        count++;
        break;
      case 3:
        x = ' ';
        y = ' ';
        z = ' ';
        count = 0;
        lcd.setCursor(0 , 0);
        lcd.print("                ");
        break;        
      }
    }
    Serial.print("x = ");
    Serial.println(x);
    Serial.print("z = ");
    Serial.println(z);
    Serial.print("y = ");
    Serial.println(y);
    Serial.print("count = ");
    Serial.println(count);
     switch(z){
      case '+':
      Serial.print("result : ");
      Serial.println((x-48) + (y-48));
      lcd.setCursor(8 , 0);
      lcd.print("=");
      lcd.setCursor(11 , 0);
      lcd.print((x-48) + (y-48));
      lcd.setCursor(12,0);
      lcd.print("   ");
      break;
      case '-':
      Serial.print("result : ");
      Serial.println((x-48) - (y-48));
      lcd.setCursor(8 , 0);
      lcd.print("=");
      lcd.setCursor(11 , 0);
      lcd.print((x-48) - (y-48));
      lcd.setCursor(12,0);
      lcd.print("   ");
      break;
      case '*':
      Serial.print("result : ");
      Serial.println((x-48) * (y-48));
      lcd.setCursor(8 , 0);
      lcd.print("=");
      lcd.setCursor(11 , 0);
      lcd.print((x-48) * (y-48));
      lcd.setCursor(12,0);
      lcd.print("   ");
      break;
      case '/':
      Serial.print("result : ");
      Serial.println((x-48) / (y-48));
      lcd.setCursor(8 , 0);
      lcd.print("=");
      lcd.setCursor(11 , 0);
      lcd.print((x-48) / (y-48));
      lcd.setCursor(12,0);
      lcd.print("   ");
      break;
     }
  }
  
  delay(10);

}
