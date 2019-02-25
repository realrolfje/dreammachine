#include <Arduino.h>
#include "RTC.h"
#include "DCF.h"
#include "Display.h"
#include "Light.h"

//#define TEST 1

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

#ifndef TEST
  void setup() {
    Serial.begin(9600);
    Serial.println("\n-------\nStarting");
    light.setup();

    // light.test();

    // while(true){};

  }

  void loop() {
    Serial.println("loop");
    light.off();
    delay(1000);

    for(byte t=0; t < SUNRISE_STEPS; t++) {
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
#else
// --------------------------------- Unit tests --------------------------------
// These need to go in a test package but for some unclear reason PlatformIO
// requires a user account for running them, which I am not agreeing with
// for running local tests. So here we go, local tests.
// -----------------------------------------------------------------------------

void setup() {
    // Test interpolation
    Serial.begin(9600);
    Serial.println("---------- tests --------------");
    light.setup();

    Serial.println("Test interpolation")




    // Interpolate: (5,255) to (10,0) gives (9,51)
    // Interpolate: (5,0) to (10,255) gives (9,204)
    // Interpolate: (50,51) to (100,204) gives (52,57)



    Serial.println("---showsky---");
    light.showSkyAt(52);
    Serial.println("---showsky---");
}

void loop(){
 // nothing
}
#endif