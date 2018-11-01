#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <U8glib.h>

class Display {
    public:
        Display();

        void showGrayScale();
        void renderBitmap();
        void displayTime(char* time, char* test);

    private:
        U8GLIB_NHD27OLED_GR* u8g;
};


#endif // DISPLAY_H