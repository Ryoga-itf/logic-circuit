#include <Arduino.h>
#include <TimerOne.h>
unsigned int count = 0;

void count_up() {
  count++;
  Serial.println(count);
}

void setup() {
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(count_up);

  Serial.begin(9600);
}

void loop() {}
