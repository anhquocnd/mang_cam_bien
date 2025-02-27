#include <Arduino.h>

#define LED 5
#define BUTTON 4

int buttonState;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);

  digitalWrite(LED,LOW);
}

void loop() {

    digitalWrite(LED,1);
  delay (100);
    digitalWrite(LED,0);
  delay(100);
}