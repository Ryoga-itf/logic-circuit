#include <Arduino.h>

constexpr int SEG_G = 3;
constexpr int SEG_F = 4;
constexpr int SEG_E = 5;
constexpr int SEG_D = 6;
constexpr int SEG_C = 7;
constexpr int SEG_B = 8;
constexpr int SEG_A = 9;
constexpr int SEG7_BIN0 = 10;
constexpr int SEG7_BIN1 = 11;

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

void write_a_digit(byte data) {
  digitalWrite(SEG7_BIN0, 0);
  digitalWrite(SEG7_BIN1, 0);

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

void loop() {
  for (byte i = 0; i <= 10; i++) {
    write_a_digit(i);
    delay(500);
  }
}
