#include <Arduino.h>

namespace seven_segment {

constexpr uint8_t SEG_G = 3;
constexpr uint8_t SEG_F = 4;
constexpr uint8_t SEG_E = 5;
constexpr uint8_t SEG_D = 6;
constexpr uint8_t SEG_C = 7;
constexpr uint8_t SEG_B = 8;
constexpr uint8_t SEG_A = 9;
constexpr uint8_t SEG7_BIN0 = 10;
constexpr uint8_t SEG7_BIN1 = 11;

void setup() {
  pinMode(SEG_G, OUTPUT);
  pinMode(SEG_F, OUTPUT);
  pinMode(SEG_E, OUTPUT);
  pinMode(SEG_D, OUTPUT);
  pinMode(SEG_C, OUTPUT);
  pinMode(SEG_B, OUTPUT);
  pinMode(SEG_A, OUTPUT);
  pinMode(SEG7_BIN0, OUTPUT);
  pinMode(SEG7_BIN1, OUTPUT);
}

void write_a_digit(byte digit, byte data) {
  constexpr byte SEG7_DIG0[] = {1, 0, 1, 0};
  constexpr byte SEG7_DIG1[] = {1, 1, 0, 0};

  digitalWrite(SEG7_BIN0, SEG7_DIG0[digit]);
  digitalWrite(SEG7_BIN1, SEG7_DIG1[digit]);

  constexpr byte SEG_GP[] = {0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1};
  constexpr byte SEG_FP[] = {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0};
  constexpr byte SEG_EP[] = {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0};
  constexpr byte SEG_DP[] = {1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1};
  constexpr byte SEG_CP[] = {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0};
  constexpr byte SEG_BP[] = {1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0};
  constexpr byte SEG_AP[] = {1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1};

  digitalWrite(SEG_G, SEG_GP[min(data, 10)]);
  digitalWrite(SEG_F, SEG_FP[min(data, 10)]);
  digitalWrite(SEG_E, SEG_EP[min(data, 10)]);
  digitalWrite(SEG_D, SEG_DP[min(data, 10)]);
  digitalWrite(SEG_C, SEG_CP[min(data, 10)]);
  digitalWrite(SEG_B, SEG_BP[min(data, 10)]);
  digitalWrite(SEG_A, SEG_AP[min(data, 10)]);
}

void clear() {
  for (byte i = 0; i <= 3; i++) {
    digitalWrite(SEG7_BIN0, i & 1);
    digitalWrite(SEG7_BIN1, i & 2);
    digitalWrite(SEG_G, 0);
    digitalWrite(SEG_F, 0);
    digitalWrite(SEG_E, 0);
    digitalWrite(SEG_D, 0);
    digitalWrite(SEG_C, 0);
    digitalWrite(SEG_B, 0);
    digitalWrite(SEG_A, 0);
  }
}

} // namespace seven_segment

void setup() {
  seven_segment::setup();
  pinMode(A1, INPUT);
}

void loop() {
  auto vr = analogRead(A1);

  for (byte i = 0; i < 4; i++) {
    seven_segment::write_a_digit(i, vr % 10);
    vr /= 10;
    delay(1);
    seven_segment::clear();
    delayMicroseconds(10);
  }
}
