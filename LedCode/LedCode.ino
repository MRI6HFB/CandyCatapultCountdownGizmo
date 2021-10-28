#define LED_PIN 5
#define SIDE1_LED_PIN 7
#define SIDE2_LED_PIN 9
#define BOTTOM_LED_PIN 3
#define BUTTON_PIN 11
#define LED_TYPE WS2813
#define NUM_SEGMENT_LEDS 14
#define NUMS_TO_DISPLAY 10
#define NUM_SEGMENTS 7
#define COUNTNUM 9


#include <FastLED.h>
int SIDE_COUNTER = 0;
CRGB leds[NUM_SEGMENT_LEDS];
CRGB bleds[12];
CRGB side1_leds[6];
CRGB side2_leds[6];
int hue = random(0, 256);
long lastSideCount = 0;

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
  pinMode(SIDE1_LED_PIN, OUTPUT);
  pinMode(SIDE2_LED_PIN, OUTPUT);
  pinMode(BOTTOM_LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  FastLED.addLeds<LED_TYPE, LED_PIN>(leds, NUM_SEGMENT_LEDS);
  FastLED.addLeds<LED_TYPE, SIDE1_LED_PIN>(side1_leds, 6);
  FastLED.addLeds<LED_TYPE, SIDE2_LED_PIN>(side2_leds, 6);
  FastLED.addLeds<LED_TYPE, BOTTOM_LED_PIN>(bleds, 12);
  lastSideCount = millis();
}

void showNumber(int number) {
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
  for(int i = 0; i < 6; i++) {
      side1_leds[i] = CRGB(0, 0, 0);
      side2_leds[i] = CRGB(0, 0, 0);
  }
  for(int i = 0; i < 12; i++) {
      bleds[i] = CRGB(0, 0, 0);
  }
}
void noSideLEDS(){
  for(int x = 0; x < 6; x++){
    side1_leds[x] = CHSV(0, 0, 0);
    side2_leds[x] = CHSV(0, 0, 0);
  }
}
void sideLEDS(){
  if(millis() - lastSideCount > 500){
    lastSideCount = millis();
  if(SIDE_COUNTER < 3){
    int x = SIDE_COUNTER; 
    side1_leds[x] = CHSV(hue, 255, 200);
    side2_leds[x] = CHSV(hue, 255, 200);
    side1_leds[5 - x] = CHSV(hue, 255, 200);
    side2_leds[5 - x] = CHSV(hue, 255, 200);
    bleds[2* x + 1] = CHSV(hue, 255, 200);
    bleds[2 * x] = CHSV(hue, 255, 200);
    bleds[7 + 2 * x] = CHSV(hue, 255, 200);
    bleds[6 + 2 * x] = CHSV(hue, 255, 200);
    SIDE_COUNTER++;
    FastLED.show();
  }
  else{
    showNothing();
    FastLED.show();
    SIDE_COUNTER = 0;
    hue = random(0, 256);
  }
  }
}

int botCount = 0;
long botTimer = 0;
int botCount2 = 0;

void celebrate() {
  hue = random(0, 256);
  showNothing();
  FastLED.show();
  delay(500);
  for(int j = 0; j < 6; j++) {
    hue = random(0, 256);
    showNumber(0);
    for(int i = 0; i < 12; i++) {
        bleds[i] = CHSV(hue, 255, 200);
    }
    for(int i = 0; i < 6; i++) {
      side1_leds[i] = CHSV(hue, 255, 200);
      side2_leds[i] = CHSV(hue, 255, 200);
    }
    FastLED.show();
    delay(500);
    showNothing();
    FastLED.show();
    delay(500);
  }
}

void loop() {

  if(digitalRead(BUTTON_PIN) == LOW){
    showNothing();
    FastLED.show();
    delay(500);
    for(int x = COUNTNUM; x >=0; x--){
      hue = random(0, 256);
      showNumber(x);
      delay(1000);
    }
    celebrate();
  }
  sideLEDS();
  delay(50);
}
