#include"DHT.h"
#include"Arduino.h"

#define DHTPIN 32
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup(){
  Serial.begin(9600);
  dht.begin();
  
}
void loop(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
   Serial.print("Nhiệt độ:");
   Serial.print(t);
   Serial.print("°C");
   Serial.print(h);
   Serial.print(" %");
   delay(1000);
}
