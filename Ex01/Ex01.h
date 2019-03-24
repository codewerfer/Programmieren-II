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

#include "Drawing.h"
#include "Segment.h"

// width of window
#define W 800
// height of window
#define H 600
// iteration, how often the ray will be reflected
#define T 50

enum options {RANDOM_INPUT=1, FILE_INPUT=2};

void init(options option, const char **filename, Segment ray,
        int n, Segment *mirrors);

void drawMirrors(int n, Segment *pSegment);

void drawRay(Segment segment);

void reflectRay(int n, Segment *mirrors, Segment ray, Segment ray0);

int main(int argc, const char *argv[]);
