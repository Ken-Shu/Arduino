//5011AS 共陰 5011BS 共陽
boolean po = 0; // 0 :共陰 1 :共陽
byte l = !po;
byte o = po;
byte seven_seg_digits [10][7] = {
  { l, l, l, l, l, l, o }, // = 0
  { o, l, l, o, o, o, o }, // = 1
  { l, l, o, l, l, o, l }, // = 2
  { l, l, l, l, o, o, l }, // = 3
  { o, l, l, o, o, l, l }, // = 4
  { l, o, l, l, o, l, l }, // = 5
  { l, o, l, l, l, l, l }, // = 6
  { l, l, l, o, o, o, o }, // = 7
  { l, l, l, l, l, l, l }, // = 8
  { l, l, l, o, o, l, l }  // = 9
};
byte pro_set_hello [5][7]{
  {o ,l ,l ,o ,l ,l ,l}, // H
  {l ,o ,o ,l ,l ,l ,l}, // E
  {o ,o ,o ,l ,l ,l ,o}, // L
  {o ,o ,o ,l ,l ,l ,o}, // L
  { l, l, l, l, l, l,o} // O
};

void setup() {
  Serial.begin(9600);
  delay(2);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);

}

void loop() {
  //digitalWrite(9,HIGH);
  //digitalWrite(3,HIGH);
  //digitalWrite(4,HIGH);
  
  sevenSegWrite();  
  delay(2000);
}
//在七段顯示器上 顯示所指定的數字
void sevenSegWrite(){
  for(int i = 0 ; i<10 ; i++){
  byte pin = 2;
  for(byte seg = 0 ; seg<7 ; seg++){
    digitalWrite(pin ,seven_seg_digits[i][seg] );
    ++pin;
  }
  delay(500);
  }
}
//七段顯示器顯示 HELLO
void helloprint(){
  for(int i = 0 ; i<5 ; i++){
  byte pin = 2;
  for(byte seg = 0 ; seg<7 ; seg++){
    digitalWrite(pin ,pro_set_hello[i][seg] );
    ++pin;
  }
  delay(500);
  }
}
