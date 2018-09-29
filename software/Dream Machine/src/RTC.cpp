#include "RTC.h"
#include <DS1302.h>
#include <Arduino.h>

RTC::RTC(int cePin, int ioPin, int clkPin) {    
    ds1302 = new DS1302(cePin, ioPin, clkPin);
}

String RTC::printTime() {
  Time t = ds1302 -> time();

  const String day = dayAsString(t.day);
  char buf[50];
  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d",
           day.c_str(),
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);
  return buf;
}

String RTC::dayAsString(const Time::Day day) {
  switch (day) {
    case Time::kSunday: return "Sunday";
    case Time::kMonday: return "Monday";
    case Time::kTuesday: return "Tuesday";
    case Time::kWednesday: return "Wednesday";
    case Time::kThursday: return "Thursday";
    case Time::kFriday: return "Friday";
    case Time::kSaturday: return "Saturday";
  }
  return "(unknown day)";
}



