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
  sped = SPEED_LVLS[5];
  brightness = 128;
  color = COLOR_LVLS[6];
  paused = false;
  last_command = IRCode::Upp;
  clear();
}

void poll_pc() {
  if (Serial.available() == 0) return;
  String command = Serial.readStringUntil(' ');
  //uint8_t args[1] = {Serial.read()};
  //uint8_t args[1];
  //Serial.readBytesUntil(0, args, 1);
  int arg = Serial.readString().toInt();
  Serial.println(command);
  if (command == "Program") {
    int prg = arg;
    program = prg % NUM_PROGS;
    DEBUG_LOG("Set program to id: ");
    DEBUG_LOGLN(program);
  } else if (command == "Brightness") {
    brightness = arg;
    DEBUG_LOG("Set brightness to lvl: ");
    DEBUG_LOGLN(brightness);
  } else if (command == "Speed") {
    sped = arg;
    DEBUG_LOG("Set speed to lvl: ");
    DEBUG_LOGLN(sped);
  } else if (command == "Color") {
    color = arg;
    DEBUG_LOG("Set color to lvl: ");
    DEBUG_LOGLN(color);
  } else if (command == "RustProgram") {
    int enable = arg;
    if (enable) {
      program = 45;
    } else {
      program = 0;
    }
  } else {
    DEBUG_LOG("Unknown command entered!");
    DEBUG_LOGLN(command);
  }
  /*switch (command) {
    case Program:
      int prg = args[0];
      program = prg % NUM_PROGS;
      DEBUG_LOG("Set program to id: ");
      DEBUG_LOGLN(program);
      break;
    case Brightness:
      brightness = args[0];
      DEBUG_LOG("Set brightness to lvl: ");
      DEBUG_LOGLN(brightness);
      break;
    case Speed:
      sped = args[0];
      DEBUG_LOG("Set speed to lvl: ");
      DEBUG_LOGLN(sped);
      break;
    case Color:
      color = args[0];
      DEBUG_LOG("Set color to lvl: ");
      DEBUG_LOGLN(color);
      break;
    case RustProgram:
      int enable = args[0];
      if (enable) {
        program = 45;
      } else {
        program = 0;
      }
      break;
    default:
      DEBUG_LOG("Unknown command entered!");
      DEBUG_LOGLN(command);
      break;
  }*/
}

void poll_ir() {
  static char num_str[4] = "0\0\0";
  static char num_index = 0;
  static int num = 0;
  static long int num_last_time = 0;
  static long int num_reset_time = 0;
  static char last_char = 0;

  if(millis() > num_last_time + 2000 && num_index != 0) {
    num_index = 3;
  }

  if(irrecv.decode(&results)) {
    // Print Code in HEX
    DEBUG_LOG("Infra red signal: ");
    DEBUG_LOGLN(results.value, HEX);
    
    if(results.overflow) {
      irparams = irparams_struct{};
      irrecv = IRrecv(RECV_PIN);
      results = decode_results{};
      DEBUG_LOGLN("ERROR Overflow detected!!!");
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
    
    switch(ircode) {
      case IRCode::Ok:
        if(program != -1) {
          program = (program + 1) % NUM_PROGS;
          last_program = program;
          DEBUG_LOG("Set program to id: ");
          DEBUG_LOGLN(program);
        }
        break;
      case IRCode::Left: case IRCode::Right: case IRCode::Upp: case IRCode::Down:
        if(program != -1) {
          last_command = ircode;
          if(paused) {
            num_index = 3;
            break;
          }

          paused = true;
        }
        break;
      case IRCode::Hashtag:
        if(program != -1) reset();
        break;
      case IRCode::Asterix:
        if(program == -1) program = last_program;
        else              program = -1;
        break;
      default:
        break;
    }
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

    DEBUG_LOG("User inputed: ");
    DEBUG_LOGLN(num_str);
    DEBUG_LOG("Last digit: ");
    DEBUG_LOGLN(int(last_char));

    num_str[0] = '0';
    num_str[1] = '\0';
    num_str[2] = '\0';
    num_index = 0;
    num_reset_time = millis();

    if(paused) {
      paused = false;
      switch(last_command) {
        case IRCode::Upp:
          program = num % NUM_PROGS;
          last_program = program;
          DEBUG_LOG("Set program to id: ");
          DEBUG_LOGLN(program);
          break;
        case IRCode::Down:
          brightness = BRIGHTNESS_LVLS[last_char];
          DEBUG_LOG("Set brightness to lvl: ");
          DEBUG_LOGLN(brightness);
          break;
        case IRCode::Right:
          sped = SPEED_LVLS[NUM_SPEED_LVLS - last_char];
          DEBUG_LOG("Set speed to lvl: ");
          DEBUG_LOGLN(sped);
          break;
        case IRCode::Left:
          color = COLOR_LVLS[last_char];
          DEBUG_LOG("Set color to lvl: ");
          DEBUG_LOGLN(color);
          break;
        default:
          DEBUG_LOGLN("Unknown command entered! This should only happen if you just press the numpad and don't select any command!");
          break;
      }
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
      if(dir) leds[pos-j] = CHSV(color, 255, brightness * (1.0 - (float)((length-1)*dir+j*-dir)/length));
      else    leds[pos-j] = CHSV(color, 255, brightness * (1.0 - (float)j/length));
      //DEBUG_LOGLN(brightness * (1.0 - (float)((length-1)*dir+j*-dir)/length));
    }
  }
  //while(1);
}

void draw_tail_many_colors(unsigned char pos, char length, char dir, int color) {
  for(int j = 0; j < length; j++) {
    if(pos-j > 0 && pos-j < NUM_LIGHTS) {
      if(dir) leds[pos-j] = CHSV(color+pos-j, 255, brightness * (1.0 - (float)((length-1)*dir+j*-dir)/length));
      else    leds[pos-j] = CHSV(color+pos-j, 255, brightness * (1.0 - (float)j/length));
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
      int index = pos+random(length)-length/2;
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
    //poll_ir();
    poll_pc();
  } while(millis() < start_time + ms || !irrecv.isIdle() || paused);

  start_time = millis();

  return current_program == program;
}

void show() {
  if(irrecv.isIdle()) {
    FastLED.show();
  }
}

void setup() {
  Serial.begin(BAUD_RATE);//500000/ 216000 / 115200 /9600
  Serial.setTimeout(10);
  irrecv.enableIRIn();

  sleep( 1500 ); // power-up safety sleep

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LIGHTS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( 255 );

  reset();
}

void loop() {
  switch (program) {
    case-1: prg_off();                                break;
    case 0: prg_single_color();                       break;
    case 1: prg_many_colors();                        break;
    case 2: prg_sin_single_color();                   break;
    case 3: prg_sin_many_colors();                    break;
    case 4: prg_comet_single_color();                 break;
    case 5: prg_comet_many_colors();                  break;
    case 6: prg_many_comets_single_color();           break;
    case 7: prg_many_comets_many_colors ();           break;
    case 8: prg_many_comets_single_color_one_dir ();  break;
    case 9: prg_shifting_color ();                    break;
    case 10: prg_bouncing_comets();                   break;
    case 11: prg_chasing_single_color();              break;
    case 12: prg_chasing_many_colors();               break;
    case 13: prg_epelepsi_single_color ();            break;
    case 14: prg_epelepsi_many_colors ();             break;
    case 15: prg_epelepsi_all_colors ();              break;
    case 16: prg_fill_from_center_many_colors();      break;
    case 17: prg_fill_from_sides_many_colors();       break;
    case 18: prg_rocket();                            break;
    case 19: prg_firework();                          break;
    case 20: prg_ping_pong_single_color();            break;
    case 21: prg_ping_pong_many_colors();             break;
    case 22: prg_stars_single_color();                break;
    case 23: prg_stars_all_color();                   break;
    case 24: prg_snake();                             break;
    case 25: prg_fade_between_single_colors();        break;
    case 26: prg_fade_between_many_colors();          break;
    case 27: prg_every_other_led();                   break;
    case 28: prg_every_other_led_fade();              break;
    case 29: prg_fill_from_center();                  break;
    case 30: prg_fill_from_sides();                   break;
    case 31: prg_fill_from_sides_and_back();          break;
    case 32: prg_fill_from_sides_and_fade();          break;
    case 33: prg_fade_in_out_single_color();          break;
    case 34: prg_fade_in_out_many_colors();           break;
    case 35: prg_every_other_led_rotating();          break;
    case 36: prg_bouncing_rainbow();                  break;
    case 37: prg_white();                             break;
    case 38: prg_fade_to_white_single_color();        break;
    case 39: prg_fade_to_white_many_colors();         break;
    case 40: prg_fade_to_white_single_color_change(); break;
    case 41: prg_random();                            break;
    case 42: prg_christmas();                         break;
    case 43: prg_flare_ups_single_color();            break;
    case 44: prg_flare_ups_many_colors();             break;
    case 45: prg_custom();                            break;
    default:
      Serial.print("PROGRAM ID ");
      Serial.print(program, DEC);
      Serial.println(" IS INVALID!!!");
      sleep(2000);
      break;
  }
}
