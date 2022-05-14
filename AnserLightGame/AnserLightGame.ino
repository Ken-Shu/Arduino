//左邊玩家
const int LEFT_LED_PIN_1 = 8;
const int LEFT_LED_PIN_2 = 9;
const int LEFT_ANSWER_BUTTON_PIN = 7;
//搶答燈
const int ANSWER_LED_PIN= 5;
//右邊玩家
const int RIGHT_LED_PIN_1 = 3;
const int RIGHT_LED_PIN_2 = 4;
const int RIGHT_ANSWER_BUTTON_PIN = 6;
//蜂鳴器(Buzeer)
const int BUZEER_PIN = 10;
//回合數
int count = 2;
//左邊玩家分數
int left_score = 0;
//右邊玩家分數
int right_score= 0;
//遊戲結束
boolean gameover = false;
//音符陣列
int freq []= {0, 262,294,330,349,392,440,494};
int bee[] ={5,3,3,4,2,2,1,2,3,4,5,5,5};
void setup() {
  Serial.begin(9600);
  //初始設定
  pinMode(LEFT_LED_PIN_1,OUTPUT);
  pinMode(LEFT_LED_PIN_2,OUTPUT);
  pinMode(LEFT_ANSWER_BUTTON_PIN,INPUT);
  pinMode(ANSWER_LED_PIN,OUTPUT);
  pinMode(RIGHT_LED_PIN_1,OUTPUT);
  pinMode(RIGHT_LED_PIN_2,OUTPUT);
  pinMode(RIGHT_ANSWER_BUTTON_PIN,INPUT_PULLUP);
  pinMode(BUZEER_PIN,OUTPUT);
  //所有燈先關閉
  digitalWrite(LEFT_LED_PIN_1 ,LOW);
  digitalWrite(LEFT_LED_PIN_2 ,LOW);
  digitalWrite(RIGHT_LED_PIN_1 ,LOW);
  digitalWrite(RIGHT_LED_PIN_2 ,LOW);
  //遊戲開始
  gameover = false;
  //遊戲開始音
  for(int i = 0; i<=13;i++){
   tone(BUZEER_PIN , freq[bee[i]],500);
   delay(200);
  } 
}

void loop() {
  int lb = digitalRead(LEFT_ANSWER_BUTTON_PIN);
  int rb = digitalRead(RIGHT_ANSWER_BUTTON_PIN);
   
  if(gameover){
    return;
  }
  //關閉搶答燈
  digitalWrite(ANSWER_LED_PIN ,LOW);
  Serial.print("開始");
  //開始出題
  delay(random(3000,10000));
  //搶答燈亮
  digitalWrite(ANSWER_LED_PIN ,HIGH);
  
  //蜂鳴器
//  digitalWrite(BUZEER_PIN , HIGH);
//  delay(50);//發音時間
//  digitalWrite(BUZEER_PIN , LOW);
  sound(50); //發出聲音
  
  //等待玩家按下按鈕
  while(true){
    if(digitalRead(LEFT_ANSWER_BUTTON_PIN) == 0){
      left_score++;
      sound(50);
       Serial.print("LEFT_BUTTON");
        Serial.println(lb);
      if(left_score == 1){
        digitalWrite(LEFT_LED_PIN_1 ,HIGH);      
      }else{
        digitalWrite(LEFT_LED_PIN_2 ,HIGH);
      }
      break;
    }
    //右邊玩家按下
     if(digitalRead(RIGHT_ANSWER_BUTTON_PIN) == 0){
      right_score++;
      sound(50);
      Serial.print("RIGHT_BUTTON");
      Serial.println(rb);
      if(right_score == 1){
        digitalWrite(RIGHT_LED_PIN_1 ,HIGH);      
      }else{
        digitalWrite(RIGHT_LED_PIN_2 ,HIGH);
      }
      break;
    }
  }
  if(left_score == count){
    Serial.println("Left WIN");
    gameover = true;
    gameoverSound(100,3);
  }
   if(right_score == count){
    Serial.println("Right WIN");
    gameover = true;
    gameoverSound(100,4);
  }
  delay(1000);
}

void sound(int delaytime) {
   //蜂鳴器
  digitalWrite(BUZEER_PIN , HIGH);
  delay(delaytime);//發音時間
  digitalWrite(BUZEER_PIN , LOW);
}

void gameoverSound(int delaytime , int times) {
  for(int i= 0 ; i<times ; i++){
   delay(delaytime);
   sound(50);  
  }
}
