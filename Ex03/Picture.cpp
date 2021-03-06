// ---------------------------------------------------------
// Picture.cpp
// Source file for Picture class
//
// Author: Jürgen Vogl <k1355432>
// Last Modification: 05.05.2019
//
// (c) Jürgen Vogl, 2019
// ----------------------------------------------------------
#include "Picture.h"

Picture::Picture()
{
}

void Picture::add(Polygon* p)
{
  list.insert(p);
}

void Picture::draw(double x, double y, double w, double h, double f)
{
#ifndef NOGRAPH
  compsys::beginDrawing(w, h, "A Picture");
#endif

  const LinkedList<Polygon*>::Node* next = list.begin();

  while (next)
  {
    next->data->draw(x, y, f);
    next = next->next;
  }

#ifndef NOGRAPH
  compsys::endDrawing();
#endif
}
