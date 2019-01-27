#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_PIN 8

#define NUM_LEDS 60
#define SUNRISE_STEPS 30


class Light {
 public:
  Light();

  void setup();
  void showSkyAt(byte time);
  void off();
  void fullWhite();

 private:
  void chase(uint32_t c);
  uint32_t getcolor(byte index);

  // ------------------ Migrated from Arduino playground to get interpolation
  // working

  static const byte sourceXArraySize = 3;
  static const byte targetXArraySize = NUM_LEDS;
  static const byte targetXStepSize = targetXArraySize / (sourceXArraySize - 1);

  static const byte sourceYArraySize = 3;
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
  const byte fyx[ sourceYArraySize][sourceXArraySize] = {
                    // There is a bug in the interpolation which makes the strip "flash"
                  {  0, 0,0},
                  { 0,0,254},
                  {254,254,254}
  };

  byte getInterpolatedZAt(byte x, byte y);
  byte getDecimatedIndex(byte arraysize, byte targetsize, byte i);
  byte interpolate(int x1, int z1, int x2, int z2, byte x);
};

#endif  // LIGHT_H