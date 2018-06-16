#ifndef RAINBOW_H
#define RAINBOW_H
#include <Adafruit_NeoPixel.h>
#include "Utils.h"

class Rainbow {
    public:
        Rainbow(Adafruit_NeoPixel strip);

        void
        rainbow(uint8_t wait);
        
        void
        rainbowCycle(uint8_t wait);
        
    private:
        Adafruit_NeoPixel strip;
};


#endif // RAINBOW_H