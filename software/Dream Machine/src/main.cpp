#include <Arduino.h>
#include <DS1302.h>

const int RTC_CE   = 50;  // Chip Enable
const int RTC_IO   = 51;  // Input/Output
const int RTC_CLK  = 52;  // Serial Clock

// Create a DS1302 object.
DS1302 rtc(RTC_CE, RTC_IO, RTC_CLK);

String dayAsString(const Time::Day day) {
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

void printTime() {
  // Get the current time and date from the chip.
  Time t = rtc.time();

  // Name the day of the week.
  const String day = dayAsString(t.day);

  // Format the time and date and insert into the temporary buffer.
  char buf[50];
  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d %02d:%02d:%02d",
           day.c_str(),
           t.yr, t.mon, t.date,
           t.hr, t.min, t.sec);

  // Print the formatted string to serial so we can see the time.
  Serial.println(buf);
}

void setup() {
  Serial.begin(9600);

  rtc.writeProtect(false);
  rtc.halt(false);
  Time t(2013, 9, 22, 1, 38, 50, Time::kSunday);
  rtc.time(t);
}

void loop() {
    printTime();
    delay(1000);
}