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

#define W 800
#define H 600

void init(int argc, const char **pString, Segment segment, int n, Segment *pSegment);

void drawMirrors(int n, Segment *pSegment);

void drawRay(Segment segment);

void reflectRay(int n, Segment *mirrors, Segment ray, Segment ray0);

int main(int argc, const char *argv[]);
