#include <Arduino.h>
#include "RTC.h"
#include "DCF.h"

const int RTC_CE   = 50;  // Chip Enable
const int RTC_IO   = 51;  // Input/Output
const int RTC_CLK  = 52;  // Serial Clock

const int DCF_PIN  = 53;  // Non-inverted input pin of DCF clock.

RTC realTimeClock = RTC(RTC_CE, RTC_IO, RTC_CLK);
DCF dcf77Clock = DCF(DCF_PIN);

void setup() {
  Serial.begin(9600);
}

void loop() {
    Serial.print("RTC: "); Serial.println(realTimeClock.printTime());
    Serial.print("DCF: "); Serial.println(dcf77Clock.printTime());
    delay(1000);
}