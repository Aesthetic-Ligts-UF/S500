/*
 *   Copyright (c) 2021 Ludwig Bogsveen
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

#ifndef PRGS_H_INCLUDED
#define PRGS_H_INCLUDED

#include "helper.hpp"
#include "globals.hpp"

#include <FastLED.h>
#include <IRremote.h>

void prg_epelepsi_single_color() {
  unsigned char offset[100];

  for(int i = 0; i < NUM_LIGHTS; i++) {
    offset[i] = random(100);
  }
  
  clear();

  int l = 0;

  while(sleep(sped)) {

    l += 5;

    for(int i = 0; i < NUM_LIGHTS; i++) {
      float b = sin((float)(i+l+offset[i])/(float)NUM_LIGHTS*3.1415*2.0)*80.0;
      b = min(brightness+b, 255.0);
      b = max(b, 0.0);
      leds[i] = CHSV(color, 255, b);
    }

    show();
  }
}

void prg_epelepsi_many_colors() {
  unsigned char offset[100];

  for(int i = 0; i < NUM_LIGHTS; i++) {
    offset[i] = random(100);
  }
  
  clear();

  int l = 0;

  while(sleep(sped)) {

    l += 5;

    for(int i = 0; i < NUM_LIGHTS; i++) {
      float b = sin((float)(i+l+offset[i])/(float)NUM_LIGHTS*3.1415*2.0)*80.0;
      b = min(brightness+b, 255.0);
      b = max(b, 0.0);
      leds[i] = CHSV(color+offset[i], 255, b);
    }

    show();
  }
}


void prg_epelepsi_all_colors() {
  unsigned char offset[100];

  for(int i = 0; i < NUM_LIGHTS; i++) {
    offset[i] = random(256);
  }
  
  clear();

  int l = 0;

  while(sleep(sped)) {

    l += 5;

    for(int i = 0; i < NUM_LIGHTS; i++) {
      float b = sin((float)(i+l+offset[i])/(float)NUM_LIGHTS*3.1415*2.0)*80.0;
      b = min(brightness+b, 255.0);
      b = max(b, 0.0);
      leds[i] = CHSV(offset[i], 255, b);
    }

    show();
  }
}

void prg_single_color() {
  //Serial.println("1");  
  while(sleep(sped)) {
    //Serial.println("2");  
    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i] = CHSV(color, 255, brightness);
    }
    show();
  }
  //Serial.println("3");  
}

void prg_many_colors() {
  while(sleep(sped)) {
    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i] = CHSV(color+((float)i/NUM_LIGHTS)*160, 255, brightness);
    }
    show();
  }
}

void prg_fade_in_out_single_color() {
  int j = 0;
  while(sleep(sped)) {
    j += 1;

    float b = sin((float)j/(float)NUM_LIGHTS*3.1415*2.0)*80.0;
    b = min(brightness+b, 255.0);
    b = max(b, 0.0);

    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i] = CHSV(color, 255, b);
    }

    show();
  }
}

void prg_fade_in_out_many_colors() {
  int j = 0;
  while(sleep(sped)) {
    j += 1;
    
    float b = sin((float)j/(float)NUM_LIGHTS*3.1415*2.0)*80.0;
    b = min(brightness+b, 255.0);
    b = max(b, 0.0);

    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i] = CHSV((color+i)%256, 255, b);
    }

    show();
  }
}

void prg_fade_between_single_colors() {  
  int j = 0;
  while(sleep(sped)) {
    j += 1;

    float b = sin((float)j/(float)NUM_LIGHTS*3.1415*2.0)*80.0;
    b = min(brightness+b, 255.0);
    b = max(b, 0.0);

    float c = sin((float)j/(float)NUM_LIGHTS*3.1415)*80.0;
    c = max(c, 0.0);

    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i] = CHSV((int)(c+color)%256, 255, b);
    }

    show();
  }
}

void prg_fade_between_many_colors() {
  int j = 0;
  while(sleep(sped)) {
    j += 1;

    float b = sin((float)j/(float)NUM_LIGHTS*3.1415*2.0)*80.0;
    b = min(brightness+b, 255.0);
    b = max(b, 0.0);

    float c = sin((float)j/(float)NUM_LIGHTS*3.1415)*80.0;
    c = max(c, 0.0);

    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i] = CHSV(((int)c+i+color)%256, 255, b);
    }

    show();
  }
}

void prg_sin_single_color() {
  int j = 0;
  while(sleep(sped)) {
    j += 1;
    for(int i = 0; i < NUM_LIGHTS; i++) {
      float b = sin((float)(i+j)/(float)NUM_LIGHTS*3.1415*2.0)*80.0;
      b = min(brightness+b, 255.0);
      b = max(b, 0.0);
      
      leds[i] = CHSV(color, 255, b);
    }

    show();
  }
}

void prg_sin_many_colors() {
  int j = 0;
  while(sleep(sped)) {
    j += 1;
    for(int i = 0; i < NUM_LIGHTS; i++) {
      float b = sin((float)(i+j)/(float)NUM_LIGHTS*3.1415*2.0)*80.0;
      char c = color+b;
      b = min(brightness+b, 255.0);
      b = max(b, 0.0);
      
      leds[i] = CHSV(c, 255, b);
    }

    show();
  }
}

void prg_comet_single_color() {
  int trail_length = 12;

  int i = 0;
  while(sleep(sped)) {
    if(i > trail_length-1 && i < NUM_LIGHTS+trail_length) { leds[i-trail_length] = CRGB(0, 0, 0); }
    for(int j = 0; j < trail_length; j++) {
      if(i-j > 0 && i-j < NUM_LIGHTS) {
        leds[i-j] = CHSV(color, 255, brightness * (1.0 - (float)j/trail_length));
      }
    }

    i++;

    if(i >= NUM_LIGHTS+trail_length) {
      i = 0;
    }

    show();
  }
}

void prg_comet_many_colors() {
  int trail_length = 12;

  int i = 0;
  while(sleep(sped)) {
    if(i > trail_length-1 && i < NUM_LIGHTS+trail_length) { leds[i-trail_length] = CRGB(0, 0, 0); }
    for(int j = 0; j < trail_length; j++) {
      if(i-j > 0 && i-j < NUM_LIGHTS) {
        leds[i-j] = CHSV(color+i, 255, brightness * (1.0 - (float)j/trail_length));
      }
    }

    i++;

    if(i >= NUM_LIGHTS+trail_length) {
      i = 0;
    }

    show();
  }
}

void prg_ping_pong_single_color() {
  int trail_length = 12;

  char dir = 0;
  int i = 0;
  
  while(sleep(sped)) {
    if(i > trail_length-1 && i < NUM_LIGHTS+trail_length) { leds[i-trail_length] = CRGB(0, 0, 0); }
    for(int j = 0; j < trail_length; j++) {
      if(i-j > 0 && i-j < NUM_LIGHTS) {
        leds[abs((NUM_LIGHTS * -dir)+(i-j))] = CHSV(color, 255, brightness * (1.0 - (float)j/trail_length));
      }
    }

    i++;

    if(i >= NUM_LIGHTS+trail_length) {
      i = 0;
      dir = !dir;
    }

    show();
  }

  dir = !dir;
}

void prg_ping_pong_many_colors() {
  int trail_length = 12;

  char dir = 0;
  int i = 0;
  
  while(sleep(sped)) {
    if(i > trail_length-1 && i < NUM_LIGHTS+trail_length) { leds[i-trail_length] = CRGB(0, 0, 0); }
    for(int j = 0; j < trail_length; j++) {
      if(i-j > 0 && i-j < NUM_LIGHTS) {
        leds[abs((NUM_LIGHTS * -dir)+(i-j))] = CHSV(color+i, 255, brightness * (1.0 - (float)j/trail_length));
      }
    }

    i++;

    if(i >= NUM_LIGHTS+trail_length) {
      i = 0;
      dir = !dir;
    }

    show();
  }
}

void prg_stars_single_color() {
  unsigned char stars[100];
  unsigned char offset[100];

  float j = 0;
  for(int i = 0; i < 100; i++) {
    stars[i] = j;
    j += NUM_LIGHTS / 100.0f;
    //Serial.println((int)stars[i]);
    offset[i] = random(100);
  }
  
  clear();

  int l = 0;

  while(sleep(1)) {

    l += 1;

    for(int i = 0; i < 100; i++) {
      float b = sin((float)(i+l+offset[i])/(float)100*3.1415*2.0)*80.0;
      b = min(brightness+b, 255.0);
      b = max(b, 0.0);
      leds[stars[i]] = CHSV(color, 55, b);
    }

    show();
  }
}

void prg_stars_all_color() {
  unsigned char stars[100];
  unsigned char offset[100];

  float j = 0;
  for(int i = 0; i < 100; i++) {
    stars[i] = j;
    j += NUM_LIGHTS / 100.0f;
    //Serial.println((int)stars[i]);
    offset[i] = random(100);
  }
  
  clear();

  int l = 0;

  while(sleep(1)) {

    l += 1;

    for(int i = 0; i < 100; i++) {
      float b = sin((float)(i+l+offset[i])/(float)100*3.1415*2.0)*80.0;
      b = min(brightness+b, 255.0);
      b = max(b, 0.0);
      leds[stars[i]] = CHSV(color+offset[i], 55, b);

      //if(b < 1.0) {
        //stars[i] = random(NUM_LIGHTS);
      //}
    }

    show();
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

  while(sleep(sped)) {
    int x = color_index;
    color_index += 1;
    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i] = ColorFromPalette( CRISTHMAS_PALLETTE_P, x, brightness, current_blending);
      x += 3;
    }
    show();
  }
}

void prg_rainbow() {
  int j = 0;
  while(sleep(sped)) {
    j += 1;

    CHSV rainbow[NUM_LIGHTS];
    fill_rainbow(rainbow, NUM_LIGHTS, color+j, 255/NUM_LIGHTS);
    
    for(int i = 0; i < NUM_LIGHTS; i++) {
      rainbow[i].v = brightness;
      leds[i] = rainbow[i];
    }

    show();
  }
}


void prg_random() {
  randomSeed(analogRead(0));
  CRGBPalette16 palette(
    CHSV(random(256), 255, brightness),
    CHSV(random(256), 255, brightness),
    CHSV(random(256), 255, brightness),
    CHSV(random(256), 255, brightness),
    CHSV(random(256), 255, brightness),
    CHSV(random(256), 255, brightness),
    CHSV(random(256), 255, brightness),
    CHSV(random(256), 255, brightness),
    CHSV(random(256), 255, brightness),
    CHSV(random(256), 255, brightness),
    CHSV(random(256), 255, brightness),
    CHSV(random(256), 255, brightness),
    CHSV(random(256), 255, brightness),
    CHSV(random(256), 255, brightness),
    CHSV(random(256), 255, brightness),
    CHSV(random(256), 255, brightness)
  );
  
  TBlendType current_blending = LINEARBLEND;
  static int color_index = 0;

  while(sleep(sped)) {
    int x = color_index;
    color_index += 1;
    for( int i = 0; i < NUM_LIGHTS; i++) {
        leds[i] = ColorFromPalette(palette, x, brightness, current_blending);
        x += 3;
    }
    show();
  }
}

void prg_snake() {
  int snake_pos = 0;
  int snake_size = 1;
  int food_pos = 100;

  while(sleep(sped)) {

    if(snake_size >= NUM_LIGHTS/2) {
      snake_size = 1;
      for(int i = 0; i < NUM_LIGHTS; i++) {
        leds[i] = CHSV(0, 0, brightness);
      }
    }

    if((snake_pos+snake_size)%NUM_LIGHTS==food_pos) {
      food_pos = random(NUM_LIGHTS-2)+1;
      snake_size++;

      for(int i = 0; i < NUM_LIGHTS; i++) {
        leds[i] = CHSV(200, 255, brightness/2);
      }
    }

    snake_pos++;

    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i].r *= 0.9;
      leds[i].g *= 0.9;
      leds[i].b *= 0.9;
    }

    for(int i = snake_pos; i < snake_pos+snake_size; i++) {
      leds[i%NUM_LIGHTS] = CHSV(100, 255, brightness); 
    }

    leds[food_pos-1] = CHSV(0, 255, brightness);
    leds[food_pos] = CHSV(0, 255, brightness);
    leds[food_pos+1] = CHSV(0, 255, brightness);

    show();
  }

}

void prg_grayscale() {
  while(sleep(sped)) {
    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i] = CHSV(0, 0, brightness);
    }

    show();
  }
}

void prg_firework() {
  while(sleep(sped)) {

  }
}

void prg_off() {
  for(CRGB& l : leds) l = CRGB(0, 0, 0);
  show();
  while(sleep(1000));   
}

#endif