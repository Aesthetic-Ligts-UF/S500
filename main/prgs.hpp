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
#include <lib8tion.h>

void prg_epelepsi_single_color() {
  bool black = false;
  while(sleep(max(COLOR_LVLS[4], sped))) {
    if(black) {
      for(int i = 0; i < NUM_LIGHTS; i++) {
        leds[i] = CRGB(0, 0, 0);
      }

      show();
    } else {
      int col = random(256);
      for(int i = 0; i < NUM_LIGHTS; i++) {
        leds[i] = CHSV(col, 255, brightness);
      }

      show();
    }
    black = !black;
  }
}

void prg_epelepsi_many_colors() {
  bool black = false;
  while(sleep(max(COLOR_LVLS[4], sped))) {
    if(black) {
      for(int i = 0; i < NUM_LIGHTS; i++) {
        leds[i] = CRGB(0, 0, 0);
      }

      show();
    } else {
      for(int i = 0; i < NUM_LIGHTS; i++) {
        leds[i] = CHSV(color+random(100), 255, brightness);
      }

      show();
    }
    black = !black;
  }
}


void prg_epelepsi_all_colors() {
  bool black = false;
  while(sleep(max(COLOR_LVLS[4], sped))) {
    if(black) {
      for(int i = 0; i < NUM_LIGHTS; i++) {
        leds[i] = CRGB(0, 0, 0);
      }

      show();
    } else {
      for(int i = 0; i < NUM_LIGHTS; i++) {
        leds[i] = CHSV(color+random(256), 255, brightness);
      }

      show();
    }
    black = !black;
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

    int b = (sin8(j) - 127) >> 1;
    b = min(brightness+b, 255);
    b = max(b, 0);

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

    int b = (sin8(j) - 127) >> 1;
    b = min(brightness+b, 255);
    b = max(b, 0);

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

    int b = (sin8(j) - 127) >> 1;
    b = min(brightness+b, 255);
    b = max(b, 0);

    int c = (sin8(j / 2) - 127) >> 1;
    c = max(c, 0);

    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i] = CHSV((c+color)%256, 255, b);
    }

    show();
  }
}

void prg_fade_between_many_colors() {
  int j = 0;
  while(sleep(sped)) {
    j += 1;

    int b = (sin8(j) - 127) >> 1;
    b = min(brightness+b, 255);
    b = max(b, 0);

    int c = (sin8(j / 2) - 127);
    c = max(c, 0);

    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i] = CHSV((c+i+color)%256, 255, b);
    }

    show();
  }
}

void prg_fade_to_white_single_color() {  
  int j = 0;
  while(sleep(sped)) {
    j += 1;

    int s = sin8(j);

    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i] = CHSV(color, s, brightness);
    }

    show();
  }
}

void prg_fade_to_white_single_color_change() {  
  int j = 0;
  while(sleep(sped)) {
    j += 1;

    int s = sin8(j);

    int c = (sin8(j / 2) - 127) >> 1;
    c = max(c, 0);

    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i] = CHSV((c+color)%256, s, brightness);
    }

    show();
  }
}

void prg_fade_to_white_many_colors() {
  int j = 0;
  while(sleep(sped)) {
    j += 1;

    int s = sin8(j);

    int c = (sin8(j / 2) - 127) >> 1;
    c = max(c, 0);

    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i] = CHSV((c+i+color)%256, s, brightness);
    }

    show();
  }
}

void prg_sin_single_color() {
  int j = 0;
  while(sleep(sped)) {
    j += 1;
    for(int i = 0; i < NUM_LIGHTS; i++) {
      int b = (sin8(i+j) - 127) >> 1;
      b = min(brightness+b, 255);
      b = max(b, 0);
      
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
      int b = (sin8(i+j) - 127) >> 1;
      b = min(brightness+b, 255);
      b = max(b, 0);
      
      leds[i] = CHSV(color+b, 255, b);
    }

    show();
  }
}

void prg_comet_single_color() {
  int trail_length = 16;

  int i = 0;
  while(sleep(sped)) {
    clear();
    draw_tail_single_color(i, trail_length, 0, color);

    i++;

    if(i >= NUM_LIGHTS+trail_length) {
      i = 0;
    }

    show();
  }
}

void prg_comet_many_colors() {
  int trail_length = 16;

  int i = 0;
  while(sleep(sped)) {
    clear();
    draw_tail_many_colors(i, trail_length, 0, color);

    i++;

    if(i >= NUM_LIGHTS+trail_length) {
      i = 0;
    }

    show();
  }
}

void prg_many_comets_single_color() {
  srand(millis());

  int trail_length = 16;

  int comets[3];
  char dir[3];

  for(int i = 0; i < 3; i++) comets[i] = random(NUM_LIGHTS);
  for(int i = 0; i < 3; i++) dir[i] = random(100) < 50;
  
  while(sleep(sped)) {
    clear();

    for(int i = 0; i < 3; i++) {
      draw_tail_single_color(comets[i], trail_length, 0, color);

      comets[i] += (dir[i]*2)-1;

      if(comets[i] >= NUM_LIGHTS+trail_length) {
        comets[i] = 0;
      } else if(comets[i] < 0) {
        comets[i] = NUM_LIGHTS-1-comets[i];
      }

      if(random(10000) > 9940) {
        dir[i] = random(100) < 50;
      }
    }

    show();
  }
}

void prg_many_comets_single_color_one_dir() {
  srand(millis());

  int trail_length = 16;

  int comets[3];
  char dir[3];

  comets[0] = 20;
  comets[1] = 60;
  comets[2] = 120;
  for(int i = 0; i < 3; i++) dir[i] = 1;
  
  while(sleep(sped)) {
    clear();

    for(int i = 0; i < 3; i++) {
      draw_tail_single_color(comets[i], trail_length, 0, color);

      comets[i] += (dir[i]*2)-1;

      if(comets[i] >= NUM_LIGHTS+trail_length) {
        comets[i] = 0;
      } else if(comets[i] < 0) {
        comets[i] = NUM_LIGHTS-1-comets[i];
      }
    }

    show();
  }
}

void prg_many_comets_many_colors() {
  srand(millis());

  int trail_length = 16;

  int comets[3];
  char dir[3];

  for(int i = 0; i < 3; i++) comets[i] = random(NUM_LIGHTS);
  for(int i = 0; i < 3; i++) dir[i] = random(100) < 50;
  
  while(sleep(sped)) {
    clear();

    for(int i = 0; i < 3; i++) {
      draw_tail_many_colors(comets[i], trail_length, 0, color);

      comets[i] += (dir[i]*2)-1;

      if(comets[i] >= NUM_LIGHTS+trail_length) {
        comets[i] = 0;
      } else if(comets[i] < 0) {
        comets[i] = NUM_LIGHTS-1-comets[i];
      }

      if(random(10000) > 9940) {
        dir[i] = random(100) < 50;
      }
    }

    show();
  }
}

void prg_ping_pong_single_color() {
  int trail_length = 16;

  char dir = 0;
  int i = 0;
  
  while(sleep(sped)) {
    clear();

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
}

void prg_ping_pong_many_colors() {
  int trail_length = 16;

  char dir = 0;
  int i = 0;
  
  while(sleep(sped)) {
    clear();
    //if(i > trail_length-1 && i < NUM_LIGHTS+trail_length) { leds[i-trail_length] = CRGB(0, 0, 0); }
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
      
      /*float b = sin((float)(i+l+offset[i])/(float)100*3.1415*2.0)*80.0;
      b = min(brightness+b, 255.0);
      b = max(b, 0.0);*/
      int b = (sin8(i+l+offset[i]) - 127) >> 1;
      b = min(brightness+b, 255);
      b = max(b, 0);
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
      /*float b = sin((float)(i+l+offset[i])/(float)100*3.1415*2.0)*80.0;
      b = min(brightness+b, 255.0);
      b = max(b, 0.0);
      leds[stars[i]] = CHSV(color+offset[i], 55, b);*/

      int b = (sin8(i+l+offset[i]) - 127) >> 1;
      b = min(brightness+b, 255);
      b = max(b, 0);
      leds[stars[i]] = CHSV(color+offset[i], 55, b);
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
  CHSV rainbow[NUM_LIGHTS];
  while(sleep(sped)) {
    j += 1;
    
    fill_rainbow(rainbow, NUM_LIGHTS, color+j, 255/NUM_LIGHTS);
    
    for(int i = 0; i < NUM_LIGHTS; i++) {
      rainbow[i].v = brightness;
      leds[i] = rainbow[i];
    }

    show();
  }
}

void prg_rainbow_every_other() {
  int j = 0;
  while(sleep(sped)) {
    clear();

    CHSV rainbow[NUM_LIGHTS];
    fill_rainbow(rainbow, NUM_LIGHTS, color+j, 255/NUM_LIGHTS);
    
    for(int i = 0; i < NUM_LIGHTS; i+=2) {
      rainbow[i].v = brightness;
      leds[i] = rainbow[i];
    }

    show();

    j += 1;
  }
}

void prg_rainbow_every_other_rotating() {
  int j = 0;

  CHSV rainbow[NUM_LIGHTS];
  fill_rainbow(rainbow, NUM_LIGHTS, color, 255/NUM_LIGHTS);
  for(int i = 0; i < NUM_LIGHTS; i++) {
    rainbow[i].v = brightness;
  }

  while(sleep(sped)) {
    clear();

    for(int i = 0; i < NUM_LIGHTS; i+=2) {
      CHSV brighter = rainbow[i];
      brighter.v = brightness*(j%100)/100;
      CHSV darker = rainbow[i];
      darker.v = brightness*(99-(j%100))/100;
      leds[(i+j/100)%NUM_LIGHTS] = brighter;
      leds[(i+j/100+1)%NUM_LIGHTS] = darker;
    }

    show();

    j += 1;
  }
}


void prg_random() {
  randomSeed(analogRead(0));
  CRGBPalette16 palette(
    CHSV(random(256), 255, 255),
    CHSV(random(256), 255, 255),
    CHSV(random(256), 255, 255),
    CHSV(random(256), 255, 255),
    CHSV(random(256), 255, 255),
    CHSV(random(256), 255, 255),
    CHSV(random(256), 255, 255),
    CHSV(random(256), 255, 255),
    CHSV(random(256), 255, 255),
    CHSV(random(256), 255, 255),
    CHSV(random(256), 255, 255),
    CHSV(random(256), 255, 255),
    CHSV(random(256), 255, 255),
    CHSV(random(256), 255, 255),
    CHSV(random(256), 255, 255),
    CHSV(random(256), 255, 255)
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

void prg_white() {
  while(sleep(sped)) {
    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i] = CHSV(0, 0, brightness);
    }

    show();
  }
}

void prg_every_other_led() {
  while(sleep(sped)) {
    for(int i = 0; i < NUM_LIGHTS; i+=2) {
      leds[i] = CHSV(color, 255, brightness);
      leds[(i+1)%256] = CHSV(color+127, 255, brightness);
    }

    show();
  }
}

void prg_every_other_led_fade() {
  int j = 0;

  while(sleep(sped)) {

    for(int i = 0; i < NUM_LIGHTS; i+=2) {
      /*float b = sin((float)(i+j)/(float)NUM_LIGHTS*3.1415*2.0)*80.0;
      b = min(brightness+b, 255.0);
      b = max(b, 0.0);*/

      int b = (sin8(i+j) - 127) >> 1;
      b = min(brightness+b, 255);
      b = max(b, 0);

      leds[i] = CHSV(color, 255, b);
      leds[(i+1)%256] = CHSV(color+127, 255, 255-b);
    }

    j += 1;

    show();
  }
}

void prg_every_other_led_rotating() {
  int j = 0;
  int index = 0;

  while(sleep(sped)) {

    for(int i = 1; i < NUM_LIGHTS; i+=2) {
      int b = (sin8(i+j) - 127) >> 1;
      b = min(brightness+b, 255);
      b = max(b, 0);

      leds[(i+index)%NUM_LIGHTS]              = CHSV(color, 255, b);
      leds[(i+1-index+NUM_LIGHTS)%NUM_LIGHTS] = CHSV(color+127, 255, 255-b);

      //Serial.println((i+index)%NUM_LIGHTS);
      //Serial.println((i+1-index+NUM_LIGHTS)%NUM_LIGHTS);
      //Serial.println();
    }

    //while(1);

    j += 1;
    index += 2;

    if(index >= NUM_LIGHTS) {
      index = 0;
    }

    show();
  }
}

void prg_fill_from_center_many_colors() {
  int size = 1;

  while(sleep(sped)) {

    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i].r *= 0.9;
      leds[i].g *= 0.9;
      leds[i].b *= 0.9;
    }

    for(int i = NUM_LIGHTS/2-size-1; i <= NUM_LIGHTS/2+size; i++) {
      leds[i] = CHSV(color+i, 255, brightness);
    }

    size += 1;

    if(size >= NUM_LIGHTS/2) {
      size = 1;
    }

    show();
  }
}

void prg_fill_from_center() {
  int size = 1;

  while(sleep(sped)) {

    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i].r *= 0.9;
      leds[i].g *= 0.9;
      leds[i].b *= 0.9;
    }

    for(int i = NUM_LIGHTS/2-size; i < NUM_LIGHTS/2+size; i++) {
      leds[i] = CHSV(color, 255, brightness);
    }

    size += 1;

    if(size >= NUM_LIGHTS/2) {
      size = 1;
    }

    show();
  }
}

void prg_fill_from_sides() {
  int size = 1;

  while(sleep(sped)) {

    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i].r *= 0.9;
      leds[i].g *= 0.9;
      leds[i].b *= 0.9;
    }

    for(int i = 0; i < size; i++) {
      leds[i]               = CHSV(color, 255, brightness);
      leds[NUM_LIGHTS-i-1]  = CHSV(color, 255, brightness);
    }

    size += 1;

    if(size > NUM_LIGHTS/2) {
      size = 0;
    }

    show();
  }
}

void prg_fill_from_sides_many_colors() {
  int size = 1;

  while(sleep(sped)) {

    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i].r *= 0.9;
      leds[i].g *= 0.9;
      leds[i].b *= 0.9;
    }

    for(int i = 0; i < size; i++) {
      leds[i]               = CHSV(color+i, 255, brightness);
      leds[NUM_LIGHTS-i-1]  = CHSV(color+i, 255, brightness);
    }

    size += 1;

    if(size > NUM_LIGHTS/2) {
      size = 0;
    }

    show();
  }
}

void prg_fill_from_sides_and_back() {
  int size = 1;
  char dir = 0;

  while(sleep(sped)) {

    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i].r *= 0.9;
      leds[i].g *= 0.9;
      leds[i].b *= 0.9;
    }

    for(int i = 0; i < size; i++) {
      leds[i]               = CHSV(color, 255, brightness);
      leds[NUM_LIGHTS-i-1]  = CHSV(color, 255, brightness);
    }

    size += (dir * 2) - 1;

    if(size >= NUM_LIGHTS/2 || size < 0) {
      dir ^= 1;
    }

    show();
  }
}

void prg_fill_from_sides_and_fade() {
  int size = 1;
  char dir = 0;

  while(sleep(sped)) {

    if(dir == 1) {
      for(int i = 0; i < size; i++) {
        leds[i]               = CHSV(color, 255, brightness);
        leds[NUM_LIGHTS-i-1]  = CHSV(color, 255, brightness);
      }
    } else {
      for(int i = 0; i < (NUM_LIGHTS / 2 - 1) - size; i++) {
        leds[i].r *= 0.9;
        leds[i].g *= 0.9;
        leds[i].b *= 0.9;
        leds[NUM_LIGHTS-i-1].r *= 0.9;
        leds[NUM_LIGHTS-i-1].g *= 0.9;
        leds[NUM_LIGHTS-i-1].b *= 0.9;
      }
    }

    size += (dir * 2) - 1;

    if(size >= NUM_LIGHTS/2 || size < -16) {
      dir ^= 1;
    }

    show();
  }
}

void prg_bouncing_rainbow() {
  int index = 0;
  char dir = 0;

  while(sleep(sped)) {
    if(index >= NUM_LIGHTS || index < 0) {
      dir ^= 1;
    }

    index += (dir * 2) - 1;

    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[(i+index+NUM_LIGHTS)%NUM_LIGHTS] = CHSV(color+i, 255, brightness);
    }
    //rotate((dir * 2) - 1);
    
    show();
  }
}

//TODO make fireworks come from both sides

class FireWork {
public:
  int pos;
  char dir;
  int time;
  bool blew;

  FireWork() {
    pos = random(NUM_LIGHTS);
    dir = random(100) < 50;
    time = random(60);
    blew = false;
  }

  void update() {
    if(time == 0) {
      blew = false;
      pos = (pos + (dir*2)-1 + NUM_LIGHTS * 2) % (NUM_LIGHTS * 2);
    } else {
      time -= 1;
    }
    if(pos == NUM_LIGHTS / 2) {
      blew = true;
      time = 100;
      dir = !dir;
      //pos = (!dir)*NUM_LIGHTS;
      pos = 0;
    }
  }

  void draw() {
    if(!blew) {
      draw_rocket(pos, 12, dir, false);
    } else {
      draw_rocket(NUM_LIGHTS/2, 100, dir, true);
    }
  }
};

void prg_firework() {
  constexpr int tail_size = 16;

  srand(millis());
  
  FireWork fireworks[1];

  while(sleep(sped)) {
    for(CRGB& led : leds) led.nscale8(251);

    for(int i = 0; i < 1; i++) fireworks[i].update();
    for(int i = 0; i < 1; i++) fireworks[i].draw();

    show();
  }
}

class Rocket {
public:
  int pos;
  char dir;

  Rocket() {
    pos = random(NUM_LIGHTS);
    dir = random(100) < 50;
  }

  void update() {
    pos = (pos + (dir*2)-1 + NUM_LIGHTS * 2) % (NUM_LIGHTS * 2);
    if(pos == 0) {
      dir = random(100) < 50;
    }
  }

  void draw() {
    draw_rocket(pos, 12, dir, true);
  }
};

void prg_rocket() {
  constexpr int tail_size = 16;

  srand(millis());
  
  Rocket rockets[3];

  while(sleep(sped)) {
    for(CRGB& led : leds) led.nscale8(251);

    for(int i = 0; i < 3; i++) rockets[i].update();
    for(int i = 0; i < 3; i++) rockets[i].draw();

    show();
  }
}

//TODO make bounces be more realistic by making them lose length completley and then expand again

void prg_bouncing_comets() {
  srand(millis());

  int c = color;

  int pos[2];
  for(int i = 0; i < 2; i++) pos[i] = random(NUM_LIGHTS);

  char dir[2];
  dir[0] = 0;
  dir[1] = 1;

  char color[2];
  for(int i = 0; i < 2; i++) color[i] = random(256);

  while(sleep(sped)) {
    for(CRGB& led : leds) led.nscale8(200);

    for(int i = 0; i < 2; i++) {
      draw_tail_single_color(pos[i], 8, dir[i], color[i]);
      pos[i] = (pos[i] + (dir[i]*2)-1 + NUM_LIGHTS) % (NUM_LIGHTS);

      for(int j = 0; j < 2; j++) {
        if(pos[i] == pos[j] && i != j) {
          color[j] = (color[j] + 5) % 256;
          color[i] = (color[i] + 5) % 256;
          dir[i] = !dir[i];
          dir[j] = !dir[j];
        }
      }

      if(random(10000) > 9940) {
        color[i] = (color[i] + random(60)) % 256;
        pos[i] = (pos[i] + random(8)) % NUM_LIGHTS; //TODO make sure that they dont spawn on the same posisiton
      }
    }
    show();
  }
}

void prg_shifting_color() {
  int i = 0;
  int c = 0;

  clear();

  while(sleep(sped)) {    
    leds[i++] = CHSV(c+color, 255, brightness);

    if(i >= NUM_LIGHTS) {
      i = 0;
      c += 20;
    }

    show();
  }
}

void prg_chasing_single_color() {
  int j = 0;

  while(sleep(sped)) {
    clear();

    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[(i+j)%NUM_LIGHTS] = CHSV(color, 255, ((i % 15) * brightness) / 15);
    }

    j += 1;
    show();
  }
}


void prg_chasing_many_colors() {
  int j = 0;

  while(sleep(sped)) {
    clear();

    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[(i+j)%NUM_LIGHTS] = CHSV(color+i, 255, ((i % 15) * brightness) / 15);
    }

    j += 1;
    show();
  }
}

//TODO make it fade in as well

void prg_flare_ups_single_color() {
  unsigned char indexes[8];
  unsigned char times[8];

  for(int i = 0; i < 8; i++) indexes[i] = random(NUM_LIGHTS);
  for(int i = 0; i < 8; i++) times[i] = random(256);
  
  while (sleep(sped)) {
    clear();

    for(int i = 0; i < 8; i++) {
      for(int j = -4; j < 5; j++) {
        CHSV led = rgb2hsv_approximate(leds[max(min(indexes[i]+j, NUM_LIGHTS-1), 0)]);
        led.v = min((led.v + ((4 - abs(j)) * times[i]) / 4), 255);
        leds[max(min(indexes[i]+j, NUM_LIGHTS-1), 0)] = CHSV(color, 255, led.v);
      }
    }

    for(int i = 0; i < 8; i++) {
      if(times[i]-- == 0) {
        times[i] = 255;
        indexes[i] = random(NUM_LIGHTS);
      }
    }

    show();
  }
}

//TODO make it fade in as well

void prg_flare_ups_many_colors() {
  unsigned char indexes[8];
  unsigned char times[8];
  unsigned char colors[8];

  for(int i = 0; i < 8; i++) indexes[i] = random(NUM_LIGHTS);
  for(int i = 0; i < 8; i++) times[i] = random(256);
  for(int i = 0; i < 8; i++) colors[i] = random(64);
  
  while (sleep(sped)) {
    clear();

    for(int i = 0; i < 8; i++) {
      for(int j = -4; j < 5; j++) {
        CHSV led = rgb2hsv_approximate(leds[max(min(indexes[i]+j, NUM_LIGHTS-1), 0)]);
        led.v = min((led.v + ((4 - abs(j)) * times[i]) / 4), 255);
        leds[max(min(indexes[i]+j, NUM_LIGHTS-1), 0)] = CHSV(colors[i]+color, 255, led.v);
      }
    }

    for(int i = 0; i < 8; i++) {
      if(times[i]-- == 0) {
        times[i] = 255;
        indexes[i] = random(NUM_LIGHTS);
      }
    }

    show();
  }
}

void prg_off() {
  for(CRGB& l : leds) l = CRGB(0, 0, 0);
  show();
  while(sleep(10));   
}

void prg_sound_single_color() {
  while(sleep(sped)) {
    int val = avrage_sound*5;
    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i] = CHSV(val, 255, brightness);
    } 
    show();
  }
}

void prg_sound_many_colors() {
  while(sleep(sped)) {
    float val = avrage_sound / 8.0f;
    //Serial.println(val);
    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i] = CHSV(color*val+(1.0-val)*i, 255, brightness);
    } 
    show();
  }
}

void prg_sound_single_color_fade() {
  while(sleep(sped)) {
    int val = avrage_sound*5;
    //Serial.println(val);
    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i] = CHSV(color, val, brightness);
    } 
    show();
  }
}

void prg_sound_rotating() {
  while(sleep(sped)) {
    int val = avrage_sound;
    //Serial.println(val);
    leds[0] = CHSV(COLOR_LVLS[val%NUM_COLOR_LVLS], 255, brightness); 
    show();
    rotate(1);
  }
}

#endif