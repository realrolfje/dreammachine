/*
 * Abstracts the battery backed real time clock.
 */
#ifndef RTC_H
#define RTC_H

#include <DS1302.h>
#include <Arduino.h>

class RTC {
    public:
        RTC(int cePin, int ioPin, int clkPin);
        String printTime();

    private:
        DS1302* ds1302;
        String dayAsString(const Time::Day day);
};

#endif // RTC_H


