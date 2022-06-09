#include "FastLED.h"
#define NUM_LEDS 50
CRGB leds[NUM_LEDS];
uint8_t gHueDelta = 5;

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<NEOPIXEL, 26>(leds, NUM_LEDS);

  Serial.begin(9600);
  uint8_t hue = 0;
  uint8_t i;
  for(i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV( hue, 170, 150);
    hue += gHueDelta;
    Serial.println(leds[i].r);
  }


}



void loop() {
  uint8_t hue = 0;
  static bool firstTime = false;
  uint16_t i;

  for(i = 0; i < NUM_LEDS; i++) {
    if(i == (NUM_LEDS-1)) {
      leds[i].r = leds[0].r;
      leds[i].g = leds[0].g;
      leds[i].b = leds[0].b;
    } else {
      leds[i].r = leds[i + 1].r;
      leds[i].g = leds[i + 1].g;
      leds[i].b = leds[i + 1].b;
    }
  }
  FastLED.show();
  delay(100);
  
}

CHSV rgb2hsv_rainbow(CRGB input_color){

    CHSV output_color;

    uint8_t maximum = max(input_color.r, max(input_color.g, input_color.b));
    uint8_t minimum = min(input_color.r, min(input_color.g, input_color.b));

    output_color.v = maximum;
    uint8_t delta = maximum - minimum;

    output_color.s = (maximum == 0) ? 0 : (255 * delta / maximum);

    if (maximum == minimum) {
        output_color.h = 0;
    }
    else {
        if (maximum == input_color.r){
            //Serial.println("red is max");
            if (input_color.g >= input_color.b){
                if ((input_color.r - input_color.g) <= (delta / 3)){
                    //Serial.println("32-64");
                    output_color.h = map((input_color.r - input_color.g), delta / 3, 0, 32, 64);
                }
                else{
                    //Serial.println("0-32");
                    output_color.h = map((input_color.r - input_color.g), delta, delta / 3, 0, 32);
                }
            }
            else{
                //Serial.println("208-255");
                output_color.h = map((input_color.r - input_color.b), 0, delta, 208, 255);
            }
        }
        else if (maximum == input_color.g){
            //Serial.println("green is max");
            if (input_color.r >= input_color.b){
                //Serial.println("64-96");
                output_color.h = map((input_color.g - input_color.r), 0, delta, 64, 96);
            }
            else{
                if (input_color.g - input_color.b <= delta / 3){
                    //Serial.println("96-128");
                    output_color.h = map((input_color.g - input_color.b), delta, delta / 3, 96, 128);
                }
                else{
                    //Serial.println("128-132?");
                    output_color.h = map((input_color.g - input_color.b), delta / 3, delta, 128, 160);
                }
            }
        }
        else if (maximum == input_color.b){
            //Serial.println("blue is max");
            if (input_color.g > input_color.r){
                //Serial.println("132?-160");
                output_color.h = map((input_color.b - input_color.g), -delta / 3, delta, 128, 160);
            }
            else{
                //Serial.println("160-208");
                output_color.h = map((input_color.b - input_color.r), delta, 0, 160, 208);
            }
        }
    }

    return output_color;
}
