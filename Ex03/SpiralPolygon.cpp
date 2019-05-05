// ---------------------------------------------------------
// SpiralPolygon.cpp
// Source file for SpiralPolygon class
//
// Author: Jürgen Vogl <k1355432>
// Last Modification: 05.05.2019
//
// (c) Jürgen Vogl, 2019
// ----------------------------------------------------------
#include "SpiralPolygon.h"


int SpiralPolygon::changeColor(int s, bool seed)
{
  if (seed)
  {
    srand(s);
  }
  // RAND_MAX may not be big enough
  if (RAND_MAX >= 0xFFFFFF)
  {
    return (rand() & 0xFFFFFF);
  }
  else if (RAND_MAX >= 0xFFF)
  {
    // 2 times 12 bit
    return (rand() << 12 & 0xFFF000) | (rand() & 0xFFF);
  }
  // 3 times 8 bit
  return (rand() << 16 & 0xFF0000) | (rand() << 8 & 0xFF00) | (rand() & 0xFF);
}

SpiralPolygon::SpiralPolygon(int n, int s, int c, double x, double y, double r,
                             double a, double r0, double a0) : PenPolygon(
  x, y, a, changeColor(s, true))
{
  for (int i = 1; i < n; ++i) // n-1 moves, correct i % c == 0
  {
    move(r);
    if (i % c == 0)
    {
      color(changeColor());
    }
    turn(a0);
    r *= r0;
  }
  move(r); // last move
}
