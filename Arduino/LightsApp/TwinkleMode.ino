#include "LED_Buffer.h"

#define MAX_POSSIBLE_BRIGHTNESS 225
#define MIN_POSSIBLE_BRIGHTNESS 50
#define MIN_POSSIBLE_OFFTIME 60
#define MAX_POSSIBLE_OFFTIME 250
class Twinkle_LED {
  public:
    uint8_t currBrightness;
    uint8_t maxBrightness;
    uint16_t timer;  
    bool brightnessIsIncreasing;
};

Twinkle_LED twinkleLEDs[NUM_LEDS]; 


void InitTwinkleMode() {
  uint16_t i;

  for(i = 0; i < NUM_LEDS; i++) {
    twinkleLEDs[i].currBrightness = 0;
    twinkleLEDs[i].maxBrightness = random(MIN_POSSIBLE_BRIGHTNESS, MAX_POSSIBLE_BRIGHTNESS);
    twinkleLEDs[i].timer = random(MIN_POSSIBLE_OFFTIME, MAX_POSSIBLE_OFFTIME);
    
  }
}
uint8_t randomHue = random(0, 255);
  
void StepTwinkle(LED_Buffer &led_buffer) {
  uint8_t i;

  CRGB new_led_array[NUM_LEDS];
  const uint16_t brightnessDelta = 2;

  for(i = 0; i<NUM_LEDS; i++) {
    if(twinkleLEDs[i].timer == 0) {
      if(twinkleLEDs[i].brightnessIsIncreasing) {
      twinkleLEDs[i].currBrightness += brightnessDelta*2;
      if(twinkleLEDs[i].currBrightness > twinkleLEDs[i].maxBrightness) {
         twinkleLEDs[i].brightnessIsIncreasing = false;
      }
      } else {
        twinkleLEDs[i].currBrightness -= brightnessDelta;
        if(twinkleLEDs[i].currBrightness == 0) {
          twinkleLEDs[i].brightnessIsIncreasing = true;
          twinkleLEDs[i].timer = random(MIN_POSSIBLE_OFFTIME, MAX_POSSIBLE_OFFTIME);
          twinkleLEDs[i].maxBrightness = random(MIN_POSSIBLE_BRIGHTNESS, MAX_POSSIBLE_BRIGHTNESS);
          //randomHue = random(0, 255);
        }
      }
    } else {
      twinkleLEDs[i].timer--;
    }
    // White light
    //new_led_array[i] = CRGB( twinkleLEDs[i].currBrightness, twinkleLEDs[i].currBrightness, twinkleLEDs[i].currBrightness);
    // Random hue
    new_led_array[i] = CHSV(randomHue, 200, twinkleLEDs[i].currBrightness);
  }
  led_buffer.updateBufferWithArray(new_led_array);
  led_buffer.SetAndIncrementUpdateIndex();
  
}
