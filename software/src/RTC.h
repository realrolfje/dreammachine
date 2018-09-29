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
        void setTime(uint8_t year, uint8_t month, uint8_t day_of_month,                      uint8_t hour, uint8_t minute, uint8_t second,                    uint8_t day_of_week);

        void setTime(Time t);
        String printTime();

    private:
        DS1302* ds1302;
        String dayAsString(const Time::Day day);
};

#endif // RTC_H


