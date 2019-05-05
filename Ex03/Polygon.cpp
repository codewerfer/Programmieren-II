#include "Polygon.h"


Polygon::Polygon()
{
}


Polygon::~Polygon()
{
}

void Polygon::add(double x, double y, unsigned int c)
{
  // create Point and insert to linked list
  list.insert(Point(x, y, static_cast<int>(c)));
}

void Polygon::draw(double x0, double y0, double f)
{
  const LinkedList<Point>::Node* next = list.begin();

  if (!next) // if list is empty, we return
    return;
  Point p1, p2;
  p1 = next->data;
#ifndef NOGRAPH
  compsys::drawPoint(x0 + p1.x * f + MIDPOINT, y0 + p1.y * f + MIDPOINT,
                     p1.color);
#else
  std::cout << "drawPoint(" << (x0 + p1.x * f) << ", " << (y0 + p1.y * f) <<
    ", " << p1.color << ");" << std::endl;
#endif
  next = next->next;
  while (next)
  {
    p2 = next->data;
#ifndef NOGRAPH
    compsys::drawLine(x0 + p1.x * f + MIDPOINT, y0 + p1.y * f + MIDPOINT,
                      x0 + p2.x * f + MIDPOINT, y0 + p2.y * f + MIDPOINT,
                      p2.color);
#else
    std::cout << "drawLine(" << (x0 + p1.x * f) << ", " << (y0 + p1.y * f) <<
      ", " << (x0 + p2.x * f) << ", " << (y0 + p2.y * f) << ", " << p2.color <<
      ");" << std::endl;
#endif
    p1 = p2;
    next = next->next;
  }
}
