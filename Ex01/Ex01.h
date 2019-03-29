// ---------------------------------------------------------
// Ex01.h
// Header file for Exercise 1.
//
// Author: Jürgen Vogl <codewerfer>
// Last Modification: 23.03.2019
//
// (c) Jürgen Vogl, 2019
// ----------------------------------------------------------

#pragma once

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>

#include <iostream>
#include <fstream>
#include <string>

#ifdef _WIN32

#include <ctime>

#endif

#include "Drawing.h"
#include "Segment.h"

// width of window
#define W 800
// height of window
#define H 600
// iteration, how often the ray will be reflected
#define T 50

// random room definitions - as used with argc 1
// number of mirrors
#define N 2
// number of walls
#define WALLCOUNT 4
// room boundaries
#define P0 0,   0
#define P1 W-1, 0
#define P2 W-1, H-1
#define P3 0,   H-1

using namespace std;
using namespace compsys;

enum options {
  RANDOM_INPUT = 1, FILE_INPUT = 2
};

void init(/*in*/ int option, const char **filename,
        /*out*/ Segment &ray, int &mirrorCount, Segment *&mirrors);

void drawMirrors(int mirrorCount, Segment mirrors[]);

void drawRay(Segment ray);

void reflectRay(/*in*/ int mirrorCount, Segment mirrors[], Segment ray,
        /*out*/ Segment &rayflection);

// inits a random ray, random mirrors and set mirrorCount to N+4
// ray and mirrors have a length of least 1 and values between 0 and W for x
// and 0 and H for y
void randomInit(Segment &ray, int &mirrorCount, Segment *&mirrors);

// inits ray, mirrorCount and mirrors from given filename
// will open file from filename and close it
void fileInit(/*in*/ const string filename,
        /*out*/ Segment &ray, int &mirrorCount, Segment *&mirrors);

// prints values to stdout
void printValues(const Segment ray, const int count, const Segment mirrors[]);

// rand between min (incl.) and max (excl.)
int rand(int min, int max);

// rand from 0 (incl.) to max (excl.)
int rand(int max) { return rand(0, max); }

// given and unmodified main method from specification Ex01
// argc is used as an option, 1 is random, 2 is read of a file
// argv is the filename
// more arguments will result in an random run
int main(int argc, const char *argv[]);
