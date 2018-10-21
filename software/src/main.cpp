#include <Arduino.h>
#include "RTC.h"
#include "DCF.h"
#include "Display.h"

const int RTC_CE   = 50;  // Chip Enable
const int RTC_IO   = 51;  // Input/Output
const int RTC_CLK  = 52;  // Serial Clock

const int DCF_PIN  = 53;  // Non-inverted input pin of DCF clock.

RTC realTimeClock = RTC(RTC_CE, RTC_IO, RTC_CLK);
DCF dcf77Clock = DCF(DCF_PIN);
Display display = Display();

void setup() {
  Serial.begin(9600);
  // display.showGrayScale();
  display.renderBitmap();

  uint8_t shift = 4;

  uint8_t a = 0b01000000;
  uint8_t b = a >> 6;
  uint8_t c = b & 0x03;

  uint8_t thispixel = (a >> ((shift-1)*2)) & 0b00000011;

  Serial.println(a);
  Serial.println(b);
  Serial.println(c);
  Serial.println(thispixel);
}

void loop() {
    // Serial.print("RTC: "); Serial.println(realTimeClock.printTime());
    // Serial.print("DCF: "); Serial.println(dcf77Clock.printTime());
    delay(1000);
}