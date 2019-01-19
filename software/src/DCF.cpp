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
    bool signal = digitalRead(dcf_input_pin);
    digitalWrite(13, signal);
//    digitalWrite(dcf_output_pin, signal);
    return signal;
}

void output_handler(const Clock::time_t &decoded_time) {
//    Clock::clock_state_t state = DCF77_Clock::get_clock_state();
//    if (state == Clock::locked) {
        digitalWrite(dcf_output_pin, !digitalRead(dcf_output_pin));
//    }
}

DCF::DCF(uint8_t input_pin) {
    dcf_input_pin = input_pin;

    pinMode(dcf_input_pin, INPUT);
    pinMode(13, OUTPUT);

    DCF77_Clock::setup();
    DCF77_Clock::set_input_provider(sample_input_pin);
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
    DCF77_Clock::debug();

    // Clock::time_t time;
    // DCF77_Clock::get_current_time(time);
    // DCF77_Clock::print(time);
    return "printed";
}
