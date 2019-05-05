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
