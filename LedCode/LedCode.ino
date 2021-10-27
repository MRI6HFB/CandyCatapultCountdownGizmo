#define LED_PIN 5
#define BUTTON_PIN 11
#define LED_TYPE WS2813
#define NUM_SEGMENT_LEDS 14
#define NUMS_TO_DISPLAY 10
#define NUM_SEGMENTS 7
#define COUNTNUM 9


#include <FastLED.h>

CRGB leds[NUM_SEGMENT_LEDS];
CRGB side1_leds[NUM_SIDE_LEDS];
CRGB side2_leds[NUM_SIDE_LEDS];

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
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  FastLED.addLeds<LED_TYPE, LED_PIN>(leds, NUM_SEGMENT_LEDS);
}

void showNumber(int number) {
  int hue = random(0, 256);
  for(int i = 0; i < NUM_SEGMENTS; i++) {
    if(lookup_table[number][i]) {
      leds[2*i] = CHSV(hue, 255, 200);
      leds[2*i + 1] = CHSV(hue, 255, 200);
    }
    else{
      leds[2*i] = CRGB(0, 0, 0);
      leds[2*i + 1] = CRGB(0, 0, 0);
    }
  }
  FastLED.show();
}
void showNothing(){
  for(int i = 0; i < NUM_SEGMENT_LEDS; i++) {
      leds[i] = CRGB(0, 0, 0);
  }
  FastLED.show();
}
void noSideLEDS(){
  for(int x = 0; x < NUM_SIDE_LEDS; x++){
    side1_leds[x] = CHSV(0, 0, 0);
    side2_leds[x] = CHSV(0, 0, 0);
  }
}
void sideLEDS(){
  int hue = random(0, 256);
  if(SIDE_COUNTER < NUM_SIDE_LEDS / 2){
    int x = SIDE_COUNTER; 
    side1_leds[x] = CHSV(hue, 255, 200);
    side2_leds[x] = CHSV(hue, 255, 200);
    side1_leds[NUM_SIDE_LEDS - x] = CHSV(hue, 255, 200);
    side2_leds[NUM_SIDE_LEDS - x] = CHSV(hue, 255, 200);
    SIDE_COUNTER++;
  }
  else{
    noSideLEDS();
    SIDE_COUNTER = 0;
  }
}

void loop() {

  if(digitalRead(BUTTON_PIN) == LOW){
    delay(500);
    for(int x = COUNTNUM; x >=0; x--){
      showNumber(x);
      delay(1000);
    }
}
  showNothing();
}
