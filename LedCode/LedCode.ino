#define LED_PIN 5
#define LED_TYPE WS2813
#define NUM_SEGMENT_LEDS 14

#include <FastLED.h>

CRGB leds[100];

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<LED_TYPE, LED_PIN>(leds, NUM_SEGMENT_LEDS);
}

void loop() {
  for(int i = 0; i < NUM_SEGMENT_LEDS; i++) {
    leds[i] = CHSV(120, 120, 120);
  }
  FastLED.show();
}
