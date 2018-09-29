#include <Arduino.h>
#include "RTC.h"

const int RTC_CE   = 50;  // Chip Enable
const int RTC_IO   = 51;  // Input/Output
const int RTC_CLK  = 52;  // Serial Clock

// Create a DS1302 object.
RTC realTimeClock = RTC(RTC_CE, RTC_IO, RTC_CLK);


void setup() {
  Serial.begin(9600);

//   rtc.writeProtect(false);
//   rtc.halt(false);
//   Time t(2019, 9, 29, 17, 03, 00, Time::kSunday);
//   rtc.time(t);
}

void loop() {
    Serial.println(realTimeClock.printTime());
    delay(1000);
}