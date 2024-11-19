#include "pitches.h"
#include <Arduino.h>

constexpr unsigned long a = 225;
constexpr unsigned long b = 450;
constexpr unsigned long c = 675;
constexpr unsigned long d = 900;
constexpr unsigned long e = 1800;

struct note {
  unsigned int frequency;
  unsigned long duration;
};

// Yobikomi-kun
struct note melody[] = {
    {NOTE_A5, a},  {NOTE_A5, b},  {NOTE_B5, a}, {NOTE_A5, a},  {NOTE_FS5, a},
    {NOTE_A5, b},  {NOTE_A5, a},  {NOTE_A5, b}, {NOTE_B5, a},  {NOTE_A5, a},
    {NOTE_FS5, a}, {NOTE_A5, b},  {NOTE_D5, a}, {NOTE_D5, a},  {NOTE_D5, a},
    {NOTE_E5, a},  {NOTE_FS5, c}, {NOTE_D5, a}, {NOTE_FS5, c}, {NOTE_A5, a},
    {NOTE_A5, d},  {NOTE_D5, a},  {NOTE_D5, a}, {NOTE_D5, a},  {NOTE_E5, a},
    {NOTE_FS5, d}, {NOTE_D5, a},  {NOTE_D5, a}, {NOTE_D5, a},  {NOTE_E5, a},
    {NOTE_FS5, d}, {NOTE_E5, a},  {NOTE_E5, a}, {NOTE_E5, a},  {NOTE_D5, a},
    {NOTE_E5, b},  {NOTE_FS5, b}, {NOTE_A5, b}, {NOTE_G5, b},  {NOTE_FS5, b},
    {NOTE_E5, b},

    {NOTE_A5, a},  {NOTE_A5, b},  {NOTE_B5, a}, {NOTE_A5, a},  {NOTE_FS5, a},
    {NOTE_A5, b},  {NOTE_A5, a},  {NOTE_A5, b}, {NOTE_B5, a},  {NOTE_A5, a},
    {NOTE_FS5, a}, {NOTE_A5, b},  {NOTE_D5, a}, {NOTE_D5, a},  {NOTE_D5, a},
    {NOTE_E5, a},  {NOTE_FS5, c}, {NOTE_D5, a}, {NOTE_FS5, c}, {NOTE_A5, a},
    {NOTE_A5, d},  {NOTE_D5, a},  {NOTE_D5, a}, {NOTE_D5, a},  {NOTE_E5, a},
    {NOTE_FS5, d}, {NOTE_D5, a},  {NOTE_D5, a}, {NOTE_D5, a},  {NOTE_E5, a},
    {NOTE_FS5, d}, {NOTE_E5, a},  {NOTE_E5, a}, {NOTE_E5, a},  {NOTE_D5, a},
    {NOTE_E5, b},  {NOTE_FS5, b}, {NOTE_A5, b}, {NOTE_G5, b},  {NOTE_FS5, b},
    {NOTE_E5, b},

    {NOTE_A5, a},  {NOTE_A5, b},  {NOTE_B5, a}, {NOTE_A5, a},  {NOTE_FS5, a},
    {NOTE_A5, b},  {NOTE_A5, a},  {NOTE_A5, b}, {NOTE_B5, a},  {NOTE_A5, a},
    {NOTE_FS5, a}, {NOTE_A5, b},  {NOTE_D5, a}, {NOTE_D5, a},  {NOTE_D5, a},
    {NOTE_E5, a},  {NOTE_FS5, c}, {NOTE_D5, a}, {NOTE_FS5, c}, {NOTE_A5, a},
    {NOTE_A5, d},  {NOTE_D5, a},  {NOTE_D5, a}, {NOTE_D5, a},  {NOTE_E5, a},
    {NOTE_FS5, d}, {NOTE_D5, a},  {NOTE_D5, a}, {NOTE_D5, a},  {NOTE_E5, a},
    {NOTE_FS5, d}, {NOTE_E5, a},  {NOTE_E5, a}, {NOTE_E5, a},  {NOTE_D5, a},
    {NOTE_E5, b},  {NOTE_FS5, b}, {NOTE_A5, b}, {NOTE_G5, b},  {NOTE_FS5, b},
    {NOTE_E5, b},

    {NOTE_A5, a},  {NOTE_A5, b},  {NOTE_B5, a}, {NOTE_A5, a},  {NOTE_FS5, a},
    {NOTE_A5, b},  {NOTE_A5, a},  {NOTE_A5, b}, {NOTE_B5, a},  {NOTE_A5, a},
    {NOTE_FS5, a}, {NOTE_E5, b},  {NOTE_D5, e},
};

void setup() {
  pinMode(2, OUTPUT);

  const int melody_length = sizeof(melody) / sizeof(note);

  for (int thisNote = 0; thisNote < melody_length; thisNote++) {
    tone(2, melody[thisNote].frequency);
    delay(melody[thisNote].duration);
  }
  noTone(2);
}

void loop() {}
