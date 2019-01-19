#ifndef LIGHT_H
#define LIGHT_H

#include <Arduino.h>

class Light {
    public:
        Light();

        void setup();
        void fullWhite();
    private:
        void chase(uint32_t c);
};

#endif // LIGHT_H