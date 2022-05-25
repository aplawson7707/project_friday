#include "FastLED.h"
#define LED_TYPE WS2812
#define LED_PIN 8 
#define NUM_LEDS 24
#define COLOR_ORDER GRB

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.clear();
}

void loop() {
  for(int dot = 0; dot < NUM_LEDS; dot++) {
    leds[dot] = CRGB::Green;
    FastLED.show();
    leds[dot] = CRGB::Black;
    delay(30);
    Serial.println(dot);
  }
}
