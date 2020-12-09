/*
 *   Copyright (c) 2020 Ludwig Bogsveen
 *   All rights reserved.

 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 
 *   The above copyright notice and this permission notice shall be included in all
 *   copies or substantial portions of the Software.
 
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *   SOFTWARE.
 */

#include "FastLED.h"

const int NUM_LIGHTS = 99;
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define LED_PIN     5

CRGB leds[NUM_LIGHTS];

int program = 3;
int sped = 1000 / 100;
int brightness = 75;
int color = 25;

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
  Serial.begin(9600);
  delay( 3000 ); // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LIGHTS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( 100 );
  //FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LIGHTS);
}

void prg_epelepsi_many_colors() {
  char change[NUM_LIGHTS];

  for(int i = 0; i < NUM_LIGHTS; i++)  {
    delay(sped);
    leds[i] = CHSV(color%255, 255, brightness%255);
    if(random(2) == 0) change[i] = 1;
    else change[i] = -1;
  }

  char c = 0;
  while(true) {
    
    for(int i = 0; i < NUM_LIGHTS; i++)  {
      delay(sped);
      CHSV led = rgb2hsv_approximate(leds[i]);
      led.h += change[i];
      led.v += change[i];
      leds[i] = led;
    }
    FastLED.show();

    if(c > 60) {
      c = 0;
      for(int i = 0; i < NUM_LIGHTS; i++) {
        change[i] *= -1;
      }
    }

    c += 1;
  }
}

void prg_epelepsi_all_colors() {
  char change[NUM_LIGHTS];

  for(int i = 0; i < NUM_LIGHTS; i++)  {
    leds[i] = CHSV(random(256), 255, brightness%255);
    if(random(2) == 0) change[i] = 2;
    else change[i] = -2;
  }

  char c = 0;

  while(true) {
    delay(sped);
    for(int i = 0; i < NUM_LIGHTS; i++)  {
      CHSV led = rgb2hsv_approximate(leds[i]);
      led.h += change[i];
      led.v += change[i];
      leds[i] = led;
    }
    FastLED.show();

    if(c >= 60) {
      c = 0;
      for(int i = 0; i < NUM_LIGHTS; i++) {
        change[i] *= -1;
      }
    }

    c += 1;
  }
}

void prg_epelepsi_single_color() {
  char change[NUM_LIGHTS];

  for(int i = 0; i < NUM_LIGHTS; i++)  {
    delay(sped);
    leds[i] = CHSV(color, 255, (brightness+random(80))%255);
    if(random(2) == 0) change[i] = 1;
    else change[i] = -1;
  }

  char c = 0;

  while(true) {
    for(int i = 0; i < NUM_LIGHTS; i++)  {
      delay(sped);
      CHSV led = rgb2hsv_approximate(leds[i]);
      led.h += change[i];
      led.v += change[i];
      leds[i] = led;
    }
    FastLED.show();

    if(c >= 255) {
      c = 0;
      for(int i = 0; i < NUM_LIGHTS; i++) {
        change[i] *= -1;
      }
    }

    c += 1;
  }
}

void prg_single_color() {
  for(int i = 0; i < NUM_LIGHTS; i++) {
    leds[i] = CHSV(color, 255, brightness);
  }
  delay(sped);
  FastLED.show();
}

void prg_many_colors() {
  for(int i = 0; i < NUM_LIGHTS; i++) {
    leds[i] = CHSV(color+i, 255, brightness);
  }
  delay(sped);
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
  int j = 0;
  while (true) {
    j += 1;
    for(int i = 0; i < NUM_LIGHTS; i++) {
      float b = (sin(((float)i+j)/(float)NUM_LIGHTS*3.1415)+1.0)*80;// value will go between 0 and 80*2
      b = min(brightness+b, 255.0);
      Serial.println((char)b);
      leds[i] = CHSV(color, 255, (char)b);
    }
    delay(sped);
    FastLED.show();
  }
}

void prg_sin_many_colors() {
  for(int i = 0; i < NUM_LIGHTS; i++) {
    char sin_val = (char)(sin((float)i/(float)NUM_LIGHTS*3.1415)*80); 
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
extern const TProgmemPalette16 CRISTHMAS_PALLETTE_P PROGMEM;

const TProgmemPalette16 CRISTHMAS_PALLETTE_P PROGMEM = 
{
    0xBD0000, //RED
    0x14AC00, //GREEN
    0xFFD700, //GOLD

    0xBD0000,
    0x14AC00,
    0xFFD700,

    0xBD0000,
    0x14AC00,
    0xFFD700,

    0xBD0000,
    0x14AC00,
    0xFFD700,

    0xBD0000,
};

void prg_christmas() {
  TBlendType current_blending = LINEARBLEND;
  static int color_index = 0;

  while(true) {
    int x = color_index;
    color_index += 1;
    for( int i = 0; i < NUM_LIGHTS; i++) {
        leds[i] = ColorFromPalette( CRISTHMAS_PALLETTE_P, x, brightness, current_blending);
        x += 3;
    }
    delay(sped);
    FastLED.show();
  }
}


void prg_random() {
  randomSeed(analogRead(0));
  CRGBPalette16 palette(
    CRGB(random(256), random(256), random(256)),
    CRGB(random(256), random(256), random(256)),
    CRGB(random(256), random(256), random(256)),
    CRGB(random(256), random(256), random(256)),
    CRGB(random(256), random(256), random(256)),
    CRGB(random(256), random(256), random(256)),
    CRGB(random(256), random(256), random(256)),
    CRGB(random(256), random(256), random(256)),
    CRGB(random(256), random(256), random(256)),
    CRGB(random(256), random(256), random(256)),
    CRGB(random(256), random(256), random(256)),
    CRGB(random(256), random(256), random(256)),
    CRGB(random(256), random(256), random(256)),
    CRGB(random(256), random(256), random(256)),
    CRGB(random(256), random(256), random(256)),
    CRGB(random(256), random(256), random(256))
  );

  for(int i = 0; i < 16; i++) {
    //palette[i] = random(2^31);
  }
  
  TBlendType current_blending = LINEARBLEND;
  static int color_index = 0;

  while(true) {
    int x = color_index;
    color_index += 1;
    for( int i = 0; i < NUM_LIGHTS; i++) {
        leds[i] = ColorFromPalette(palette, x, brightness, current_blending);
        x += 3;
    }
    delay(sped);
    FastLED.show();
  }
}


void loop() {
  switch (program) {
    case 0: prg_single_color();             break;
    case 1: prg_epelepsi_single_color();    break;
    case 2: prg_fade_in_out_single_color(); break;
    case 3: prg_sin_single_color();         break;
    case 4: prg_many_colors();              break;
    case 5: prg_epelepsi_many_colors();     break;
    case 6: prg_epelepsi_all_colors();      break;
    case 7: prg_fade_in_out_many_colors();  break;
    case 8: prg_sin_many_colors();          break;
    case 9: prg_comet_single_color();       break;
    case 10: prg_christmas();               break;
    case 11: prg_random();                  break;
    default:
      Serial.print("PROGRAM ID");
      Serial.print(program, DEC);
      Serial.println(" IS INVALID!!!");
      break;
  }
}
