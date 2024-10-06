//***************************************************************
// Project Friday
// Device Type: Arduino Nano
// Device Name: nano_01
// General Description: Lighting Control
//***************************************************************

#include "FastLED.h"

#define RING_LED_TYPE    WS2812  //WS2811, WS2812, WS2812B
#define STRIP_LED_TYPE WS2812B

#define RING_COLOR_ORDER RGB
#define STRIP_COLOR_ORDER RGB

#define RING_DATA_PIN 8
#define LEFT_STRIP_DATA_PIN 7
#define RIGHT_STRIP_DATA_PIN 6

#define RING_NUM_LEDS 24 // Uncomment for 24 LED NeoPixel Ring
//#define RING_NUM_LEDS 35 // Uncomment for 35 LED NeoPixel Ring
#define STRIP_NUM_LEDS 8

#define BRIGHTNESS 100
CRGB RING_LEDS[RING_NUM_LEDS];
CRGB STRIP_LEDS[STRIP_NUM_LEDS];

static float pulseSpeed = 0.9;  // Larger value gives faster pulse.

#define POT_PIN A0

// NeoPixel Color Map (Color Mode must be "RGB"):
// Yellow: 65
// Orange: 80
// Red: 100
// Hot Pink: 120
// Violet: 140
// Blue: 160
// Dull Blue: 180
// Sky Blue: 200
// Aqua: 220
// Pale Green: 240
// Green: 260
// Yellow Green: 280
// Yellow: 320

uint8_t sat = 250; // Do Not Edit

float pulseValueMin = 180.0;  // Pulse minimum value (Should be less then pulseValueMax).
float pulseValueMax = 240.0;  // Pulse maximum value (Should be larger then pulseValueMin).

float val = pulseValueMin;  // Do Not Edit
static float pulseValueDelta = (pulseValueMax - pulseValueMin) / 2.35040238;  // Do Not Edit


//---------------------------------------------------------------
void setup(){
  Serial.begin(57600);  // Allows serial monitor output (check baud rate)
  delay(2000);  // Startup delay
  FastLED.addLeds<RING_LED_TYPE, RING_DATA_PIN, RING_COLOR_ORDER>(RING_LEDS, RING_NUM_LEDS);
  FastLED.addLeds<STRIP_LED_TYPE, LEFT_STRIP_DATA_PIN, STRIP_COLOR_ORDER>(STRIP_LEDS, STRIP_NUM_LEDS);
  FastLED.addLeds<STRIP_LED_TYPE, RIGHT_STRIP_DATA_PIN, STRIP_COLOR_ORDER>(STRIP_LEDS, STRIP_NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();
  FastLED.show();
  Serial.println("////////////////////////////");
  Serial.println("//////////////////////////// \n");
  Serial.println("Project: Friday");
  Serial.println("Device: nano_01");
  Serial.println("Firmware: nano_01.ino");
  Serial.println("Setup complete. \n");
  Serial.println("////////////////////////////");
  Serial.println("////////////////////////////");
}


//---------------------------------------------------------------
void loop(){
  int potValue = analogRead(POT_PIN);
  int hue = map(potValue, 0, 1023, 65, 320);

  Serial.println(hue);
  
  float dV = ((exp(sin(pulseSpeed * millis()/2000.0*PI)) -0.36787944) * pulseValueDelta);
  val = pulseValueMin + dV;

  for (int i = 0; i < RING_NUM_LEDS; i++) {
    RING_LEDS[i] = CHSV(hue, sat, val);
    STRIP_LEDS[i] = CHSV(hue, sat, val);

    // You can experiment with commenting out these dim8_video lines
    // to get a different sort of look.
    RING_LEDS[i].r = dim8_video(RING_LEDS[i].r);
    RING_LEDS[i].g = dim8_video(RING_LEDS[i].g);
    RING_LEDS[i].b = dim8_video(RING_LEDS[i].b);

    // You can experiment with commenting out these dim8_video lines
    // to get a different sort of look.
    STRIP_LEDS[i].r = dim8_video(STRIP_LEDS[i].r);
    STRIP_LEDS[i].g = dim8_video(STRIP_LEDS[i].g);
    STRIP_LEDS[i].b = dim8_video(STRIP_LEDS[i].b);
  }

  FastLED.show();
   
} // end_main_loop
