#include "Light.h"

Light::Light() {}

void Light::setup(){
  strip.begin();
  off();
}

void Light::off() {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    uint32_t c = Color(0, 0, 0, 0);
    strip.setPixelColor(i, c);
  }
  strip.show();
}

void Light::fullWhite() {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    //    uint32_t c = getcolor(i * step);
    uint32_t c = Color(0, 0, 0, 255);
    strip.setPixelColor(i, c);
  }
  strip.show();
}

void Light::test() {
  byte x1 = 10;
  byte y1 = 5;

  byte x2 = 100;
  byte y2 = 105;

  for (int x=0; x <= 255; x++){
    byte y = interpolate(x1,y1, x2, y2, x);

    Serial.print(x1); Serial.print(";");
    Serial.print(y1); Serial.print(";");
    Serial.print(x2); Serial.print(";");
    Serial.print(y2); Serial.print(";");
    Serial.print(x); Serial.print(";");
    Serial.println(y);

  }
}


void Light::showSkyAt(byte time){
  for (uint16_t i=0; i < NUM_LEDS_PER_ROW; i++) {
    uint32_t c = getInterpolatedColorAt(i,time);

    /*
     * The LEDs are mounted in a zig-zag pattern,
     * the first row running bottom-to-top, the next
     * row running top-to-bottom, etc.
     */
    for (uint16_t j=0; j< NUM_LED_ROWS; j++) {
      if (j % 2) {
        strip.setPixelColor((j * NUM_LEDS_PER_ROW) + (NUM_LEDS_PER_ROW - i -1), c);
      } else {
        strip.setPixelColor(j * NUM_LEDS_PER_ROW + i, c);
      }
    }
  }

  // for (uint16_t i = 0; i < strip.numPixels(); i++) {
  //   uint32_t c = getInterpolatedColorAt(i,time);
    
  //   // Serial.print("c = Color(50, 0, 0, ");
  //   // Serial.print(b);
  //   // Serial.print("); strip.setPixelColor(");
  //   // Serial.print(i);
  //   // Serial.println(", c);");

  //   strip.setPixelColor(i, c);
  // }
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

  return Color(index, index, index, index);
}

// ------------------ Migrated from Arduino playground to get interpolation working

/*
 * Interprets the matrix fyx as defined in Light.h, as if it
 * was an array of size targetXArraySize and targetYArraySize.
 * Given an x and y in the target space, it lineary interpolates
 * the fyx[][] array to calculate z.
 */
uint32_t Light::getInterpolatedColorAt(byte x, byte y) {
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

  // Interpolate color on yi, x between xi and xj
  uint32_t coloryixi = fyx[yi][xi];
  uint32_t coloryixj = fyx[yi][xj];

  // Serial.print("coloryixi="); Serial.println(coloryixi);
  // Serial.print("coloryixj="); Serial.println(coloryixj);

  uint32_t coloryix = interpolate(xi*targetXStepSize, coloryixi, xj*targetXStepSize, coloryixj, x);

  // Serial.print("coloryix="); Serial.println(coloryix);

  // Interpolate color on xj
  uint32_t coloryjxi = fyx[yj][xi];
  uint32_t coloryjxj = fyx[yj][xj];

  // Serial.print("coloryjxi="); Serial.println(coloryjxi);
  // Serial.print("coloryjxj="); Serial.println(coloryjxj);

  uint32_t coloryjx = interpolate(xi*targetXStepSize, coloryjxi, xj*targetXStepSize, coloryjxj, x);

  // Serial.print("coloryjx="); Serial.println(coloryix);

  // interpolate z on y between xi and xj
  uint32_t coloryx = interpolate(yi*targetYStepSize, coloryix, yj*targetYStepSize, coloryjx, y);

  // Serial.print("Interpolated light at ("); Serial.print(x);
  // Serial.print(","); Serial.print(y);
  // Serial.print(")="); Serial.println(coloryx);

  return coloryx;  
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

  byte z = byte(round(constrain(zf,0,255)));

  // Serial.print("Interpolate: (");
  // Serial.print(x1);  Serial.print(",");  Serial.print(z1);
  // Serial.print(") to (");
  // Serial.print(x2);  Serial.print(",");  Serial.print(z2);
  // Serial.print(") gives (");
  // Serial.print(x);  Serial.print(",");  Serial.print(z);
  // Serial.println(")");

  return z;
}

/*
 * Given two color coordinates (x1, color1) and (x2, color22) and
 * an x between x1 and x2, calculate the color for x.
 */
uint32_t Light::interpolate(int x1, uint32_t color1, int x2, uint32_t color2, byte x) {
  byte w1 = color1 >> 24;
  byte r1 = color1 >> 16;
  byte g1 = color1 >> 8;
  byte b1 = color1;

  byte w2 = color2 >> 24;
  byte r2 = color2 >> 16;
  byte g2 = color2 >> 8;
  byte b2 = color2;

  byte w = interpolate(x1, w1, x2, w2, x);
  byte r = interpolate(x1, r1, x2, r2, x);
  byte g = interpolate(x1, g1, x2, g2, x);
  byte b = interpolate(x1, b1, x2, b2, x);

  return Color(r, g, b, w);
}

