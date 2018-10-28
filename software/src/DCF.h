#ifndef DCF_H
#define DCF_H

#include <Arduino.h>

class DCF {
    public:
        DCF(uint8_t dcf_input_pin);
        DCF(uint8_t dcf_input_pin, uint8_t dcf_output_pin);
        String printTime();
    private:
};


#endif // DCF_H