#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_PIN 8

#define NUM_LEDS 60
#define SUNRISE_STEPS 255

const static uint32_t Color(uint8_t r, uint8_t g, uint8_t b, uint8_t w) {
  return ((uint32_t)w << 24) | ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

class Light {
 public:
  Light();

  void setup();
  void showSkyAt(byte time);
  void off();
  void fullWhite();
  void test();

 private:
  void chase(uint32_t c);
  uint32_t getcolor(byte index);

  // ------------------ Migrated from Arduino playground to get interpolation
  // working

  static const byte sourceXArraySize = 3;
  static const byte targetXArraySize = NUM_LEDS;
  static const byte targetXStepSize = targetXArraySize / (sourceXArraySize - 1);

  static const byte sourceYArraySize = 6;
  static const byte targetYArraySize = SUNRISE_STEPS;
  static const byte targetYStepSize = targetYArraySize / (sourceYArraySize - 1);

  Adafruit_NeoPixel strip =
    Adafruit_NeoPixel(NUM_LEDS, NEOPIXEL_PIN, NEO_GRBW + NEO_KHZ800);

  /*
   * Colors of the sunrise.
   * In this case the horizontal rows are the "x axis" and represent a complete
   * set of colors for the led strip. The vertical list is the "y axis" and
   * represents time.
   * 
   * The first row is the "sun down" color set,
   * the last row is the "sun up" color set.
   */
  const uint32_t fyx[ sourceYArraySize][sourceXArraySize] = {
                    // There is a bug in the interpolation which makes the strip "flash"
                  {   Color(0,0,0,0),    Color(0,0,0,0),   Color(0,0,0,0) },
                  {  Color(50,0,0,0),    Color(30,5,5,0),   Color(30,5,10,0) },
                  {   Color(50,20,10,5),   Color(40,10,0,2),   Color(40,10,20,1) },
                  {   Color(80,20,30,40),  Color(50,30,30,20),  Color(40,20,30,10) },
                  {   Color(10,0,30,80),  Color(10,0,30,80),  Color(10,0,30,80) },
                  {   Color(0,0,0,0),    Color(0,0,0,0),   Color(0,0,0,0) }
  };

  uint32_t getInterpolatedColorAt(byte x, byte y);
  byte getDecimatedIndex(byte arraysize, byte targetsize, byte i);
  byte interpolate(int x1, int z1, int x2, int z2, byte x);
  uint32_t interpolate(int x1, uint32_t z1, int x2, uint32_t z2, byte x);
};

#endif  // LIGHT_H