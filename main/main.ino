#include "FastLED.h"

const int NUM_LIGHTS = 150;

CRGB leds[NUM_LIGHTS];

int program = 0;
int sped = 100;
int brightness = 100;
int color = 0;

const int din_mamma_1 = 0x7100AB;
const int din_mamma_2 = 0xFF35AB;

void poll_inputs() {
  
}

//Same as delay but it polls inputs from the IR sensor and does work acordingly
//TODO return a bool if the current program should be changed
void sleep(int ms) {
  unsigned long start_time = millis();
  while millis() < start_time + ms {
    poll_inputs();
  }
}

void setup() {
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LIGHTS);
}

void prg_epelepsi() {
  for(int i = 0; i < NUM_LIGHTS; i++)  {
    delay(sped);
    leds[i] = CHSV((color+random(20))%255, 255, (brightness+random(20))%255);
  }
  FastLED.show();
}

void prg_single_color() {
  for(int i = 0; i < NUM_LIGHTS; i++) {
    leds[i] = CHSV(color, 255, brightness);
  }
  delay(sped*NUM_LIGHTS);
  FastLED.show();
}

void prg_fade_in_out() {
  for(int i = 0; i < NUM_LIGHTS; i++) {
    leds[i] = CHSV(color, 255, 0);
  }
  
  //FADE IN
  for(int j = 0; j < brightness; j++) {
    for(int i = 0; i < NUM_LIGHTS; i++) {
      CHSV led = rgb2hsv_approximate(leds[i]);
      led.v += 1;
      leds[i] = led;
    }
    delay(sped);
    FastLED.show();
  }

  //FADE OUT
  for(int j = 0; j < brightness; j++) {
    for(int i = 0; i < NUM_LIGHTS; i++) {
      CHSV led = rgb2hsv_approximate(leds[i]);
      led.v -= 1;
      leds[i] = led;
    }
    delay(sped);
    FastLED.show();
  }
}

void prg_sin() {
  for(int i = 0; i < NUM_LIGHTS; i++) {
    leds[i] = CHSV(color, 255, brightness+(char)(sin((float)i/(float)NUM_LIGHTS*3.1415)*20));
    delay(sped);
    FastLED.show();
  }
}

void loop() {
  switch (program) {
    case 0:
      prg_epelepsi();
      break;
   case 1:
      prg_single_color();
      break;
    case 2:
      prg_fade_in_out();
      break;
    case 3:
      prg_sin();
      break;
    default:
      Serial.print("PROGRAM ID");
      Serial.print(program, DEC);
      Serial.println(" IS INVALID!!!");
      break;
  }
}
