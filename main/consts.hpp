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

#ifndef CONSTS_H_INCLUDED
#define CONSTS_H_INCLUDED

#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
#define LED_PIN     5

constexpr unsigned long ARDUINO_COMMUNICATION_BAUD_RATE = 9600;
constexpr unsigned long RUST_PROGRAM_BAUD_RATE = 500000;

// Define sensor pin
constexpr int RECV_PIN = 4;

constexpr int NUM_PROGS = 46;
constexpr int NUM_LIGHTS = 150;

constexpr long din_mamma_1 = 0x7100AB;
constexpr long din_mamma_2 = 0xFF35AB;

constexpr int NUM_SPEED_LVLS = 10;

const int SPEED_LVLS[NUM_SPEED_LVLS] = {
    1, 2, 4, 8, 16, 32, 64, 128, 256, 512
};

constexpr int NUM_BRIGHTNESS_LVLS = 10;

const int BRIGHTNESS_LVLS[NUM_BRIGHTNESS_LVLS] = {
    0, 25, 50, 75, 100, 125, 150, 175, 200, 255
};

constexpr int NUM_COLOR_LVLS = 10;

const int COLOR_LVLS[NUM_COLOR_LVLS] = {
    0, //RED
    16,//ORANGE
    48,//YELLOW
    76,//LIGHT_GREEN
    96,//GREEN
    108,//TEAL
    132,//LIGHT_BLUE
    160,//BLUE
    184,//PURPLE
    220,//PINK
};

#endif