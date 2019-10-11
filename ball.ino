#include <FastLED.h>
#include "mpu.h"
#define LED_PIN 7
#define NUM_LEDS 64
#define MPU_ADDR 0x68

char tmp_str[7]; // temporary variable used in convert function
char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}

CRGB leds[NUM_LEDS];
int counter;
int hue;
mpu::mpu_acceleration mpu_acc;
void setup() {
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear(true);
  FastLED.setBrightness(30);
  counter = 0;
  hue = random8();
  Serial.begin(115200);
  mpu::setup(MPU_ADDR);
}
void loop() {
  int16_t blup;
  leds[32] = CHSV(hue, 255, 90);
  hue += 5;
  if (hue >= 255) {
    hue = 0;
  }
  blup = mpu::read(MPU_ADDR, &mpu_acc);
  Serial.print("a_x: "); Serial.println(blup);
  Serial.print(", a_y: "); Serial.println(convert_int16_to_str(mpu_acc.a_y));
  Serial.print(", a_z: "); Serial.println(convert_int16_to_str(mpu_acc.a_z));

  delay(100);
}