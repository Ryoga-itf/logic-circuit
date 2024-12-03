#ifndef KeyRepeat_h_
#define KeyRepeat_h_

#include <Arduino.h>

using time_type = decltype(millis());
constexpr uint8_t INPUT_THRESHOLD = 511;

class KeyRepeat {
public:
  KeyRepeat(uint8_t pin, time_type delay_ms, time_type interval_ms,
            bool isAnalogPin = false)
      : m_pin(pin), m_delay_ms(delay_ms), m_interval_ms(interval_ms),
        m_isAnalogPin(isAnalogPin) {}

  void setup();
  bool read();

private:
  uint8_t m_pin;
  time_type m_last_beat = 0;
  bool m_last_sw = false;

  const time_type m_delay_ms;
  const time_type m_interval_ms;
  const bool m_isAnalogPin;
};

#endif
