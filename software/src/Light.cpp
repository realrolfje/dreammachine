#include "Light.h"
#include <Adafruit_NeoPixel.h>

#define NEOPIXEL_PIN 8

#define NUM_LEDS 60

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, NEOPIXEL_PIN, NEO_GRBW + NEO_KHZ800);

Light::Light() {
  Serial.println("Setup led strip");
  pinMode(NEOPIXEL_PIN, OUTPUT);
  strip.setBrightness(100);
  strip.begin();
  strip.setPixelColor(7, 127, 127, 127, 127);
  strip.show(); // Initialize all pixels to 'off'
}

void Light::fullWhite() {
    Serial.println("Full white");
    while(true){
        chase(strip.Color(255, 0, 0, 0)); // Red
        chase(strip.Color(0, 255, 0, 0)); // Green
        chase(strip.Color(0, 0, 255, 0)); // Blue
        chase(strip.Color(0, 0, 0, 255)); // Wite


        // for(uint16_t i=0; i<strip.numPixels(); i++) {
        //     strip.setPixelColor(i, strip.Color(127,127,127, 255 ) );
        // }
        strip.show();
    }
}


 void Light::chase(uint32_t c) {
  int trail =20;   
  for(uint16_t i=0; i<strip.numPixels()+trail; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i-trail, 0); // Erase pixel a few steps back
      strip.show();
      delay(25);
  }
}
