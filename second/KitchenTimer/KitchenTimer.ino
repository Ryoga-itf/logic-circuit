#include "7SegmentLED.hpp"
#include "KeyRepeat.hpp"
#include <Arduino.h>
#include <TimerOne.h>

constexpr unsigned int MAX_TIMECOUNT = 60 * 60;
unsigned int timecount = 0;
KeyRepeat keyUp(A6, 1000, 100, true);
KeyRepeat keyDown(A7, 1000, 100, true);
KeyRepeat keyMode(A2, 1000, 100, true);

/*
 *             keyUp (A6)
 *                 |
 *                 o
 * keyMode (A2)--o   o-- *none* (A3)
 *         (16)    o            (17)
 *                 |
 *            KeyDown (A7)
 */

enum class State {
  Setting,
  SettingCounterInc,
  SettingCounterDec,
  CountDown,
  Beep,
};

void setup() {
  SevenSegmentLED.setup();
  keyUp.setup();
  keyDown.setup();
  keyMode.setup();

  Timer1.initialize(1000000);
  Timer1.attachInterrupt([]() {
    if (timecount > 0) {
      timecount--;
    }
  });
  Timer1.stop();
}

void loop() {
  static auto state = State::Setting;

  switch (state) {
  case State::Setting:
    if (keyUp.read() > 0) {
      state = State::SettingCounterInc;
    }
    if (keyDown.read() > 0) {
      state = State::SettingCounterDec;
    }
    if (timecount > 0 && keyMode.read() == 1) {
      Timer1.restart();
      state = State::CountDown;
    }
    break;
  case State::SettingCounterInc:
    timecount = (timecount + 1) % MAX_TIMECOUNT;
    state = State::Setting;
    break;
  case State::SettingCounterDec:
    if (timecount > 0) {
      timecount--;
    }
    state = State::Setting;
    break;
  case State::CountDown:
    if (keyMode.read() == 1) {
      Timer1.stop();
      state = State::Setting;
    }
    if (timecount == 0) {
      Timer1.stop();
      state = State::Beep;
    }
    break;
  case State::Beep:
    tone(2, 880);
    delay(1000);
    noTone(2);
    state = State::Setting;
    break;
  }

  SevenSegmentLED.write_timecount(timecount);
}
