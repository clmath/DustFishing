// This is a demonstration on how to use an input device to trigger changes on your neo pixels.
// You should wire a momentary push button to connect from ground to a digital IO pin.  When you
// press the button it will change to a new pixel animation.  Note that you need to press the
// button once to start the first animation!

#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN    5    // Digital IO pin connected to the NeoPixels.

#define PIXEL_COUNT 150

// Parameter 1 = number of pixels in strip,  neopixel stick has 8
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_RGB     Pixels are wired for RGB bitstream
//   NEO_GRB     Pixels are wired for GRB bitstream, correct for neopixel stick
//   NEO_KHZ400  400 KHz bitstream (e.g. FLORA pixels)
//   NEO_KHZ800  800 KHz bitstream (e.g. High Density LED strip), correct for neopixel stick
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);


uint32_t 
Wheel(byte WheelPos);

void
theaterChaseRainbow(uint8_t wait);

void
theaterChase(uint32_t c, uint8_t wait);

void
rainbowCycle(uint8_t wait);

void
rainbow(uint8_t wait);

void
colorWipe(uint32_t c, uint8_t wait);

void
sparkle(int wait);

void
sparkleRainbow(int wait);

void
wave(int wait);

void
startShow(int i);

// Create a temporary strip with 2500 LEDs and reset them.
void 
reset(uint32_t count = 2500) 
{
  Adafruit_NeoPixel reset_strip = Adafruit_NeoPixel(count, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
  reset_strip.begin();
  reset_strip.clear();
  reset_strip.show();
}

void
setup() 
{
  reset();
  strip.begin();
  strip.setBrightness(30);
  strip.show(); // Initialize all pixels to 'off'
}

void
loop()
{
  startShow(12);
}

void
startShow(int i) 
{
  switch(i)
  {
    case 0: colorWipe(strip.Color(0, 0, 0), 50);    // Black/off
            break;
    case 1: colorWipe(strip.Color(255, 0, 0), 50);  // Red
            break;
    case 2: colorWipe(strip.Color(0, 255, 0), 50);  // Green
            break;
    case 3: colorWipe(strip.Color(0, 0, 255), 50);  // Blue
            break;
    case 4: theaterChase(strip.Color(127, 127, 127), 50); // White
            break;
    case 5: theaterChase(strip.Color(127,   0,   0), 50); // Red
            break;
    case 6: theaterChase(strip.Color(  0,   0, 127), 50); // Blue
            break;
    case 7: rainbow(50);
            break;
    case 8: rainbowCycle(50);
            break;
    case 9: theaterChaseRainbow(50);
            break;
    case 10: sparkle(50);
            break;
    case 11: sparkleRainbow(50);
            break;
    case 12: wave(250);
            break;
    default:
            break;
  }
}

/// Fill the dots one after the other with a color.
void
colorWipe(uint32_t c, uint8_t wait) 
{
  for(uint16_t i = 0; i < strip.numPixels(); i++) 
  {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}


void 
wave(int wait)
{
  const int colorsLenth = 10;
  uint32_t colors[colorsLenth] = {0x002CCF, 0x3D00CF, 0x0B11CF, 0x1417C2, 0x1417C2, 0x1472C2, 0x1398B8, 0x6DA5C2, 0x8AB9FF, 0xA8FFEE};
  int ks[24] = {0, 1, 2, 3, 4, 5, 6, 7, 7, 6, 6, 5, 5, 4, 4, 3, 3, 4, 5, 6, 7, 8, 9, 10}; 


  for(int k = 0; k < 24; k++) {
    for(int j = 0; j < colorsLenth; j++)
    {
      for(int i = 0; i < strip.numPixels(); i = i+colorsLenth)
      {
        strip.setPixelColor(i+j, colors[colorsLenth - ((j + ks[k]) % colorsLenth)]);
      }
    }
    strip.show();
    delay(wait);
  }


}

void 
sparkle(int wait)
{
  uint32_t color = 0xFFFFFF;
  for(int i = 0; i < strip.numPixels(); i++)
  {
    if (random(0, 100) < 20) {
      strip.setPixelColor(i, color);
    } else {
      strip.setPixelColor(i, 0);
    }
  }
  strip.show();
  delay(wait);
}

void
sparkleRainbow(int wait)
{
  uint32_t color = 0x1A43AB;
  
  for(uint16_t j = 0; j < 256*5; j++) 
  {
    for(uint16_t i = 0; i < strip.numPixels(); i++)
    {
      if (random(0, 100) < 20) {
        strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    //  strip.setPixelColor(i, Wheel(random(0,255)));
      } else {
        strip.setPixelColor(i, color);
      }
    } 
      
    strip.show();
    delay(wait);
  }
}

void
rainbow(uint8_t wait)
{
  for(uint16_t j = 0; j < 256; j++) 
  {
    for(uint16_t i = 0; i < strip.numPixels(); i++) 
      strip.setPixelColor(i, Wheel((i+j) & 255));

    strip.show();
    delay(wait);
  }
}

/// Slightly different, this makes the rainbow equally distributed throughout.
void
rainbowCycle(uint8_t wait) 
{
  for(uint16_t j = 0; j<256*5; j++)
  { // 5 cycles of all colors on wheel
    for(uint16_t i = 0; i < strip.numPixels(); i++)
      strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
    strip.show();
    delay(wait);
  }
}

/// Theatre-style crawling lights.
void
theaterChase(uint32_t c, uint8_t wait) 
{
  for (int j=0; j<10; j++) //do 10 cycles of chasing
  {
    for (int q=0; q < 3; q++) 
    {
      for (int i=0; i < strip.numPixels(); i=i+3) 
        //turn every third pixel on      
        strip.setPixelColor(i+q, c); 
      strip.show();

      delay(wait);

      for (int i=0; i < strip.numPixels(); i=i+3) {
        strip.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
}

/// Theatre-style crawling lights with rainbow effect.
void 
theaterChaseRainbow(uint8_t wait) 
{
  // Cycle all 256 colors in the wheel.
  for (int j = 0; j < 256; j++) 
  {
    for (int q = 0; q < 3; q++) 
    {
      // Turn every third pixel on.
      for (int i = 0; i < strip.numPixels(); i = i + 3) 
        strip.setPixelColor(i + q, Wheel((i + j) % 255));    
      strip.show();

      delay(wait);

      // Turn every third pixel off.
      for (int i = 0; i < strip.numPixels(); i = i + 3) 
        strip.setPixelColor(i + q, 0);        
    }
  }
}

/// Input a value 0 to 255 to get a color value.
/// The colours are a transition r - g - b - back to r.
uint32_t 
Wheel(byte WheelPos) 
{
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) 
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);

  if(WheelPos < 170) 
  {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }

  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}
