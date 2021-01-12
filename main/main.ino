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
#include <FastLED.h>
#include <IRremote.h>

// Define sensor pin
constexpr int RECV_PIN = 4;
 
// Define IR Receiver and Results Objects
IRrecv irrecv(RECV_PIN);
decode_results results;

constexpr int NUM_PROGS = 16;
constexpr int NUM_LIGHTS = 100;
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define LED_PIN     5

CRGB leds[NUM_LIGHTS];

int program = 7;
int sped = 10;
int brightness = 200;
int color = 100;

constexpr long din_mamma_1 = 0x7100AB;
constexpr long din_mamma_2 = 0xFF35AB;

enum class IRCode : long int {
  ONE     = 0xFFA25D,
  TWO     = 0xFF629D,
  THREE   = 0xFFE21D,
  FOUR    = 0xFF22DD,
  FIVE    = 0xFF02FD,
  SIX     = 0xFFC23D,
  SEVEN   = 0xFFE01F,
  EIGHT   = 0xFFA857,
  NINE    = 0xFF906F,
  ZERO    = 0xFF9867,
  ASTERIX = 0xFF6897,
  HASHTAG = 0xFFB04F,
  UPP     = 0xFF18E7,
  DOWN    = 0xFF4AB5,
  RIGHT   = 0xFF5AA5,
  LEFT    = 0xFF10EF,
};

void poll_inputs() {
  //TODO fill in code to poll innput from the IR sensor
  if (irrecv.decode(&results)) {
    // Print Code in HEX
    Serial.println(results.value, HEX);
    irrecv.resume();

    IRCode ircode = (IRCode)results.value;

    switch(ircode) {
      case IRCode::UPP:
        program = (program + 1) % 16;
        break;
      case IRCode::DOWN:
        program = (NUM_PROGS + (program - 1)) % 16;
        break;
      default:
        break;
    }
  }
}

//TODO return a bool if the current program should be changed
bool sleep(long int ms) {
  int current_program = program;
  unsigned long start_time = millis();
  while(millis() < start_time + ms) {
    poll_inputs();
  }

  //program = ((millis() / 1000) / 4) % 14;
  if(current_program != program) 
    color = random(256);

  return current_program == program;
}

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();

  sleep( 60000000 ); // power-up safety sleep
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LIGHTS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( 80 );
  //FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LIGHTS);
}

void prg_epelepsi_many_colors() {
  char change[NUM_LIGHTS];

  for(int i = 0; i < NUM_LIGHTS; i++)  {
    sleep(sped);
    leds[i] = CHSV(color%255, 255, brightness%255);
    if(random(2) == 0) change[i] = 1;
    else change[i] = -1;
  }

  char c = 0;
  while(sleep(sped)) {
    
    for(int i = 0; i < NUM_LIGHTS; i++)  {
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

  while(sleep(sped)) {
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
    leds[i] = CHSV(color, 255, (brightness+random(80))%255);
    if(random(2) == 0) change[i] = 1;
    else change[i] = -1;
  }

  char c = 0;

  while(sleep(sped)) {
    for(int i = 0; i < NUM_LIGHTS; i++)  {
      //sleep(sped);
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
  while(sleep(sped)) {
    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i] = CHSV(color, 255, brightness);
    }
    FastLED.show();
  }
}

void prg_many_colors() {
  while(sleep(sped)) {
    for(int i = 0; i < NUM_LIGHTS; i++) {
      leds[i] = CHSV(color+((float)i/NUM_LIGHTS)*160, 255, brightness);
    }
    FastLED.show();
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

    FastLED.show();
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

    FastLED.show();
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

    FastLED.show();
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

    FastLED.show();
  }
}

void prg_comet_single_color() {
  int trail_length = 12;
  for(int i = 0; i < NUM_LIGHTS+trail_length; i++) {
    if(i > trail_length-1 && i < NUM_LIGHTS+trail_length) { leds[i-trail_length] = CRGB(0, 0, 0); }
    for(int j = 0; j < trail_length; j++) {
      if(i-j > 0 && i-j < NUM_LIGHTS) {
        leds[i-j] = CHSV(color, 255, brightness * (1.0 - (float)j/trail_length));
      }
    }
    sleep(sped);
    FastLED.show();
  }
}

void prg_comet_many_colors() {
  int trail_length = 12;
  for(int i = 0; i < NUM_LIGHTS+trail_length; i++) {
    if(i > trail_length-1 && i < NUM_LIGHTS+trail_length) { leds[i-trail_length] = CRGB(0, 0, 0); }
    for(int j = 0; j < trail_length; j++) {
      if(i-j > 0 && i-j < NUM_LIGHTS) {
        leds[i-j] = CHSV(color+i, 255, brightness * (1.0 - (float)j/trail_length));
      }
    }
    sleep(sped);
    FastLED.show();
  }
}

void prg_ping_pong_single_color() {
  static char dir = 0;

  int trail_length = 12;
  for(int i = 0; i < NUM_LIGHTS+trail_length; i++) {
    if(i > trail_length-1 && i < NUM_LIGHTS+trail_length) { leds[i-trail_length] = CRGB(0, 0, 0); }
    for(int j = 0; j < trail_length; j++) {
      if(i-j > 0 && i-j < NUM_LIGHTS) {
        leds[abs((NUM_LIGHTS * -dir)+(i-j))] = CHSV(color, 255, brightness * (1.0 - (float)j/trail_length));
      }
    }
    sleep(sped);
    FastLED.show();
  }

  dir = !dir;
}

void prg_ping_pong_many_colors() {
  static char dir = 0;

  int trail_length = 12;
  for(int i = 0; i < NUM_LIGHTS+trail_length; i++) {
    if(i > trail_length-1 && i < NUM_LIGHTS+trail_length) { leds[i-trail_length] = CRGB(0, 0, 0); }
    for(int j = 0; j < trail_length; j++) {
      if(i-j > 0 && i-j < NUM_LIGHTS) {
        leds[abs((NUM_LIGHTS * -dir)+(i-j))] = CHSV(color+i, 255, brightness * (1.0 - (float)j/trail_length));
      }
    }
    sleep(sped);
    FastLED.show();
  }

  dir = !dir;
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
    FastLED.show();
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

    FastLED.show();
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
    FastLED.show();
  }
}

void prg_off() {
  for(CRGB& l : leds) l = CRGB(0, 0, 0);
  FastLED.show();
  while(sleep(1000));   
}

void loop() {
  switch (program) {
    case-1: prg_off();                      break;
    case 0: prg_single_color();             break;
    case 1: prg_many_colors();              break;
    case 2: prg_comet_single_color();       break;
    case 3: prg_comet_many_colors();        break;
    case 4: prg_sin_single_color();         break;
    case 5: prg_sin_many_colors();          break;
    case 6: prg_epelepsi_single_color();    break;
    case 7: prg_epelepsi_many_colors();     break;
    case 8: prg_epelepsi_all_colors();      break;
    case 9: prg_fade_in_out_single_color(); break;
    case 10: prg_fade_in_out_many_colors(); break;
    case 11: prg_random();                  break;
    case 12: prg_christmas();               break;
    case 13: prg_rainbow();                 break;
    case 14: prg_ping_pong_single_color();  break;
    case 15: prg_ping_pong_many_colors();  break;
    default:
      Serial.print("PROGRAM ID");
      Serial.print(program, DEC);
      Serial.println(" IS INVALID!!!");
      break;
  }
}
