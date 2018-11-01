#include "DCF.h"
#include <dcf77.h>
#include <Arduino.h>

/*
 * This is here, outside the class defintion because of
 * the way the DCF77_Clock expects the function pointer
 * to be passed in. Maybe there is a better way.
 */
uint8_t dcf_input_pin = 0;
uint8_t dcf_output_pin = 0;

uint8_t sample_input_pin() {
    return digitalRead(dcf_input_pin);
}

void output_handler(const Clock::time_t &decoded_time) {
    Clock::clock_state_t state = DCF77_Clock::get_clock_state();
    if (state == Clock::locked) {
        digitalWrite(dcf_output_pin, !digitalRead(dcf_output_pin));
    }
}

DCF::DCF(uint8_t input_pin) {
    dcf_input_pin = input_pin;

    pinMode(dcf_input_pin, INPUT);
    DCF77_Clock::setup();
    DCF77_Clock::set_input_provider(sample_input_pin);
}

DCF::DCF(uint8_t input_pin, uint8_t output_pin) {
    dcf_input_pin = input_pin;

    pinMode(dcf_input_pin, INPUT);
    DCF77_Clock::setup();
    DCF77_Clock::set_input_provider(sample_input_pin);

    dcf_output_pin = output_pin;
    pinMode(dcf_output_pin, OUTPUT);
    DCF77_Clock::set_output_handler(output_handler);
}

String DCF::quality() {
    uint8_t q = DCF77_Clock::get_overall_quality_factor();
    return String(q, DEC);
}

String DCF::state() {
    Clock::clock_state_t state = DCF77_Clock::get_clock_state();
    
    switch (state) {
        case Clock::useless  : return "useless";  break;
        case Clock::dirty    : return "dirty";    break;
        case Clock::free     : return "free";     break;
        case Clock::unlocked : return "unlocked"; break;
        case Clock::locked   : return "locked";   break;
        case Clock::synced   : return "synced";   break;
        default:
            break;
    }
    return "?";
}

String DCF::printTime(){
    return "nope";
}
