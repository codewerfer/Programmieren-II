#pragma once
#include "Polygon.h"
#include <cmath>

// LOGO Turtle commands
#define FD(x) move(x)
#define BK(x) move(-x)
#define RT(x) turn((-x*2*M_PI)/360)
#define LT(x) turn((x*2*M_PI)/360)
#define SETPC(x) color(x)

/**
 * \brief Turtle (LOGO) like implementation of Polygon class.
 */
class PenPolygon : public Polygon
{
  double x, y, angle; // coordinates and angle
  int c;              // color

public:
  /**
   * \brief Creates a PenPolygon
   * \param x Startpoint x
   * \param y Startpoint y
   * \param a Angle of the startpoint/first line.
   * \param c Color of startpoint/first line. double by definition.
   */
  PenPolygon(double x = 0, double y = 0, double a = 0, double c = 0);
  /**
   * \brief Creates a Line of length r.
   * \param r Length of the line.
   */
  void move(double r);
  /**
   * \brief Turns Turtle
   * \param a Turn by this angle (in RAD, so 2*PI is a full circle)
   */
  void turn(double a);
  /**
   * \brief Changes color.
   * \param c RGB in form 0xRRGGBB
   */
  void color(unsigned int c);
};
