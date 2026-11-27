#include <Arduino.h>
#include <avr/wdt.h>
#include "FastLED.h"

namespace RGBConfig {
const uint8_t PIN_LED = 4;
const uint8_t NUM_LEDS = 1;
const uint8_t BRIGHTNESS = 30;
const uint16_t COLOR_HOLD_MS = 1000;
}

CRGB g_leds[RGBConfig::NUM_LEDS];

void safeDelay(uint16_t ms) {
  for (uint16_t i = 0; i < ms; ++i) {
    delay(1);
    wdt_reset();
  }
}

void showColor(const CRGB& color, const __FlashStringHelper* name) {
  g_leds[0] = color;
  FastLED.show();
  Serial.print(F("RGB color: "));
  Serial.println(name);
  safeDelay(RGBConfig::COLOR_HOLD_MS);
}

void setup() {
  wdt_enable(WDTO_2S);

  Serial.begin(9600);

  FastLED.addLeds<NEOPIXEL, RGBConfig::PIN_LED>(g_leds, RGBConfig::NUM_LEDS);
  FastLED.setBrightness(RGBConfig::BRIGHTNESS);
  FastLED.clear(true);

  Serial.println(F("RGB lesson ready"));
}

void loop() {
  wdt_reset();

  showColor(CRGB::Red, F("Red"));
  showColor(CRGB::Green, F("Green"));
  showColor(CRGB::Blue, F("Blue"));
  showColor(CRGB::Yellow, F("Yellow"));
  showColor(CRGB::Cyan, F("Cyan"));
  showColor(CRGB::Violet, F("Violet"));
  showColor(CRGB::White, F("White"));
  showColor(CRGB::Black, F("Off"));
}
