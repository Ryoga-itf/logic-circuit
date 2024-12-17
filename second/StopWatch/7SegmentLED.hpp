#ifndef _SevenSegmentLED_h_
#define _SevenSegmentLED_h_

#include "TimeCount.hpp"
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

constexpr byte SEG7_DIG0[] = {1, 0, 1, 0};
constexpr byte SEG7_DIG1[] = {1, 1, 0, 0};

constexpr byte SEG_GP[] = {0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1};
constexpr byte SEG_FP[] = {1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0};
constexpr byte SEG_EP[] = {1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0};
constexpr byte SEG_DP[] = {1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1};
constexpr byte SEG_CP[] = {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0};
constexpr byte SEG_BP[] = {1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0};
constexpr byte SEG_AP[] = {1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1};

class SevenSegmentLED {
public:
  void setup();
  void write_a_digit(byte digit, byte data);
  void write_timecount(TimeCount timecount);
  void write_timecount_with_blink(TimeCount timecount, byte target, bool blink);
  void clear();
};

}; // namespace seven_segment

extern seven_segment::SevenSegmentLED SevenSegmentLED;

#endif
