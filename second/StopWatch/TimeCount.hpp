#ifndef _TimeCount_h_
#define _TimeCount_h_
#include <Arduino.h>

class TimeCount {
public:
  TimeCount() = default;
  TimeCount(unsigned int minutes, unsigned int second)
      : m_minutes(minutes), m_seconds(second) {}

  inline unsigned int milliseconds() const { return m_milliseconds; }
  inline unsigned int seconds() const { return m_seconds; }
  inline unsigned int minutes() const { return m_minutes; }

  inline unsigned int count() const { return m_minutes * 60 + m_seconds; }

  void inc_digit(byte digit);
  void dec_digit(byte digit);
  byte get_digit(byte digit) const;

  TimeCount &operator++();
  TimeCount &operator--();
  TimeCount operator++(int);
  TimeCount operator--(int);

  TimeCount &inc_milliseconds();
  TimeCount &dec_milliseconds();

  inline friend bool operator==(const TimeCount &lhs, const TimeCount &rhs) {
    return lhs.count() == rhs.count();
  }
  inline friend bool operator==(const TimeCount &lhs, const unsigned int &rhs) {
    return lhs.count() == rhs;
  }

private:
  unsigned int m_milliseconds = 0;
  unsigned int m_seconds = 0;
  unsigned int m_minutes = 0;
};

#endif
