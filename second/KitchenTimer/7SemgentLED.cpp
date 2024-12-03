#include "7SegmentLED.hpp"

namespace seven_segment {

void SevenSegmentLED::setup() {
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

void SevenSegmentLED::write_a_digit(byte digit, byte data) {
  digitalWrite(SEG7_BIN0, SEG7_DIG0[digit]);
  digitalWrite(SEG7_BIN1, SEG7_DIG1[digit]);

  digitalWrite(SEG_G, SEG_GP[min(data, 10)]);
  digitalWrite(SEG_F, SEG_FP[min(data, 10)]);
  digitalWrite(SEG_E, SEG_EP[min(data, 10)]);
  digitalWrite(SEG_D, SEG_DP[min(data, 10)]);
  digitalWrite(SEG_C, SEG_CP[min(data, 10)]);
  digitalWrite(SEG_B, SEG_BP[min(data, 10)]);
  digitalWrite(SEG_A, SEG_AP[min(data, 10)]);
}

void SevenSegmentLED::write_timecount(unsigned int timecount) {
  const int minutes = timecount / 60;
  const int seconds = timecount % 60;

  int tmp = minutes * 100 + seconds;
  for (byte i = 0; i < 4; i++) {
    write_a_digit(i, tmp % 10);
    tmp /= 10;
    delay(1);
    clear();
  }
}

void SevenSegmentLED::clear() {
  for (byte i = 0; i < 4; i++) {
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
