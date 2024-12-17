#include "7SegmentLED.hpp"
#include "KeyRepeat.hpp"
#include "TM1637.hpp"
#include "TimeCount.hpp"
#include <Arduino.h>
#include <TimerOne.h>

TimeCount timecount;
KeyRepeat keyUp(A6, 1000, 100, true);
KeyRepeat keyDown(A7, 1000, 100, true);
KeyRepeat keyMode(A2, 1000, 100, true);
KeyRepeat keyDigit(A3, 1000, 100, true);

/*
 *             keyUp (A6)
 *                 |
 *                 o
 * keyMode (A2)--o   o-- digit (A3)
 *         (16)    o           (17)
 *                 |
 *            KeyDown (A7)
 */

enum class State {
  Setting,
  SettingCounterInc,
  SettingCounterDec,
  CountDown,
  StopWatch,
  StopWatchPause,
  Beep,
};

void setup() {
  SevenSegmentLED.setup();
  keyUp.setup();
  keyDown.setup();
  keyMode.setup();

  Timer1.initialize(1000000);
  Timer1.stop();
}

void loop() {
  static auto state = State::Setting;
  static byte target = 0;
  static auto cycle = 0;
  static unsigned int count_from = 0;

  bool blink = false;

  switch (state) {
  case State::Setting:
    if (keyUp.read() > 0) {
      state = State::SettingCounterInc;
    }
    if (keyDown.read() > 0) {
      state = State::SettingCounterDec;
    }
    if (keyMode.read() == 1) {
      if (timecount == 0) {
        Timer1.initialize(1000);
        Timer1.attachInterrupt([]() { timecount.inc_milliseconds(); });
        Timer1.restart();
        state = State::StopWatch;
      } else {
        Timer1.initialize(1000000);
        Timer1.attachInterrupt([]() {
          if (timecount.count() > 0) {
            timecount--;
          }
        });
        Timer1.restart();
        state = State::CountDown;
        count_from = timecount.count();
      }
    }
    if (keyDigit.read() == 1) {
      target = (target + 1) % 4;
      cycle = 0;
    }
    blink = cycle < 100;
    break;
  case State::SettingCounterInc:
    timecount.inc_digit(target);
    state = State::Setting;
    break;
  case State::SettingCounterDec:
    timecount.dec_digit(target);
    state = State::Setting;
    break;
  case State::CountDown:
    if (keyMode.read() == 1) {
      Timer1.stop();
      TM1637.set(0b00000000, 0b10000111);
      state = State::Setting;
    }
    if (timecount == 0) {
      Timer1.stop();
      TM1637.set(0b00000000, 0b10000111);
      state = State::Beep;
    }

    {
      const auto progress = int(8.0 * (timecount.count()) / count_from);
      byte data8 = 0b00000000;
      for (int i = 0; i < progress; i++) {
        data8 = (data8 | (1 << i));
      }
      constexpr byte INTENSITY = 0b10001010; // 4/16
      TM1637.set(data8, INTENSITY);
    }

    break;
  case State::StopWatch:
    if (keyMode.read() == 1) {
      Timer1.stop();
      timecount = TimeCount();

      TM1637.set(0b00000000, 0b10000111);
      state = State::Setting;
    }

    if (keyDigit.read() == 1) {
      Timer1.stop();
      state = State::StopWatchPause;
    }

    {
      const auto progress = (timecount.milliseconds() + 1) / 125.0;
      byte data8 = 0b00000000;
      for (int i = 0; i < progress; i++) {
        data8 = (data8 | (1 << i));
      }
      constexpr byte INTENSITY = 0b10001010; // 4/16
      TM1637.set(data8, INTENSITY);
    }

    break;
  case State::StopWatchPause:
    if (keyMode.read() == 1) {
      timecount = TimeCount();
      TM1637.set(0b00000000, 0b10000111);
      state = State::Setting;
    }

    if (keyDigit.read() == 1) {
      Timer1.resume();
      state = State::StopWatch;
    }
    break;
  case State::Beep:
    tone(2, 880);
    delay(1000);
    noTone(2);
    state = State::Setting;
    break;
  }
  cycle = (cycle + 1) % 300;

  SevenSegmentLED.write_timecount_with_blink(timecount, target, blink);
}
