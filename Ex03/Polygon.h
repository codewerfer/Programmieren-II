#pragma once
#include "MyDrawing.h"
//#include "LinkedList.h"
#include "LinkedList.cpp"

/**
 * \brief Polygon class
 * add Points and draw a polygon
 */
class Polygon
{
  /**
   * \brief Point structure
   * Saves coordinates and color of a point
   */
  struct Point {
    double x, y; // x, y Coordinates
    int color;   // Color
    /**
     * \brief Default constructor, position (0,0) and color black.
     */
    Point() : x(0), y(0), color(BLACK) {}

    /**
     * \brief Constructor
     * \param x x coordinate
     * \param y y coordinate
     * \param color color of/to this point
     */
    Point(double x, double y, int color) : x(x), y(y), color(color) {}
  };

  LinkedList<Point> list; // the linked list of points.

public:
  // create and destroy polygon
  Polygon();
  ~Polygon();

  // add point with coordinates (x,y) to polygon
  // line from last point to this one has color c (default black)
  void add(double x, double y, unsigned int c = 0);

  // draws the polygon at absolute coordinates (x0,y0) scaled by factor f;
  // thus every point (x,y) is drawn at position (x0+x*f, y0+y*f)
  void draw(double x0, double y0, double f);
};
