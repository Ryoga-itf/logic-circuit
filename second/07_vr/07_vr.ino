#include <Arduino.h>

void setup() {
  pinMode(A1, INPUT);
  Serial.begin(9600);
}

void loop() {
  const auto vr = analogRead(A1);

  Serial.println(vr);

  delay(100);
}
