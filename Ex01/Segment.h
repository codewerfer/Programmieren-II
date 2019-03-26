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

class Segment {
public:
  // Point structure
  struct Point {
  private:
    double x;
    double y;

  public:
    Point() {}

    Point(double x, double y) : x(x), y(y) {}

    double getX() const;

    double setX(double x);

    double getY() const;

    double setY(double y);
  };

  // default constructor
  Segment() {}

  // constructor from 2 Points
  Segment(Point start, Point end) : startPoint(start), endPoint(end) {}

  // constructor from 4 values
  Segment(double x0, double y0,
          double x1, double y1) : startPoint(x0, y0), endPoint(x1, y1) {}

  // returns Euclidean length of vector
  double norm() const;

  // returns signed distance d of a point to this segment
  // if (near) 0, we are on the line.
  double distance(Point p) const;

  // returns intersect of this segment with other
  bool intersect(Segment other) const;

  // returns intersect of this segment with other, and where it happens
  bool intersect(Segment other, Point &where) const;

  // get start point
  Point getStartPoint() const;

  // get end point
  Point getEndPoint() const;

private:
  Point startPoint; // absolute start point of segment
  Point endPoint;   // absolute end point of segment

  // determinate
  double det() const;

  // determinate of determinate between a and b
  static double det(Point a, Point b);

  // determinate of segment
  static double det(Segment segment);
};

double Segment::Point::getX() const { return x; }

double Segment::Point::setX(double x) { return this->x = x; }

double Segment::Point::getY() const { return y; }

double Segment::Point::setY(double y) { return this->y = y; }

double Segment::norm() const {
  return sqrt(pow(endPoint.getX() - startPoint.getX(), 2) +
              pow(endPoint.getY() - startPoint.getY(), 2));
}

double Segment::distance(Segment::Point p) const {
  // d = (x-x1)(y2-y1)-(y-y1)(x2-x1)
  // dnorm = d/norm()
  return ((p.getX() - startPoint.getX()) * (endPoint.getY() - startPoint.getY()) -
          (p.getY() - startPoint.getY()) * (endPoint.getX() - startPoint.getX()))
         / norm();
}

double Segment::det(Segment::Point a, Segment::Point b) {
  return a.getX() * b.getY() - a.getY() * b.getX();
}

double Segment::det() const {
  return det(startPoint, endPoint);
}

Segment::Point Segment::getStartPoint() const {
  return startPoint;
}

Segment::Point Segment::getEndPoint() const {
  return endPoint;
}

double Segment::det(Segment segment) {
  return segment.det();
}
