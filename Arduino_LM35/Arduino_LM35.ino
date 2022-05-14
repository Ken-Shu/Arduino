#define LM35_PIN A1
void setup() {
  pinMode(LM35_PIN , INPUT);
  Serial.begin(9600);
}

void loop() {
  float value = analogRead(LM35_PIN);
  float temp = (value/1024.0*5.0)/0.01;
  Serial.print("Temp : ");
  Serial.println(temp);
  delay(10000);
}
