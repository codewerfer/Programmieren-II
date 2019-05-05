#pragma once

// gives out text instead of graphics
// allows Valgrind on WSL without X11
//#define NOGRAPH

#ifndef NOGRAPH
#include "../Drawing/Drawing.h"
// add 0.5 to x and y to get midpoint at drawing
#define MIDPOINT 0.5
#else
#include <iostream>
#endif

// Colors
#define BLACK 0x000000
#define WHITE 0xFFFFFF
#define BLUE 0x0000FF
#define RED 0xFF0000
#define GREEN 0x00FF00
#define CYAN 0x00FFFF
#define MAGENTA 0xFF00FF
#define YELLOW 0xFFFF00
