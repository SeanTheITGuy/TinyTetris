/* 
 * 
 * Dpad for Arduino TinyTetris 
 * 
 * Designed for https://github.com/AJRussell/Tiny-Tetris
 * 
 * Clumsy code by tobozo (c+) 2016
 * Apologies for coding horror
 * 
 */
 
#ifndef DPADCPP
#define DPADCPP

#include <Arduino.h>

#define LEFT    12
#define RIGHT   13
#define DOWN    0
#define ROTATE  14

static int dpadwarp[5] = { 0,0,0,0,0 };
static volatile int Debounce = 0;
static volatile bool processKey = true;
static volatile int currentPos;

class Dpad
{

  static const int DebounceMax = 10;
  
  public:

  static int getPos() {
    delay(150);
    if(digitalRead(LEFT) == LOW) return 1;
    if(digitalRead(RIGHT) == LOW) return 2;
    if(digitalRead(DOWN) == LOW) return 3;
    if(digitalRead(ROTATE) == LOW) return 4;
    return 0;       
  }

    static boolean DoDebounce() {
      Debounce++;
      if(Debounce > DebounceMax) {
        return true;
      }
      return false;
    }

    static int setAccel(int acceleration, int offset) {
      if(processKey) {
        dpadwarp[currentPos] = millis();
      }
      if(millis() < dpadwarp[currentPos] + offset) {
        processKey = false;
      } else {
        processKey = true;
        acceleration = acceleration + 70;
        if (acceleration > offset) {
          acceleration = offset;
        }
      }
      return acceleration;
    }

  private:
  
    static int getPosition(int pin) {
      return analogRead(pin);
    }
};

#endif



 
