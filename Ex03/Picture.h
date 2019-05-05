// ---------------------------------------------------------
// Picture.h
// Header file for Picture class
//
// Author: Jürgen Vogl <k1355432>
// Last Modification: 05.05.2019
//
// (c) Jürgen Vogl, 2019
// ----------------------------------------------------------
#pragma once

#include "Polygon.h"
//#include "LinkedList.cpp"

/**
 * \brief Creates a picture, a list of Polygon*.
 * Can draw this list in a separate Window.
 */
class Picture
{
  LinkedList<Polygon*> list; // Polygon* list

public:
  // default constructor
  Picture();
  // add Polygon* to list
  void add(Polygon* p);
  // Opens a new grafic windows with size w and h and draws
  // the Polygons in list from Base Postition x/y with a scale f
  void draw(double x, double y, double w, double h, double f = 1.0);
};
