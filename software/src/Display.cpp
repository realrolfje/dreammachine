#include "Display.h"
#include <Arduino.h>
#include <U8glib.h>

const int u8_sck   = 49; // Serial clock
const int u8_mosi  = 50; // Master out, slave in
const int u8_cs    = 51; // Chip select
const int u8_dc    = 52; // Data/Command selector
const int u8_reset = 53; // Reset

const uint8_t V[] PROGMEM = {
   0b01000000, 0b00000001,
   0b10010000, 0b00000110,
   0b11100100, 0b00011011,
   0b11111001, 0b01101111
};

Display::Display() {
  u8g = new U8GLIB_NHD27OLED_GR(u8_sck, u8_mosi, u8_cs, u8_dc, u8_reset);
  u8g -> begin();
  u8g -> setFont(u8g_font_6x12);
  u8g -> setFontRefHeightExtendedText();
  u8g -> setDefaultForegroundColor();
  u8g -> setFontPosTop();
  u8g -> setContrast(255);
}

void Display::showGrayScale() {
    u8g -> firstPage();
    do {
        for(uint8_t i = 0; i < 20; i++) {
            u8g -> setColorIndex(i);
            u8g -> drawBox(5 + (5*i),5,5,5);
            u8g -> drawBox(5 + (5*i),15,5,5);
        }
    } while (u8g -> nextPage());
}

void Display::displayTime(char* time) {
    u8g -> setFont(u8g_font_fub35n);
    u8g -> setFontPosTop();
    u8g -> firstPage();
    do {
        u8g -> drawStr( 0, 0, time);
    } while (u8g -> nextPage());
}

void Display::renderBitmap() {
    u8g -> firstPage();
    do {
        for(uint8_t y = 0; y < 4; y++) {
            for(uint8_t x = 0; x < 2; x++) {
//                uint8_t pixels = V[y*2 + x];
                uint8_t pixels = pgm_read_byte(V + y*2 + x);

                for(uint8_t shift = 4; shift > 0; shift--){
                    uint8_t thispixel = (pixels >> ((shift-1)*2)) & 0b00000011;
                    u8g -> setColorIndex(thispixel);
                    u8g -> drawPixel(x*4 + (4 - shift),y);
                }
            }
        }
    } while (u8g -> nextPage());
}