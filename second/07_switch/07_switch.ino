#include "HardwareSerial.h"
#include <Arduino.h>

void setup() {
  pinMode(16, INPUT);
  pinMode(17, INPUT);
  pinMode(A6, INPUT);
  pinMode(A7, INPUT);
  Serial.begin(9600);
}

/*
 *          SW3 (A6)
 *             |
 *             o
 * SW1 (A2)--o   o-- SW2 (A3)
 *     (16)    o         (17)
 *             |
 *          SW4 (A7)
 */

void loop() {
  int sw1 = digitalRead(16);
  int sw2 = digitalRead(17);
  int sw3 = analogRead(A6);
  int sw4 = analogRead(A7);

  Serial.print(sw1);
  Serial.print('\t');
  Serial.print(sw2);
  Serial.print('\t');
  Serial.print(sw3);
  Serial.print('\t');
  Serial.println(sw4);

  delay(100);
}
