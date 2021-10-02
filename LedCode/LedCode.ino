#define LED_PIN 5
#define LED_TYPE WS2813
#define NUM_SEGMENT_LEDS 14
#define NUMS_TO_DISPLAY 10
#define NUM_SEGMENTS 7



#include <FastLED.h>

CRGB leds[NUM_SEGMENT_LEDS];

const byte lookup_table[NUMS_TO_DISPLAY][NUM_SEGMENTS] = {{1, 1, 1, 0, 1, 1, 1},     // 0
                                                    {0, 0, 1, 0, 0, 0, 1},           // 1
                                                    {0, 1, 1, 1, 1, 1, 0},           // 2
                                                    {0, 1, 1, 1, 0, 1, 1},           // 3
                                                    {1, 0, 1, 1, 0, 0, 1},           // 4
                                                    {1, 1, 0, 1, 0, 1, 1},           // 5
                                                    {1, 1, 0, 1, 1, 1, 1},           // 6
                                                    {0, 1, 1, 0, 0, 0, 1},           // 7
                                                    {1, 1, 1, 1, 1, 1, 1},           // 8
                                                    {1, 1, 1, 1, 0, 1, 1}            // 9
                                                    };

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<LED_TYPE, LED_PIN>(leds, NUM_SEGMENT_LEDS);
}

void showNumber(int number) {
  for(int i = 0; i < NUM_SEGMENTS; i++) {
    if(lookup_table[number][i]) {
      leds[2*i] = CRGB(200, 0, 0);
      leds[2*i + 1] = CRGB(200, 0, 0);
    }
  }
  FastLED.show();
}

void loop() {
  for(int i = 0; i < NUM_SEGMENT_LEDS; i++) {
    leds[i] = CRGB(120, 120, 120);
  }
  FastLED.show();
}
