#include "KeyRepeat.hpp"
#include "Arduino.h"

void KeyRepeat::setup() { pinMode(m_pin, INPUT); }

int KeyRepeat::read() {
  const bool current_sw = m_isAnalogPin ? analogRead(m_pin) >= INPUT_THRESHOLD
                                        : digitalRead(m_pin) == HIGH;

  const auto now = millis();
  int ret = 0;

  if (current_sw) {
    if (!m_last_sw) {
      m_last_beat = now + m_delay_ms;
      ret = 1;
    }
    if (now >= m_last_beat && now - m_last_beat >= m_interval_ms) {
      m_last_beat = now;
      ret = 2;
    }
  }

  m_last_sw = current_sw;

  return ret;
}
