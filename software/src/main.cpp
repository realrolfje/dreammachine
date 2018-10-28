#include <Arduino.h>
#include "RTC.h"
#include "DCF.h"
#include "Display.h"

const int RTC_CE   = 50;  // Chip Enable
const int RTC_IO   = 51;  // Input/Output
const int RTC_CLK  = 52;  // Serial Clock

const int DCF_PIN  = 22;  // Non-inverted input pin of DCF clock.
const int DCF_OUT  = 23;  // Second pulse from decoded DCF clock signal.

RTC realTimeClock = RTC(RTC_CE, RTC_IO, RTC_CLK);
DCF dcf77Clock = DCF(DCF_PIN, DCF_OUT);
Display display = Display();

void setup() {
  Serial.begin(9600);

}

void loop() {
    // Serial.print("RTC: "); Serial.println(realTimeClock.printTime());
    // Serial.print("DCF: "); Serial.println(dcf77Clock.printTime());
  display.displayTime("21:44");
  delay(1000);
  display.displayTime("22 45");
  delay(1000);
  display.displayTime("23:46");
  delay(1000);
  display.displayTime("24 47");
  delay(1000);
}