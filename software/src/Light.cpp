#include "Light.h"

Light::Light() {}

void Light::setup(){
  strip.setBrightness(255);
  strip.begin();
  off();
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

void Light::test() {
uint32_t c;
c = strip.Color(50, 0, 0, 0  ); strip.setPixelColor(0, c);
c = strip.Color(0, 0, 0, 25 ); strip.setPixelColor(1, c);
c = strip.Color(0, 0, 0, 51 ); strip.setPixelColor(2, c);
c = strip.Color(0, 0, 0, 76 ); strip.setPixelColor(3, c);
c = strip.Color(0, 0, 0, 101); strip.setPixelColor(4, c);
c = strip.Color(0, 0, 0, 127); strip.setPixelColor(5, c);
c = strip.Color(0, 0, 0, 153); strip.setPixelColor(6, c);
c = strip.Color(0, 0, 0, 178); strip.setPixelColor(7, c);
c = strip.Color(0, 0, 0, 204); strip.setPixelColor(8, c);
c = strip.Color(0, 0, 0, 229); strip.setPixelColor(9, c);
  strip.show();
}


void Light::showSkyAt(byte time){
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    uint8_t b = getInterpolatedZAt(i,time);
    uint32_t c = strip.Color(0, 0, 0, b);
    
    // Serial.print("c = strip.Color(50, 0, 0, ");
    // Serial.print(b);
    // Serial.print("); strip.setPixelColor(");
    // Serial.print(i);
    // Serial.println(", c);");

    // strip.setPixelColor(i, strip.Color(0, 0, 0, c));
    strip.setPixelColor(i, c);
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
  // Serial.print("x="); Serial.println(x);
  // Serial.print("y="); Serial.println(y);

  // Determine the two y coordinates to interpolate between
  byte yj = getDecimatedIndex(sourceYArraySize, targetYArraySize, y);
  byte yi = yj-1;

  // Serial.print("Source Y arrayzise="); Serial.println(sourceYArraySize);
  // Serial.print("Target Y arrayzise="); Serial.println(targetYArraySize);

  // Serial.print("yi="); Serial.println(yi);
  // Serial.print("yj="); Serial.println(yj);

  // Determine the two x coordinates to interpolate between
  byte xj = getDecimatedIndex(sourceXArraySize, targetXArraySize, x);
  byte xi = xj-1;

  // Serial.print("Source X arrayzise="); Serial.println(sourceXArraySize);
  // Serial.print("Target X arrayzise="); Serial.println(targetXArraySize);

  // Serial.print("xi="); Serial.println(xi);
  // Serial.print("xj="); Serial.println(xj);

  // Interpolate z on yi, x between xi and xj
  byte zyixi = fyx[yi][xi];
  byte zyixj = fyx[yi][xj];

  // Serial.print("zyixi="); Serial.println(zyixi);
  // Serial.print("zyixj="); Serial.println(zyixj);

  byte zyix = interpolate(xi*targetXStepSize, zyixi, xj*targetXStepSize, zyixj, x);

  // Serial.print("zyix="); Serial.println(zyix);

  // Interpolate z on xj
  byte zyjxi = fyx[yj][xi];
  byte zyjxj = fyx[yj][xj];

  // Serial.print("zyjxi="); Serial.println(zyjxi);
  // Serial.print("zyjxj="); Serial.println(zyjxj);

  byte zyjx = interpolate(xi*targetXStepSize, zyjxi, xj*targetXStepSize, zyjxj, x);

  // Serial.print("zyjx="); Serial.println(zyix);

  // interpolate z on y between xi and xj
  byte zyx = interpolate(yi*targetYStepSize, zyix, yj*targetYStepSize, zyjx, y);

  // Serial.print("Interpolated light at ("); Serial.print(x);
  // Serial.print(","); Serial.print(y);
  // Serial.print(")="); Serial.println(zyx);

  return zyx;  
}

/*
 * Calculates the index in the short array of size "arraysize"
 * just above the given "i" if that were an index in a byte
 * array of "targetsize".
 */
byte Light::getDecimatedIndex(byte arraysize, byte targetsize, byte i) {
  byte stepsize = (targetsize) / (arraysize - 1);
  byte xx = i / stepsize;
  return min(arraysize - 1, xx + 1);
}

/*
 * Given two points (x1,z1) and (x2,z2) and
 * an x between x1 and x2, calculate z for x.
 */
byte Light::interpolate(int x1, int z1, int x2, int z2, byte x) {
  float zf = z1 + float(x - x1) * (z2 - z1) / (x2 - x1);
  byte z = byte(round(zf));

  // Serial.print("Interpolate: (");
  // Serial.print(x1);  Serial.print(",");  Serial.print(z1);
  // Serial.print(") to (");
  // Serial.print(x2);  Serial.print(",");  Serial.print(z2);
  // Serial.print(") gives (");
  // Serial.print(x);  Serial.print(",");  Serial.print(z);
  // Serial.println(")");

  return z;
}
