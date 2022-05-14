// 4*4 keypad 薄膜鍵盤
#include "Adafruit_Keypad.h"

//定義鍵盤的行列
const byte ROWS = 4; //定義列數(橫向)
const byte COLS = 4; //定義行數(縱向)

//定義鍵盤上每一個按鈕名稱
char keys[ROWS][COLS] = {
  {'1' , '2' , '3' , 'A'},
  {'4' , '5' , '6' , 'B'},
  {'7' , '8' , '9' , 'C'},
  {'*' , '0' , '#' , 'D'},
};

//定義腳位(列)
byte rows_Pin[ROWS] = {11 ,10 ,9 ,8 };
//定義腳位(行)
byte cols_Pin[COLS] ={7 ,6 ,5 ,4 };

//鍵盤自製初始化
Adafruit_Keypad customKeypad = Adafruit_Keypad(makeKeymap(keys) , rows_Pin ,cols_Pin ,ROWS ,COLS);

void setup() {
  Serial.begin(9600);
  delay(2);
  customKeypad.begin();
  Serial.println("customKeypad ready ...");

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
    }
  }
  
  delay(10);

}
