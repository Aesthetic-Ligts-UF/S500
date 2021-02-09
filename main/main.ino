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
#define DEBUG
#include <IRremote.h>
#include "globals.hpp"
#include "consts.hpp"
#include "prgs.hpp"
#include "helper.hpp"

void clear() {
  for(int i = 0; i < NUM_LIGHTS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
}

void reset() {
  program = 0;
  last_program = program;
  sped = 1;
  brightness = 128;
  color = COLOR_LVLS[0];
  sound_index = 0;
  avrage_sound = 0;

  clear();
}

void poll_sound() {
  //Serial.println(analogRead(A0));
  sound_lvls[sound_index++] = max(analogRead(A0) - STANDARD_SOUND_LVL, 0);

  if(sound_index >= 8) {
    sound_index = 0;
  }

  if(sound_index == 0) {
    long int sum = 0;
    for(int i = 0; i < 8; i++) {
      sum += sound_lvls[i];
    }
    avrage_sound = sum / 8;
    //Serial.println(avrage_sound);
  }

  //Serial.println(analogRead(A0));
}

void poll_inputs() {
  static char num_str[4] = "0\0\0";
  static char num_index = 0;
  static int num = 0;
  static long int num_last_time = 0;
  static long int num_reset_time = 0;
  static char last_char = 0;
  //color = COLOR_LVLS[(millis()/2000)%12];

  if(millis() > num_last_time + 2000 && num_index != 0) {
    num_index = 3;
  }

  if(num_index == 3) {
    num = atoi(num_str);
    
    if(num_str[2] != '\0') {
      last_char = num_str[2] - '0';
    } else if(num_str[1] != '\0') {
      last_char = num_str[1] - '0';
    } else {
      last_char = num_str[0] - '0';
    }

    Serial.print("User inputed: ");
    Serial.println(num_str);
    Serial.print("Last digit: ");
    Serial.println(int(last_char));

    num_str[0] = '0';
    num_str[1] = '\0';
    num_str[2] = '\0';
    num_index = 0;
    num_reset_time = millis();
  }

  if(millis() > num_reset_time + 15000) {
    //num = 0;
  }


  if(irrecv.decode(&results)) {
    // Print Code in HEX
    Serial.print("Infra red signal: ");
    Serial.println(results.value, HEX);
    
    if (results.overflow) {
      irparams = irparams_struct{};
      irrecv = IRrecv(RECV_PIN);
      results = decode_results{};
      Serial.println("ERROR Overflow detected!!!");
    }

    irrecv.resume();

    IRCode ircode = (IRCode)results.value;

    switch(ircode) {
      case IRCode::Zero:
        num_str[num_index++] = '0';
        num_last_time = millis();
        break;
      case IRCode::One:
        num_str[num_index++] = '1';
        num_last_time = millis();
        break;
      case IRCode::Two:
        num_str[num_index++] = '2';
        num_last_time = millis();
        break;
      case IRCode::Three:
        num_str[num_index++] = '3';
        num_last_time = millis();
        break;
      case IRCode::Four:
        num_str[num_index++] = '4';
        num_last_time = millis();
        break;
      case IRCode::Five:
        num_str[num_index++] = '5';
        num_last_time = millis();
        break;
      case IRCode::Six:
        num_str[num_index++] = '6';
        num_last_time = millis();
        break;
      case IRCode::Seven:
        num_str[num_index++] = '7';
        num_last_time = millis();
        break;
      case IRCode::Eight:
        num_str[num_index++] = '8';
        num_last_time = millis();
        break;
      case IRCode::Nine:
        num_str[num_index++] = '9';
        num_last_time = millis();
        break;
      case IRCode::Upp: case IRCode::Left: case IRCode::Down: case IRCode::Right:
        if(num_index != 0)
          num_index = 3;
        break;
      default:
        break;
    }

    if(num_index == 3) {
      num = atoi(num_str);
      
      if(num_str[2] != '\0') {
        last_char = num_str[2] - '0';
      } else if(num_str[1] != '\0') {
        last_char = num_str[1] - '0';
      } else {
        last_char = num_str[0] - '0';
      }

      Serial.print("User inputed: ");
      Serial.println(num_str);
      Serial.print("Last digit: ");
      Serial.println(int(last_char));

      num_str[0] = '0';
      num_str[1] = '\0';
      num_str[2] = '\0';
      num_index = 0;
      num_reset_time = millis();
    }
    
    switch(ircode) {
      case IRCode::Ok:
        if(program == -1) program = last_program;
        else              program = -1;
        break;
      case IRCode::Left:
        //color = (color + 20) % 256;
        color = COLOR_LVLS[num % NUM_COLOR_LVLS];
        break;
      case IRCode::Right:
        //sped = (sped % 40) + 5;
        //sped = (num < 1) * 1 + num;
        //sped = SPEED_LVLS[num % NUM_SPEED_LVLS];
        sped = SPEED_LVLS[last_char];
        break;
      case IRCode::Upp:
        clear();
        //program = (program + 1) % NUM_PROGS;
        program = num % NUM_PROGS;
        last_program = program;
        break;
      case IRCode::Down:
        //brightness = (brightness + 32) % 256;
        //brightness = num % 256;
        brightness = BRIGHTNESS_LVLS[num % NUM_BRIGHTNESS_LVLS];
        break;
      case IRCode::Hashtag:
        reset();
        break;
      case IRCode::Asterix:
        Serial.println("DEBUG INFO:");
        Serial.print("Program:");     Serial.println(program);
        Serial.print("Speed:");       Serial.println(sped);
        Serial.print("Brightness:");  Serial.println(brightness);
        Serial.print("Color:");       Serial.println(color);
        Serial.print("Num:");         Serial.println(num);

        break;
      default:
        break;
    }
  }
}

void rotate(char amount) {
  CRGB temp[NUM_LIGHTS];  

  for(int i = 0; i < NUM_LIGHTS; i++) {
    temp[(i+amount+NUM_LIGHTS)%NUM_LIGHTS] = leds[i%NUM_LIGHTS];
  }

  for(int i = 0; i < NUM_LIGHTS; i++) {
    leds[i] = temp[i];
  }
}

void draw_tail_single_color(unsigned char pos, char length, char dir, int color) {
  for(int j = 0; j < length; j++) {
    if(pos-j > 0 && pos-j < NUM_LIGHTS) {
      //leds[abs((NUM_LIGHTS * -dir)+(pos-j))] = CHSV(color, 255, brightness * (1.0 - (float)j/length));
      leds[pos-j] = CHSV(color, 255, brightness * (1.0 - (float)((length-1)*-dir+j)/length));
    }
  }
}

void draw_tail_many_colors(unsigned char pos, char length, char dir, int color) {
  for(int j = 0; j < length; j++) {
    if(pos-j > 0 && pos-j < NUM_LIGHTS) {
      leds[pos-j] = CHSV(color+pos-j, 255, brightness * (1.0 - (float)((length-1)*-dir+j)/length));
    }
  }
}


void draw_rocket(int pos, char length, char dir, bool blow) {
  if(!blow) {
    for(int j = 0; j < length; j++) {
      if(pos-j >= 0 && pos-j < NUM_LIGHTS) {
        leds[pos-j] = CHSV(color, 205, brightness * (1.0 - (float)((length-1)*-dir+j)/length));
      }
    }
  } else {
    for(int i = 0; i < 6; i++) {
      int index = pos+random(32)-16;
      if(index >= 0 && index < NUM_LIGHTS) {
        CHSV led = rgb2hsv_approximate(leds[index]);// = CHSV(color, 205, min(255, max(brightness+random(64)-32, 0)));
        led.v += random(32)+brightness-16;
        led.h = color;
        led.s = 205;
        leds[index] = led;
      }
    }
  }
}

//TODO make it not give try to use changing pgs as a prg of it self
bool sleep(long int ms) {
  int current_program = program;

  static unsigned long start_time = millis();
  static bool rotating = false;

  do {
    poll_sound();
    poll_inputs();
  } while(millis() < start_time + ms);

  start_time = millis();

  if(program != -1) {
    if(current_program != program) {
      rotating = false;
    }

    if(program == NUM_PROGS-1) {
      rotating = true;
    }

    if(rotating) {
      program = ((millis() / 1000) / 4) % (NUM_PROGS - 1);
    }
  }

  return current_program == program;
}

void show() {
  if(irrecv.isIdle()) {
    FastLED.show();
  }
}

void setup() {
  Serial.begin(9600);
  irrecv.enableIRIn();

  Serial.println("Start up!");

  sleep( 1500 ); // power-up safety sleep

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LIGHTS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( 255 );

  reset();

  /*for(int i : COLOR_LVLS) {
    Serial.println(i);
  }*/
}

void loop() {
  switch (program) {
    case-1: prg_off();                                break;
    case 0: prg_single_color();                       break;
    case 1: prg_many_colors();                        break;
    case 2: prg_comet_single_color();                 break;
    case 3: prg_comet_many_colors();                  break;
    case 4: prg_sin_single_color();                   break;
    case 5: prg_sin_many_colors();                    break;
    case 6: prg_epelepsi_single_color();              break;
    case 7: prg_epelepsi_many_colors();               break;
    case 8: prg_epelepsi_all_colors();                break;
    case 9: prg_fade_in_out_single_color();           break;
    case 10: prg_fade_in_out_many_colors();           break;
    case 11: prg_random();                            break;
    case 12: prg_christmas();                         break;
    case 13: prg_rainbow();                           break;
    case 14: prg_rainbow_every_other();               break;
    case 15: prg_rainbow_every_other_rotating();      break;
    case 16: prg_ping_pong_single_color();            break;
    case 17: prg_ping_pong_many_colors();             break;
    case 18: prg_stars_single_color();                break;
    case 19: prg_stars_all_color();                   break;
    case 20: prg_snake();                             break;
    case 21: prg_grayscale();                         break;
    case 22: prg_fade_between_single_colors();        break;
    case 23: prg_fade_between_many_colors();          break;
    case 24: prg_every_other_led();                   break;
    case 25: prg_every_other_led_fade();              break;
    case 26: prg_fill_from_center();                  break;
    case 27: prg_fill_from_sides();                   break;
    case 28: prg_fill_from_sides_and_back();          break;
    case 29: prg_fill_from_sides_and_fade();          break;
    case 30: prg_bouncing_rainbow();                  break;
    case 31: prg_every_other_led_rotating();          break;
    case 32: prg_firework();                          break;
    case 33: prg_fade_to_white_single_color_change(); break;
    case 34: prg_fade_to_white_many_colors();         break;
    case 35: prg_fade_to_white_single_color();        break;
    case 36: prg_many_comets_single_color();          break;
    case 37: prg_many_comets_many_colors();           break;
    case 38: prg_many_comets_single_color_one_dir();  break;
    case 39: prg_bounce();                            break;
    case 40: prg_comet_shifting_color();              break;
    case 41: prg_chasing_single_color();              break;
    case 42: prg_chasing_rainbow();                   break;
    case 43: prg_flare_ups_single_color();            break;
    case 44: prg_flare_ups_many_colors();             break;
    case 45: prg_sound_single_color();                break;
    case 46: prg_sound_many_colors();                 break;
    case 47: prg_sound_single_color_fade();           break;
    case 48: prg_sound_rotating();                    break;
    default:
      Serial.print("PROGRAM ID ");
      Serial.print(program, DEC);
      Serial.println(" IS INVALID!!!");
      sleep(2000);
      break;
  }
}
