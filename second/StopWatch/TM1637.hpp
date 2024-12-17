#ifndef _TM1637_h_
#define _TM1637_h_

#include <Arduino.h>

namespace tm1637 {

constexpr byte LCLK = 14;
constexpr byte DIO = 12;
constexpr byte HALF_CLK = 10;
constexpr byte MODE = 0b01000100; // 固定アドレスモード
constexpr byte ADR = 0b11000000;  // 1桁目アドレス

class TM1637 {
public:
  void set(byte data, byte intensity);

private:
  void start();
  void end();
  bool writeS_byte(byte b);
};
} // namespace tm1637

extern tm1637::TM1637 TM1637;

#endif
