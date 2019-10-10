#include <FastLED.h>
#define LED_PIN     7
#define NUM_LEDS    64
CRGB leds[NUM_LEDS];
int counter;
int hue;
void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clearData();
  FastLED.clear(true);
  FastLED.setBrightness(30);
  counter = 0;
  hue = random8();
  Serial.begin(115200);
}
void loop() {
  Serial.print("Setting hue to: ");
  Serial.println(hue);
  leds[counter] = CHSV(hue, 255, 255);
  counter++;
  if (counter > NUM_LEDS) {
    counter = 0;
    hue = random8();
    FastLED.clear();
  }
  FastLED.show();
  hue += 255/NUM_LEDS;
  if (hue >= 255) {
    hue = 0;
  }
  delay(50);
}