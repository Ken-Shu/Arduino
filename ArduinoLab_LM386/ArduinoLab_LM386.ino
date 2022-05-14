//LM386 音頻處理晶片
/*
 * 接線方式
 * A0 : A0
 * G :GND
 * + :5V
 * D0 : 不接
 */
#define RELAY_PIN 4
#define CONTROL_PIN 13
int count = 1;

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN , OUTPUT);
  pinMode(CONTROL_PIN , OUTPUT);
  delay(2);
  Serial.println("Enable IR");
}

void loop() {
  //控制燈 如果此燈有亮 才能控制RELAY燈
  digitalWrite(CONTROL_PIN , HIGH);
  //讀取 A0 的值
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  if(sensorValue > 35){
    digitalWrite(RELAY_PIN , !digitalRead(RELAY_PIN));
    digitalWrite(CONTROL_PIN , LOW);
    delay(5000);
  }
//  if(sensorValue > 35){
//    if(count%2 == 1){
//    Serial.println(sensorValue);
//    Serial.print("count : ");
//    Serial.println(count);
//    digitalWrite(RELAY_PIN,HIGH);
//    }else if(count%2 == 0){
//    Serial.print("count : ");
//    Serial.println(count);
//    digitalWrite(RELAY_PIN,LOW);
//    
//    }
//    count++;
//  }
  delay(30);

}
