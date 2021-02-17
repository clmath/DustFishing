#include <Adafruit_NeoPixel.h>
#include "Utils.h"
#include "Rainbow.h"


Rainbow::Rainbow(Adafruit_NeoPixel strip) : strip(strip) 
{
}

void
Rainbow::rainbow(uint8_t wait)
{
    for(uint16_t j = 0; j < 12; j++) 
    {
        for(uint16_t i = 0; i < strip.numPixels(); i++) 
        {
            strip.setPixelColor(i, Utils::Wheel((i+j) & 255));
        }

        strip.show();
        delay(wait);
    }
}

// Slightly different, this makes the rainbow equally distributed throughout.
void
Rainbow::rainbowCycle(uint8_t wait)
{
    for(uint16_t j = 0; j<256*5; j++)
    { // 5 cycles of all colors on wheel
        for(uint16_t i = 0; i < strip.numPixels(); i++)
        {
            strip.setPixelColor(i, Utils::Wheel(((i * 256 / strip.numPixels()) + j) & 255));
        }   
       
        strip.show();
        delay(wait);
    }
};