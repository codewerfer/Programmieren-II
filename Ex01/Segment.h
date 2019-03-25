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

private:
  Point start;
  Point end;
};

double Segment::Point::getX() { return x; }

double Segment::Point::setX(double x) { return this->x = x;}

double Segment::Point::getY() { return y; }

double Segment::Point::setY(double y) { return this->y = y;}

double Segment::norm()
{
  return sqrt(pow(end.getX() - start.getX(), 2) +
              pow(end.getY() - start.getY(), 2));
}
