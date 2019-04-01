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
#include <string>
#include <algorithm>

#include <chrono>
#include <thread>

#ifdef _WIN32

#include <ctime>

#endif

#include "Drawing.h"
#include "Segment.h"

// The specification is not 100% clear how the ray is handled in the input.txt
// file. After asking Prof. Schreiner, he said the 2nd pair is a vector. But in
// the delivered video, it is a absolute position. Therefore I implemented both.
// One can change it with following definition. (Comment it out for same result
// as the video does)
//#define VEC_SPEC

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

// Colors
#define BLACK 0x000000
#define WHITE 0xFFFFFF
#define BLUE 0x0000FF
#define RED 0xFF0000
#define GREEN 0x00FF00
#define CYAN 0x00FFFF
#define MAGENTA 0xFF00FF
#define YELLOW 0xFFFF00

// drawRay definitions
// drawn pixels per draw
#define D 4
// red dot radius
#define R 6

// tolerance
#define TOLERANCE 1e-12

using namespace std;
using namespace compsys;

/**
 * Enum for init opitions
 */
enum options {
  RANDOM_INPUT = 1, FILE_INPUT = 2
};

/**
 * Set up ray and mirrors, based on program arguments.
 * For random, the will have a length of least 1.
 * @param option See enum options, it's set from argc (Argument count)
 *        RANDOM_INPUT: ray and mirrors are set randomly. mirrorCount := N + 4
 *        FILE_INPUT: ray, mirrorCount and mirrors will be read from file.
 * @param filename Filename where ray and mirrors are loaded from if FILE_INPUT
 * @param ray read or randomized light ray
 * @param mirrorCount read from file or set to N + 4 (WALLCOUNT)
 * @param mirrors
 */
void init(/*in*/ const int option, const char **filename,
        /*out*/ Segment &ray, int &mirrorCount, Segment *&mirrors);

/**
 * Draw Mirrors
 * Start with draw a white filled rectangle of Applications windows size.
 * Afterward it draws all mirrors in blue.
 * @param mirrorCount Number of mirrors to draw.
 * @param mirrors Array of mirrors.
 */
void drawMirrors(const int mirrorCount, const Segment mirrors[]);

/**
 * Animate the drawing of the light ray.
 * Draws it in RED.
 * Draws lines with D pixels (=length), sets start and endpoints with the
 * midpoint algorithm - to get nice results.
 * @param ray Light ray that will be animated from startPoint to endPoint.
 */
void drawRay(const Segment &ray, unsigned int color = RED);

/**
 * Mirror and wall version. Ray will be reflected from all in mirrors.
 * @param mirrorCount Number of elements in mirrors.
 * @param mirrors mirrors array. Nearest one on the way of the ray is reflection
 *        target.
 * @param ray Light ray. It endPoint will be updated to the point where it hits
 *        the nearest mirror on its way.
 * @param rayflection startPoint is the endPoint of the ray. endPoint
 */
void reflectRay(/*in*/const int mirrorCount, const Segment mirrors[],
                      Segment &ray, /*out*/ Segment &rayflection);

/**
 * Wall only version. Ray will be reflected on the walls - this are the mirrors
 * 0 to 3.
 * @param mirrorCount not used
 * @param mirrors Array of mirrors, in this we only use the first 4, that are
 *        defined to be the wall.
 * @param ray our ray, its endpoint will be updated to the point where it hits
 *        the mirror/wall.
 * @param rayflection the reflected ray, with endpoint of ray as startpoint, and
 *        a modified vector of the rays vector.
 */
void reflectRayOld(/*in*/const int mirrorCount, const Segment mirrors[],
                         Segment &ray, /*out*/ Segment &rayflection);

/**
 * inits a random ray, random mirrors and set mirrorCount to N+4 ray and mirrors
 * have a length of least 1 and values between 0 and W for x and 0 and H for y
 * @param ray randomized ray
 * @param mirrorCount number of elements in mirrors array, defined as N+4
 * @param mirrors randomized mirrors, can intersect with etch other
 */
void randomInit(Segment &ray, int &mirrorCount, Segment *&mirrors);

/**
 * inits ray, mirrorCount and mirrors from given filename will open file from
 * filename and close it
 * @param filename
 * @param ray
 * @param mirrorCount
 * @param mirrors
 */
void fileInit(/*in*/ const string& filename,
        /*out*/ Segment &ray, int &mirrorCount, Segment *&mirrors);

/**
 * prints values to stdout
 * @param ray light ray
 * @param count number of elements in mirrors array
 * @param mirrors mirrors array
 */
void printValues(const Segment& ray, const int count, const Segment mirrors[]);

/**
 * rand between min (incl.) and max (excl.)
 * @param min lower bound (inclusive)
 * @param max upper bound (exclusive)
 * @return a number from {min, min+1, ..., max-2, max-1}
 */
int rand(int min, int max);

/**
 * rand from 0 (incl.) to max (excl.)
 * @param max uppber bound (exclusive)
 * @return a number from {0, 1, ..., max-2, max-1}
 */
int rand(int max) { return rand(0, max); }

// given and unmodified main method from specification Ex01
// argc is used as an option, 1 is random, 2 is read of a file
// argv is the filename
// more arguments will result in an random run
int main(int argc, const char *argv[]);
