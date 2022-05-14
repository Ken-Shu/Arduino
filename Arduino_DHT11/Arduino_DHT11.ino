#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11

//初始化物件
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");

  dht.begin();
}

void loop() {
  delay(2000);
  float h = dht.readHumidity(); // 濕度
  float t = dht.readTemperature(); // 攝氏
  float f = dht.readTemperature(true); //華氏
  //若讀取失敗 則重讀
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  //華氏體感溫度
  float hif = dht.computeHeatIndex(f, h); 
  //攝氏體感溫度
  float hic = dht.computeHeatIndex(t, h, false); 
  //列印資料
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));
  
}
