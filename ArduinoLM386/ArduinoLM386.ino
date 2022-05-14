//LM386 音頻處理晶片
/*
 * 接線方式
 * A0 : A0
 * G :GND
 * + :5V
 * D0 : 不接
 */
void setup() {
  Serial.begin(9600);
  delay(2);
}

void loop() {
  //讀取 A0 的值
  int sensorValue = analogRead(A0);
  
  //if(sensorValue > 35){
    Serial.println(sensorValue);  
  //}
  delay(10);

}
