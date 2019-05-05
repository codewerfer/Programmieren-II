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

class Picture
{
  LinkedList<Polygon*> list;

public:
  Picture();
  void add(Polygon* p);
  void draw(double x, double y, double w, double h, double f = 1.0);
};
