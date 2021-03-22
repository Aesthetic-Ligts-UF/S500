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

#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

#define DEBUG

#ifdef DEBUG
#define DEBUG_LOG(...) Serial.print(__VA_ARGS__); 
#define DEBUG_LOGLN(...) Serial.println(__VA_ARGS__); 
#else
#define DEBUG_LOG(...)
#define DEBUG_LOGLN(...)
#endif

enum class IRCode : long long {
  None    = 0x000000,
  One     = 0xFFA25D,
  Two     = 0xFF629D,
  Three   = 0xFFE21D,
  Four    = 0xFF22DD,
  Five    = 0xFF02FD,
  Six     = 0xFFC23D,
  Seven   = 0xFFE01F,
  Eight   = 0xFFA857,
  Nine    = 0xFF906F,
  Zero    = 0xFF9867,
  Asterix = 0xFF6897,
  Hashtag = 0xFFB04F,
  Upp     = 0xFF18E7,
  Down    = 0xFF4AB5,
  Right   = 0xFF5AA5,
  Left    = 0xFF10EF,
  Ok      = 0xFF38C7,
  Repeat  = 0xFFFFFFFF
};

void reset();
void poll_inputs();
bool sleep(long int ms);
void show();
void clear();
void rotate(char amount);
void draw_tail_single_color(unsigned char pos, char length, char dir, int color);
void draw_tail_many_colors(unsigned char pos, char length, char dir, int color);
void draw_rocket(int pos, char length, char dir, bool blow);
void poll_sound();
void poll_input();

#endif