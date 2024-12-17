#include "TM1637.hpp"

namespace tm1637 {

void TM1637::set(byte data, byte intensity) {
  start();
  writeS_byte(MODE);
  end();

  start();
  writeS_byte(ADR);
  writeS_byte(data);
  end();

  start();
  writeS_byte(intensity);
  end();
}

void TM1637::start() {
  pinMode(LCLK, INPUT);
  delayMicroseconds(HALF_CLK);
  pinMode(DIO, INPUT);
  delayMicroseconds(HALF_CLK);
  pinMode(DIO, OUTPUT);
  delayMicroseconds(HALF_CLK);
}
void TM1637::end() {
  pinMode(DIO, OUTPUT);
  delayMicroseconds(HALF_CLK);
  pinMode(LCLK, INPUT);
  delayMicroseconds(HALF_CLK);
  pinMode(DIO, INPUT);
  delayMicroseconds(HALF_CLK);
}
bool TM1637::writeS_byte(byte data) {
  for (byte i = 0; i < 8; i++) {
    pinMode(LCLK, OUTPUT);
    delayMicroseconds(HALF_CLK);

    if (data & 0b00000001) {
      pinMode(DIO, INPUT);
    } else
      pinMode(DIO, OUTPUT);

    delayMicroseconds(HALF_CLK);

    pinMode(LCLK, INPUT);
    delayMicroseconds(HALF_CLK);

    data = data >> 1;
  }

  // wait ACK
  pinMode(LCLK, OUTPUT);
  pinMode(DIO, INPUT);
  delayMicroseconds(HALF_CLK);

  // end ACK
  pinMode(LCLK, INPUT);
  delayMicroseconds(HALF_CLK);
  byte ack = digitalRead(DIO);

  if (ack == 0) {
    pinMode(DIO, OUTPUT);
  }

  delayMicroseconds(HALF_CLK);
  pinMode(LCLK, OUTPUT);
  delayMicroseconds(HALF_CLK);

  return ack;
}

} // namespace tm1637
