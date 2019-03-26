// ---------------------------------------------------------
// Segment.h
// Header file for Segment class
//
// Author: Jürgen Vogl <codewerfer>
// Last Modification: 23.03.2019
//
// (c) Jürgen Vogl, 2019
// ----------------------------------------------------------

#pragma once

class Segment
{
public:
  struct Point
  {
  private:
    double x;
    double y;

  public:
    Point() {}

    Point(double x, double y) : x(x), y(y) {}

    double getX();

    double setX(double x);

    double getY();

    double setY(double y);
  };

  Segment() {}

  Segment(Point start, Point end) : start(start), end(end) {}

  Segment(double x0, double y0,
          double x1, double y1) : start(x0, y0), end(x1, y1) {}

  // returns Euclidean length of vector
  double norm();

  // returns signed distance d of a point to this segment
  // if (near) 0, we are on the line.
  double distance(Point p);

  // returns intersect of this segment with other
  bool intersect(Segment other);

  // returns intersect of this segment with other, and where it happens
  bool intersect(Segment other, Point &where);

private:
  Point start;
  Point end;

  double det();

  double det(Point a, Point b);
};

double Segment::Point::getX() { return x; }

double Segment::Point::setX(double x) { return this->x = x; }

double Segment::Point::getY() { return y; }

double Segment::Point::setY(double y) { return this->y = y; }

double Segment::norm()
{
  return sqrt(pow(end.getX() - start.getX(), 2) +
              pow(end.getY() - start.getY(), 2));
}

double Segment::distance(Segment::Point p)
{
  // d = (x-x1)(y2-y1)-(y-y1)(x2-x1)
  // dnorm = d/norm()
  return ((p.getX() - start.getX()) * (end.getY() - start.getY()) -
          (p.getY() - start.getY()) * (end.getX() - start.getX()))
         / norm();
}

double Segment::det(Segment::Point a, Segment::Point b)
{
  return a.getX() * b.getY() - a.getY() * b.getX();
}

double Segment::det()
{
  return det(start, end);
}

bool Segment::intersect()
{

}
