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
  last_program = 0;
  program = 0;//NUM_PROGS-1;
  sped = 10;
  brightness = 128;
  color = 100;
}

void poll_inputs() {
  static char num_str[4] = "000";
  static char num_index = 0;
  static int num = 0;

  if(num_index == 3) {
    num = atoi(num_str);
    Serial.println(num_str);
    num_str[0] = '0';
    num_str[1] = '0';
    num_str[2] = '0';
    num_index = 0;
  }

  if(irrecv.decode(&results)) {
    // Print Code in HEX
    Serial.println(results.value, HEX);
    irrecv.resume();

    IRCode ircode = (IRCode)results.value;

    switch(ircode) {
      case IRCode::OK:
        if(program == -1) program = last_program;
        else              program = -1;
        break;
      case IRCode::LEFT:
        color += 20;
        //color = num % 256;
        break;
      case IRCode::RIGHT:
        sped = (sped % 40) + 5;
        //sped = (num < 1) * 1 + num;
        break;
      case IRCode::UPP:
        program = (program + 1) % NUM_PROGS;
        //program = num % NUM_PROGS;
        last_program = program;
        break;
      case IRCode::DOWN:
        brightness = (brightness + 32) % 256;
        //brightness = num % 256;
        break;
      case IRCode::HASHTAG:
        reset();
        break;
      case IRCode::ASTERIX:
        Serial.println("DEBUG INFO:");
        Serial.print("Program:");     Serial.println(program);
        Serial.print("Speed:");       Serial.println(sped);
        Serial.print("Brightness:");  Serial.println(brightness);
        Serial.print("Color:");       Serial.println(color);
        break;
      case IRCode::ZERO:
        num_str[num_index++] = '0';
        break;
      case IRCode::ONE:
        num_str[num_index++] = '1';
        break;
      case IRCode::TWO:
        num_str[num_index++] = '2';
        break;
      case IRCode::THREE:
        num_str[num_index++] = '3';
        break;
      case IRCode::FOUR:
        num_str[num_index++] = '4';
        break;
      case IRCode::FIVE:
        num_str[num_index++] = '5';
        break;
      case IRCode::SIX:
        num_str[num_index++] = '6';
        break;
      case IRCode::SEVEN:
        num_str[num_index++] = '7';
        break;
      case IRCode::EIGHT:
        num_str[num_index++] = '8';
        break;
      case IRCode::NINE:
        num_str[num_index++] = '9';
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

  /*program = ((millis() / 1000) / 4) % 14;
  if(current_program != program) 
    color = random(256);*/

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

  sleep( 1500 ); // power-up safety sleep
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LIGHTS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness( 80 );
  //FastLED.addLeds<NEOPIXEL, 6>(leds, NUM_LIGHTS);

  reset();
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
    //case 15: prg_ping_pong_many_colors();   break;
    case 15: prg_stars_single_color();      break;
    default:
      Serial.print("PROGRAM ID");
      Serial.print(program, DEC);
      Serial.println(" IS INVALID!!!");
      sleep(2000);
      break;
  }
}
