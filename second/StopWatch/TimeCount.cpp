#include "TimeCount.hpp"

void TimeCount::inc_digit(byte digit) {
  if (digit == 0) {
    const auto tmp = m_seconds % 10;
    if (tmp == 9) {
      m_seconds -= 9;
    } else {
      m_seconds += 1;
    }
  } else if (digit == 1) {
    const auto tmp = m_seconds / 10;
    if (tmp == 5) {
      m_seconds -= 50;
    } else {
      m_seconds += 10;
    }
  } else if (digit == 2) {
    const auto tmp = m_minutes % 10;
    if (tmp == 9) {
      m_minutes -= 9;
    } else {
      m_minutes += 1;
    }
  } else if (digit == 3) {
    const auto tmp = m_minutes / 10;
    if (tmp == 9) {
      m_minutes -= 90;
    } else {
      m_minutes += 10;
    }
  }
}

void TimeCount::dec_digit(byte digit) {
  if (digit == 0) {
    const auto tmp = m_seconds % 10;
    if (tmp == 0) {
      m_seconds += 9;
    } else {
      m_seconds -= 1;
    }
  } else if (digit == 1) {
    const auto tmp = m_seconds / 10;
    if (tmp == 0) {
      m_seconds += 50;
    } else {
      m_seconds -= 10;
    }
  } else if (digit == 2) {
    const auto tmp = m_minutes % 10;
    if (tmp == 0) {
      m_minutes += 9;
    } else {
      m_minutes -= 1;
    }
  } else if (digit == 3) {
    const auto tmp = m_minutes / 10;
    if (tmp == 0) {
      m_minutes += 90;
    } else {
      m_minutes -= 10;
    }
  }
}

byte TimeCount::get_digit(byte digit) const {
  int tmp = m_minutes * 100 + m_seconds;
  for (byte i = 0; i < digit; i++) {
    tmp /= 10;
  }
  return tmp % 10;
}

TimeCount &TimeCount::operator++() {
  m_seconds++;
  if (m_seconds == 60) {
    m_seconds = 0;
    m_minutes++;
  }
  return *this;
}
TimeCount &TimeCount::operator--() {
  if (m_seconds == 0) {
    m_seconds = 60;
    m_minutes--;
  }
  m_seconds--;
  return *this;
}

TimeCount TimeCount::operator++(int) {
  TimeCount tmp(*this);
  ++(*this);
  return tmp;
}
TimeCount TimeCount::operator--(int) {
  TimeCount tmp(*this);
  --(*this);
  return tmp;
}

TimeCount &TimeCount::inc_milliseconds() {
  m_milliseconds++;
  if (m_milliseconds == 1000) {
    m_milliseconds = 0;
    m_seconds++;
  }
  return *this;
}
TimeCount &TimeCount::dec_milliseconds() {
  if (m_milliseconds == 0) {
    m_milliseconds = 1000;
    m_seconds--;
  }
  m_milliseconds--;
  return *this;
}
