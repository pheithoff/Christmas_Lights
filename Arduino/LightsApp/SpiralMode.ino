#include "LED_Buffer.h"

class Trailing_LED {
  public:
    int16_t currBrightness;
    int16_t currHue;
};

CRGB Spiral_LED_Array[NUM_LEDS];

Trailing_LED Trailing_LEDs[NUM_LEDS]; 



uint8_t spiralHue = 100;
uint8_t spiralSaturation = 150;
uint8_t spiralBrightness = 254;

void StepSpiral(LED_Buffer &led_buffer) {
  static int16_t currIndex;
  const uint16_t StepFrequency = 3; // Steps every 1 step
  static uint16_t cnt = 0;
  static bool bool_SpiralingForward = true;
  uint16_t i;
  
  cnt++;
  if(cnt > StepFrequency) {

    if(bool_SpiralingForward) {
      currIndex++;
      if(currIndex == NUM_LEDS) {
          bool_SpiralingForward = false;
          currIndex--;
      }
      Spiral_LED_Array[currIndex] = CHSV(spiralHue, spiralSaturation, spiralBrightness);
    } else {
      Spiral_LED_Array[currIndex] = 0;
      currIndex--;
      if(currIndex < 0) {
        currIndex = 0;
        bool_SpiralingForward = true;
      }
      Spiral_LED_Array[currIndex] = CHSV(spiralHue, spiralSaturation, spiralBrightness);
    }    
    cnt = 0;
  }
  
  led_buffer.updateBufferWithArray(Spiral_LED_Array);
  led_buffer.SetAndIncrementUpdateIndex();
}


void Step_SpiralTrails(LED_Buffer &led_buffer) {
  static int16_t currIndex;
  const uint16_t StepFrequency = 3; // Steps every 1 step
  static uint16_t cnt = 0;
  static bool bool_SpiralingForward = true;
  uint16_t i;
  
  cnt++;
  if(cnt > StepFrequency) {

    if(bool_SpiralingForward) {
      Spiral_LED_Array[currIndex] = 0;
      currIndex++;
      if(currIndex == NUM_LEDS) {
          bool_SpiralingForward = false;
          currIndex--;
      }
      Spiral_LED_Array[currIndex] = CHSV(spiralHue, spiralSaturation, spiralBrightness);
    } else {
      Spiral_LED_Array[currIndex] = 0;
      currIndex--;
      if(currIndex < 0) {
        currIndex = 0;
        bool_SpiralingForward = true;
      }
      Spiral_LED_Array[currIndex] = CHSV(spiralHue, spiralSaturation, spiralBrightness);
    }   
    for(i = 0; i < NUM_LEDS; i++) {
      if( (Trailing_LEDs[i].currBrightness > 0) && (i != currIndex) ) {
        Trailing_LEDs[i].currBrightness = Trailing_LEDs[i].currBrightness - 10;
        if(Trailing_LEDs[i].currBrightness < 0) {
          Trailing_LEDs[i].currBrightness = 0;
        }
        Spiral_LED_Array[i] = CHSV(spiralHue, spiralSaturation, Trailing_LEDs[i].currBrightness);
      }
    }
    Trailing_LEDs[currIndex].currBrightness = spiralBrightness; 
    cnt = 0;
  }

  
  led_buffer.updateBufferWithArray(Spiral_LED_Array);
  led_buffer.SetAndIncrementUpdateIndex();

}

void Step_SpiralRainbow(LED_Buffer &led_buffer) {
  static int16_t currIndex;
  const uint16_t StepFrequency = 3; // Steps every 1 step
  static uint16_t cnt = 0;
  static bool bool_SpiralingForward = true;
  uint16_t i;
  const uint8_t DELTA_HUE = 6;
  spiralSaturation = 255;
  cnt++;
  if(cnt > StepFrequency) {

    if(bool_SpiralingForward) {
      currIndex++;
      spiralHue = spiralHue + DELTA_HUE;
      if(currIndex == NUM_LEDS) {
          bool_SpiralingForward = false;
          spiralHue = spiralHue - DELTA_HUE;
          currIndex--;
      }
      Spiral_LED_Array[currIndex] = CHSV(spiralHue, spiralSaturation, spiralBrightness);
    } else {
      Spiral_LED_Array[currIndex] = 0;
      currIndex--;
      spiralHue = spiralHue - DELTA_HUE;
      if(currIndex < 0) {
        currIndex = 0;
        bool_SpiralingForward = true;
        spiralHue = spiralHue + DELTA_HUE;
      }
      Spiral_LED_Array[currIndex] = CHSV(spiralHue, spiralSaturation, spiralBrightness);
    }   
    cnt = 0;
  }

  
  led_buffer.updateBufferWithArray(Spiral_LED_Array);
  led_buffer.SetAndIncrementUpdateIndex();

}
