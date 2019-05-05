// ---------------------------------------------------------
// PenPolygon.cpp
// Source file for PenPolygon class
//
// Author: Jürgen Vogl <k1355432>
// Last Modification: 05.05.2019
//
// (c) Jürgen Vogl, 2019
// ----------------------------------------------------------
#include "PenPolygon.h"

PenPolygon::PenPolygon(double x, double y, double a, double c)
                      : x(x), y(y), c(static_cast<int>(c))
{
  // 0 <= angle < TAU
  angle = std::fmod(a, 2 * M_PI);
  if (std::signbit(angle))
    angle += 2 * M_PI;
  add(this->x, this->y, this->c);
}

void PenPolygon::move(double r)
{
  /*   a    dir  sin  cos
   *   0     x    0    1
   *  PI/2  -y    1    0
   *   PI   -x    0   -1
   * 3PI/2   y   -1    0   
   */
  const double x1 = x + r * std::cos(angle);
  const double y1 = y - r * std::sin(angle);
  add(x1, y1, c);
  x = x1;
  y = y1;
}

void PenPolygon::turn(double a)
{
  // 0 <= angle + a < TAU
  angle = std::fmod(angle + a, 2 * M_PI);
  if (std::signbit(angle))
    angle += 2 * M_PI;
}

void PenPolygon::color(unsigned int c)
{
  this->c = static_cast<int>(c);
}
