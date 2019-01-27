#include <Arduino.h>
#include "RTC.h"
#include "DCF.h"
#include "Display.h"
#include "Light.h"

const int RTC_CE   = 50;  // Chip Enable
const int RTC_IO   = 51;  // Input/Output
const int RTC_CLK  = 52;  // Serial Clock

const int DCF_PIN  = 22;  // Non-inverted input pin of DCF clock.
const int DCF_OUT  = 23;  // Second pulse from decoded DCF clock signal.

//RTC realTimeClock = RTC(RTC_CE, RTC_IO, RTC_CLK);
//DCF dcf77Clock = DCF(DCF_PIN, DCF_OUT);
//DCF dcf77Clock = DCF(DCF_PIN);
//Display display = Display();
Light light = Light();

void setup() {
  Serial.begin(9600);
  Serial.println("Starting");

}

void loop() {
  Serial.println("loop");
  light.off();
  delay(1000);

  for(byte t=0; t < SUNRISE_STEPS; t++) {
    Serial.print(t);
    Serial.print(" ");
    
    light.showSkyAt(t);
    delay(25);
  }
    // Serial.print("RTC: "); Serial.println(realTimeClock.printTime());
    // Serial.print("DCF: "); Serial.println(dcf77Clock.printTime());

  // char quality[10];
  // dcf77Clock.quality().toCharArray(quality, sizeof(quality));

  // char state[20];
  // dcf77Clock.state().toCharArray(state, sizeof(state));

  // Serial.print("Quality: ");
  // Serial.println(dcf77Clock.quality());

  // Serial.print("State: ");
  // Serial.println(dcf77Clock.state());

  // dcf77Clock.printTime();
  // delay(2000);

//  display.displayTime(quality, state);

//  delay(5000);
}