//***************************************************************
// Breathing effect
// Color shifts from hueA to hueB as it pulses.
//
// Set A and B to the same hue if you don't want the color to
// change.  Saturation for the high and low can also be set.
//
//***************************************************************

#include "FastLED.h"
#define RING_LED_TYPE    WS2812  //WS2811, WS2812, WS2812B
#define COLOR_ORDER RGB
#define RING_DATA_PIN 8 
#define RING_NUM_LEDS 24 // Uncomment for 24 LED NeoPixel Ring
//#define RING_NUM_LEDS 35 // Uncomment for 35 LED NeoPixel Ring
#define BRIGHTNESS 100
CRGB RING_LEDS[RING_NUM_LEDS];

static float pulseSpeed = 0.9;  // Larger value gives faster pulse.

// 24 & 35 LED NeoPixel Ring Color Map:
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

uint8_t hueA = 80;  // Start hue at valueMin. This sets the starting color.
uint8_t satA = 250;  // Start saturation at valueMin. This sets the starting color saturation.
float valueMin = 180.0;  // Pulse minimum value (Should be less then valueMax).
//float valueMin = 240.0; // Uncomment to stop from pulsing

uint8_t hueB = 80;  // End hue at valueMax. This sets the ending color.
uint8_t satB = 250;  // End saturation at valueMax. This sets the ending color saturation.
float valueMax = 240.0;  // Pulse maximum value (Should be larger then valueMin).

uint8_t hue = hueA;  // Do Not Edit
uint8_t sat = satA;  // Do Not Edit
float val = valueMin;  // Do Not Edit
uint8_t hueDelta = hueA - hueB;  // Do Not Edit
static float delta = (valueMax - valueMin) / 2.35040238;  // Do Not Edit


//---------------------------------------------------------------
void setup(){
  Serial.begin(57600);  // Allows serial monitor output (check baud rate)
  delay(2000);  // Startup delay
  FastLED.addLeds<RING_LED_TYPE, RING_DATA_PIN, COLOR_ORDER>(RING_LEDS, RING_NUM_LEDS);
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
  float dV = ((exp(sin(pulseSpeed * millis()/2000.0*PI)) -0.36787944) * delta);
  val = valueMin + dV;
  hue = map(val, valueMin, valueMax, hueA, hueB);  // Map hue based on current val
  sat = map(val, valueMin, valueMax, satA, satB);  // Map sat based on current val

  for (int i = 0; i < RING_NUM_LEDS; i++) {
    RING_LEDS[i] = CHSV(hue, sat, val);

    // You can experiment with commenting out these dim8_video lines
    // to get a different sort of look.
    RING_LEDS[i].r = dim8_video(RING_LEDS[i].r);
    RING_LEDS[i].g = dim8_video(RING_LEDS[i].g);
    RING_LEDS[i].b = dim8_video(RING_LEDS[i].b);
  }

  FastLED.show();
  if (Serial.available() > 0) {
    int msg = Serial.read() - '0';
    Serial.print("Command received: ");
    Serial.println(msg);
  };
   
} // end_main_loop
