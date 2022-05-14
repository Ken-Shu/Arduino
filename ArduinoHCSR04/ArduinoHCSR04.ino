//超音波 HC-SR 04
#define TRIG_PIN 5
#define ECHO_PIN 6

#define RELAY_PIN 4

void setup() {
  Serial.begin(9600);
  delay(2);
  pinMode(ECHO_PIN,INPUT);
  pinMode(TRIG_PIN,OUTPUT);
  pinMode(RELAY_PIN , OUTPUT);
  Serial.print("begin");
}

void loop() {
  //發送 HIGH 電壓 持續 10ms
  digitalWrite(TRIG_PIN , HIGH);
  delayMicroseconds(10); //延遲 10 ms
  digitalWrite(TRIG_PIN , LOW);
  //讀取 ECHO_PIN 的資料 並透過 pulseIn 來讀取針腳脈衝時間
  int duration = pulseIn(ECHO_PIN , HIGH); //HIGH 才能讀取
  //在攝氏0~50度下音速每一公分需要29.1ms
  //公式 距離(cm) = 時間(us)/(來回)2/29.1(m/s轉換cm/us)
  int cm = (duration/2)/29.1;
  Serial.print("duration : ");
  Serial.print(duration);
  Serial.print(",  cm : ");
  Serial.println(cm);
  if(cm<10){
    digitalWrite(RELAY_PIN,HIGH);
  }else{
    digitalWrite(RELAY_PIN,LOW);
  }
  delay(200);
  

}
