#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <U8glib.h>

class Display {
    public:
        Display();

    private:
        U8GLIB_NHD27OLED_GR* u8g;
};


#endif // DISPLAY_H