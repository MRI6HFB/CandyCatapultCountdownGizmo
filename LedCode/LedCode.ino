#define LED_PIN 5

#include <FastLED.h>

CRGB leds[100];

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<WS2813, LED_PIN>(leds, 1);
}

void loop() {
  for(int i = 0; i < 100; i++) {
    leds[i] = CHSV(120, 120, 120);
  }
  FastLED.show();
}
