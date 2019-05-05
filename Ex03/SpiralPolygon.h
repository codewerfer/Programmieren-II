// ---------------------------------------------------------
// SpiralPolygon.h
// Header file for SpiralPolygon class
//
// Author: Jürgen Vogl <k1355432>
// Last Modification: 05.05.2019
//
// (c) Jürgen Vogl, 2019
// ----------------------------------------------------------
#pragma once
#include "PenPolygon.h"

class SpiralPolygon : public PenPolygon
{
  /**
   * \brief Change color by a number generator.
   * \param s seed for number generator
   * \param seed activates seed
   * \return
   */
  static int changeColor(int s = 0, bool seed = false);

public:
  /**
   * \brief Creates a spiral-shaped polygon
   * \param n how many lines
   * \param s seed for random number for color c
   * \param c color changes after this number of lines
   * \param x Start position x
   * \param y Start position y
   * \param r length at start
   * \param a direction at start
   * \param r0 length factor for every new line (r * r0 * r0 * ..)
   * \param a0 direction change for every new line (a + a0 + a0 + .. )
   */
  SpiralPolygon(int n, int s, int c, double x, double y, double r, double a,
    double r0, double a0);
};
