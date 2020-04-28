#ifndef UTIL_H
#define UTIL_H
#include "tones.h"

/* Back to the Future Theme song (Notes and durations in a 2D array)*/
const int bttf[2][21] = {{
                  NOTE_G5, NOTE_C5,
                  NOTE_FS5,REST,NOTE_G5,NOTE_A5,
                  NOTE_G5,NOTE_E5,NOTE_C5,NOTE_FS5,NOTE_G5,NOTE_A5,
                  NOTE_G5,NOTE_D5, NOTE_G5,NOTE_D6,
                  NOTE_D6,NOTE_CS6,NOTE_B5,NOTE_CS6,
                  NOTE_D6},
                  {
                  2, 2,
                  3, 8, 14, 14,
                  5, 5, 5, 6, 14, 14,
                  4, 4, 4, 4,
                  2, 6, 14, 14,
                  1}};

/* Character definitions */
#define SOLID 0
#define DOWN_ARROW 1
#define LEFT_ARROW 2
#define RIGHT_ARROW 3
#define DOUBLE_ARROW 4
#define RUN_MAN 5

byte solid[] = {
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111,
  B11111
};
byte down[] = {
  B00000,
  B01110,
  B01110,
  B01110,
  B11111,
  B01110,
  B00100,
  B00000
};
byte right[] = {
  B00000,
  B00000,
  B00100,
  B11110,
  B11111,
  B11110,
  B00100,
  B00000
};
byte left[] = {
  B00000,
  B00000,
  B00100,
  B01111,
  B11111,
  B01111,
  B00100,
  B00000
};

byte bi[] = {
  B00100,
  B01100,
  B11111,
  B01100,
  B00110,
  B11111,
  B00110,
  B00100
};

byte run[] = {
  B00011,
  B00011,
  B11100,
  B10111,
  B00101,
  B01110,
  B01010,
  B10010
};

// RGB color code struct package
typedef struct RGB
{
    // Red
    unsigned char r;
    // Green
    unsigned char g;
    // Blue
    unsigned char b;
} RGB;

/* RGB predefined colors */
#define OFF     RGB {0, 0, 0}
#define RED     RGB {255, 0, 0}
#define GREEN   RGB {0, 255, 0}
#define BLUE    RGB {0, 0, 255}
#define VIOLET  RGB {255,0,255}
#define CYAN    RGB {0,255,255}
#define YELLOW  RGB {255,255,0}
#define ORANGE  RGB {255,69,0}
#define SKYBLUE RGB {30,144,255}
#define PURPLE RGB {128, 0, 128}
#define WHITE   RGB {255, 255, 255}


#endif