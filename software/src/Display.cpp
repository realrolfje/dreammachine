#include "Display.h"
#include <Arduino.h>
#include <U8glib.h>

const int u8_sck   = 49; // Serial clock
const int u8_mosi  = 50; // Master out, slave in
const int u8_cs    = 51; // Chip select
const int u8_dc    = 52; // Data/Command selector
const int u8_reset = 53; // Reset

Display::Display() {
  u8g = new U8GLIB_NHD27OLED_GR(u8_sck, u8_mosi, u8_cs, u8_dc, u8_reset);
  u8g -> setFont(u8g_font_6x12);
  u8g -> setFontRefHeightExtendedText();
  u8g -> setDefaultForegroundColor();
  u8g -> setFontPosTop();
}
