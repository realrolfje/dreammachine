#include "DCF.h"
#include <dcf77.h>
#include <Arduino.h>

/*
 * This is here, outside the class defintion because of
 * the way the DCF77_Clock expects the function pointer
 * to be passed in. Maybe there is a better way.
 */
uint8_t dcf_input_pin = 0;
uint8_t sample_input_pin() {
    return digitalRead(dcf_input_pin);
}

DCF::DCF(uint8_t input_pin) {
    dcf_input_pin = input_pin;

    pinMode(dcf_input_pin, INPUT);
    DCF77_Clock::setup();
    DCF77_Clock::set_input_provider( sample_input_pin);
}

String DCF::printTime(){
    return "nope";
}
