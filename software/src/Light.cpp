#include "Light.h"

Light::Light() {
  strip.setBrightness(255);
  strip.begin();
}

void Light::off() {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    uint32_t c = strip.Color(0, 0, 0, 0);
    strip.setPixelColor(i, c);
  }
  strip.show();
}

void Light::fullWhite() {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    //    uint32_t c = getcolor(i * step);
    uint32_t c = strip.Color(0, 0, 0, 255);
    strip.setPixelColor(i, c);
  }
  strip.show();
}

void Light::showSkyAt(byte time){
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    byte c = getInterpolatedZAt(i,time);
    
    strip.setPixelColor(i, strip.Color(0, 0, 0, c));
  }
  strip.show();
}

/*
 * Returns a packed 32-bit WRGB color for the sunrise.
 * The sun "rises" in 256 steps:
 * 0 - Sun down (no light)
 * 255 - Sun up (full sunlight)
 */
uint32_t Light::getcolor(byte index) {
  uint8_t r = round(255 * (1 + cos(double(PI / 255) * index)) / 2);
  uint8_t g = 0;
  uint8_t b = 0;
  uint8_t w = round(255 * (1 + cos(double(PI / 255) * index - 100)) / 2);

  return strip.Color(index, index, index, index);
}

// ------------------ Migrated from Arduino playground to get interpolation working

/*
 * Interprets the matrix fyx as defined in Light.h, as if it
 * was an array of size targetXArraySize and targetYArraySize.
 * Given an x and y in the target space, it lineary interpolates
 * the fyx[][] array to calculate z.
 */
byte Light::getInterpolatedZAt(byte x, byte y) {
  // Determine the two y coordinates to interpolate between
  byte yj = getDecimatedIndex(sourceYArraySize, targetYArraySize, y);
  byte yi = yj-1;

  // Determine the two x coordinates to interpolate between
  byte xj = getDecimatedIndex(sourceXArraySize, targetXArraySize, x);
  byte xi = xj-1;

  // Interpolate z on yi, x between xi and xj
  byte zyixi = fyx[yi][xi];
  byte zyixj = fyx[yi][xj];

  byte zyix = interpolate(xi*targetXStepSize, zyixi, xj*targetXStepSize, zyixj, x);

  // Interpolate z on xj
  byte zyjxi = fyx[yj][xi];
  byte zyjxj = fyx[yj][xj];

  byte zyjx = interpolate(xi*targetXStepSize, zyjxi, xj*targetXStepSize, zyjxj, x);

  // interpolate z on y between xi and xj
  byte zyx = interpolate(yi*targetYStepSize, zyix, yj*targetYStepSize, zyjx, y);
  return zyx;  
}

/*
 * Calculates the index in the short array of size "arraysize"
 * just above the given "i" if that were an index in a byte
 * array of "targetsize".
 */
byte Light::getDecimatedIndex(byte arraysize, byte targetsize, byte i) {
  byte stepsize = (targetsize - 1) / (arraysize - 1);
  byte xx = i / stepsize;
  return min(arraysize - 1, xx + 1);
}

/*
 * Given two points (x1,z1) and (x2,z2) and
 * an x between x1 and x2, calculate z for x.
 */
byte Light::interpolate(int x1, int z1, int x2, int z2, byte x) {
  float zf = z1 + float(x - x1) * (z2 - z1) / (x2 - x1);
  return round(zf);
}
