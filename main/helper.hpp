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
  OK      = 0xFF38C7
};

void reset();
void poll_inputs();
bool sleep(long int ms);
void show();
void clear();

#endif