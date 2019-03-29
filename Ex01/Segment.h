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

#include <sstream>

class Segment {
public:
  // Point structure
  struct Point {
    double x;
    double y;

  public:
    Point() = default;

    Point(double x, double y) : x(x), y(y) {}

    Point(const Point &p) : x(p.x), y(p.y) {}
  };

  // default constructor
  Segment() {}

  // constructor from 2 Points
  Segment(Point start, Point end) : startPoint(start), endPoint(end) {}

  // constructor from 4 values
  Segment(double x0, double y0,
          double x1, double y1) : startPoint(x0, y0), endPoint(x1, y1) {}

  // constructor that parses a string to Segment
  Segment(const std::string str) {
    std::stringstream stream(str);

    //int n[4];
    //int i = 0;
//    while (stream) {
//      stream >> n[i++];
//    }
    stream >> startPoint.x >> std::ws >> startPoint.y >> std::ws >>
              endPoint.x >> std::ws >> endPoint.y;
//    startPoint.setX(n[0]);
//    startPoint.setY(n[1]);
//    endPoint.setX(n[2]);
//    endPoint.setY(n[3]);
  }

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

  // let Segment be interoperable with cout
  friend std::ostream &operator<<(std::ostream &stream, const Segment &seg);

protected:
  // absolute end point of segment

  Point startPoint;
// absolute start point of segment
  Point endPoint;
private:
  // determinate
  double det() const;

  // determinate of determinate between a and b
  static double det(Point a, Point b);

  // determinate of segment
  static double det(Segment segment);
};

class SegmentVec : public Segment {
protected:
  using Segment::startPoint;
  using Segment::endPoint;

public:
  // constructor that parses a string to SegmentVec
  SegmentVec(const std::string str) {
    std::istringstream stream(str);

    int n[4];
    int i = 0;
    while (stream) {
      stream >> n[i++];
    }
    startPoint.x = (n[0]);
    startPoint.y = (n[1]);
    endPoint.x = (n[2] + n[0]);
    endPoint.y = (n[3] + n[1]);
  }

  SegmentVec(const Segment seg) {
    Segment::startPoint = seg.getStartPoint();
    Segment::endPoint = seg.getEndPoint();
  }

  friend std::ostream &operator<<(std::ostream &stream, const SegmentVec &ray);
};

std::ostream &operator<<(std::ostream &stream, const SegmentVec &ray) {
  stream << ray.startPoint.x << " " << ray.startPoint.y << " " <<
         ray.endPoint.x - ray.startPoint.x << " " <<
         ray.endPoint.y - ray.startPoint.y;
  return stream;
}

double Segment::norm() const {
  return sqrt(pow(endPoint.x - startPoint.x, 2) +
              pow(endPoint.y - startPoint.y, 2));
}

double Segment::distance(Segment::Point p) const {
  // d = (x-x1)(y2-y1)-(y-y1)(x2-x1)
  // dnorm = d/norm()
  return ((p.x - startPoint.x) * (endPoint.y - startPoint.y)
       - (p.y - startPoint.y) * (endPoint.x - startPoint.x))
       / norm();
}

double Segment::det(Segment::Point a, Segment::Point b) {
  return a.x * b.y - a.y * b.x;
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

std::ostream &operator<<(std::ostream &stream, const Segment &seg) {
  stream << seg.startPoint.x << " " << seg.startPoint.y << " " <<
         seg.endPoint.x << " " << seg.endPoint.y;
  return stream;
}
