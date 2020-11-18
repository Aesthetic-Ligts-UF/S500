#include "FastLED.h"

const int NUM_LIGHTS = 150;

CRGB leds[NUM_LIGHTS];

int program = 0;
int sped = 100;
int brightness = 100;
int color = 0;

const long din_mamma_1 = 0x7100AB;
const long din_mamma_2 = 0xFF35AB;

void poll_inputs() {
  //TODO fill in code to poll innput from the IR sensor
}

//TODO return a bool if the current program should be changed
void sleep(int ms) {
  unsigned long start_time = millis();
  while(millis() < start_time + ms) {
    poll_inputs();
  }
}

void setup() {
  FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LIGHTS);
}

void prg_epelepsi_many_colors() {
  for(int i = 0; i < NUM_LIGHTS; i++)  {
    delay(sped);
    leds[i] = CHSV((color+random(20))%255, 255, (brightness+random(20))%255);
  }
  FastLED.show();
}

void prg_epelepsi_all_colors() {
  for(int i = 0; i < NUM_LIGHTS; i++)  {
    delay(sped);
    leds[i] = CHSV(random(256), 255, (brightness+random(20))%255);
  }
  FastLED.show();
}

void prg_epelepsi_single_color() {
  for(int i = 0; i < NUM_LIGHTS; i++)  {
    delay(sped);
    leds[i] = CHSV(color, 255, (brightness+random(20))%255);
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

void prg_many_colors() {
  for(int i = 0; i < NUM_LIGHTS; i++) {
    leds[i] = CHSV(color+i, 255, brightness);
  }
  delay(sped*NUM_LIGHTS);
  FastLED.show();
}

void prg_fade_in_out_single_color() {
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

void prg_fade_in_out_many_colors() {
  for(int i = 0; i < NUM_LIGHTS; i++) {
    leds[i] = CHSV((color+i)%256, 255, 0);
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

void prg_sin_single_color() {
  for(int i = 0; i < NUM_LIGHTS; i++) {
    leds[i] = CHSV(color, 255, brightness+(char)(sin((float)i/(float)NUM_LIGHTS*3.1415)*20));
    delay(sped);
    FastLED.show();
  }
}

void prg_sin_many_colors() {
  for(int i = 0; i < NUM_LIGHTS; i++) {
    char sin_val = (char)(sin((float)i/(float)NUM_LIGHTS*3.1415)*20);
    leds[i] = CHSV(color+sin_val, 255, brightness+sin_val);
    delay(sped);
    FastLED.show();
  }
}

void prg_comet_single_color() {
  for(int i = 0; i < NUM_LIGHTS+4; i++) {
    if(i > 3 && i < NUM_LIGHTS+4) { leds[i-4] = CRGB(0, 0, 0); }
    if(i > 2 && i < NUM_LIGHTS+3) { leds[i-3] = CHSV(color, 255, brightness * 0.25); }
    if(i > 1 && i < NUM_LIGHTS+2) { leds[i-2] = CHSV(color, 255, brightness * 0.50); }
    if(i > 0 && i < NUM_LIGHTS+1) { leds[i-1] = CHSV(color, 255, brightness * 0.75); }
    if(i < NUM_LIGHTS) { leds[i] = CHSV(color, 255, brightness); }
    delay(sped);
    FastLED.show();
  }
}

void prg_comet_many_colors() {
  for(int i = 0; i < NUM_LIGHTS+4; i++) {
    if(i > 3 && i < NUM_LIGHTS+4) { leds[i-4] = CRGB(0, 0, 0); }
    if(i > 2 && i < NUM_LIGHTS+3) { leds[i-3] = CHSV(color+i, 255, brightness * 0.25); }
    if(i > 1 && i < NUM_LIGHTS+2) { leds[i-2] = CHSV(color+i, 255, brightness * 0.50); }
    if(i > 0 && i < NUM_LIGHTS+1) { leds[i-1] = CHSV(color+i, 255, brightness * 0.75); }
    if(i < NUM_LIGHTS) { leds[i] = CHSV(color, 255, brightness); }
    delay(sped);
    FastLED.show();
  }
}

void loop() {
  switch (program) {
    case 0:
      prg_epelepsi_single_color();
      break;
   case 1:
      prg_single_color();
      break;
    case 2:
      prg_fade_in_out_single_color();
      break;
    case 3:
      prg_sin_single_color();
      break;
    case 4:
      prg_many_colors();
      break;
    case 5:
      prg_epelepsi_many_colors();
      break;
    case 6:
      prg_epelepsi_all_colors();
      break;
    case 7:
      prg_fade_in_out_many_colors();
      break;
    case 8:
      prg_sin_many_colors();
      break;
    case 9:
      prg_comet_single_color();
      break;
    default:
      Serial.print("PROGRAM ID");
      Serial.print(program, DEC);
      Serial.println(" IS INVALID!!!");
      break;
  }
}
