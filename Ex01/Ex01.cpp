﻿// ---------------------------------------------------------
// Ex01.cpp
// class File for file manipulation and associated operations.
//
// Author: Jürgen Vogl <codewerfer>
// Last Modification: 23.03.2019
//
// (c) Jürgen Vogl, 2019
// ----------------------------------------------------------

#include "Ex01.h"

int main(int argc, const char *argv[]) {
  beginDrawing(W, H, "Laser", 0xFFFFFF);

  Segment ray;
  int n;
  Segment *mirrors;
  init(argc, argv, ray, n, mirrors);
  drawMirrors(n, mirrors);
  for (int i = 0; i < T; i++) {
    Segment ray0;
    reflectRay(n, mirrors, ray, ray0);
    drawRay(ray);
    ray = ray0;
  }
  delete[] mirrors;

  cout << "Close window to exit..." << endl;
  endDrawing();
}

void init(int option, const char *filename[],
          Segment &ray, int &mirrorCount, Segment *&mirrors) {
  switch (options(option)) {
    case RANDOM_INPUT:
      // random endPoint points for ray
      // N + 4 mirrors
      //   first 4 represent wall (0, W-1, H-1)
      //   rest is random (can intersect)
      // * Ray and mirrors must stay inside the room.
      // * Lenght of vectors must be at least 1.
      randomInit(ray, mirrorCount, mirrors);
      break;
    case FILE_INPUT:
      // load from filename.
      fileInit(filename, ray, mirrorCount, mirrors);
      break;
    default:
      cout << "Invalid argument count. Start with random values.";
      randomInit(ray, mirrorCount, mirrors);
  }
  // output of values to stdout
  printValues(ray, mirrorCount, mirrors);
}

void printValues(const Segment ray, const int count, const Segment *mirrors) {
  // output of ray - watch out, second pair are the vector, therefore x1 - x0
  // and y1 - y0.
  cout << ray.getStartPoint().getX() << " " << ray.getStartPoint().getY() <<
       " " << ray.getEndPoint().getX() - ray.getStartPoint().getX() << " " <<
       ray.getEndPoint().getY() - ray.getStartPoint().getY() << endl;
  cout << count << endl;
  // print
  for (int i = 0; i < count; ++i) {
    cout << mirrors[i].getStartPoint().getX() << " " <<
         mirrors[i].getStartPoint().getY() << " " <<
         mirrors[i].getEndPoint().getX() << " " <<
         mirrors[i].getEndPoint().getY() << endl;
  }
}

void fileInit(const char *filename[], Segment &ray, int &mirrorCount, Segment *&mirrors) {

}

void drawMirrors(int mirrorCount, Segment mirrors[]) {

}

void drawRay(Segment ray) {

}

void reflectRay(int mirrorCount, Segment mirrors[], Segment ray,
                Segment &rayflection) {

}


void randomInit(Segment &ray, int &mirrorCount, Segment *&mirrors) {
  // init rand
  srand(time(0));

  // create ray
  do {
    ray = Segment(rand(W), rand(H), rand(W), rand(H));
  } while (ray.norm() < 1);

  // set mirrorCount
  mirrorCount = N + WALLCOUNT;

  // create mirrors, startPoint with 4 walls
  mirrors = new Segment[mirrorCount];
  mirrors[0] = Segment(Segment::Point(P0), Segment::Point(P1));
  mirrors[1] = Segment(Segment::Point(P1), Segment::Point(P2));
  mirrors[2] = Segment(Segment::Point(P2), Segment::Point(P3));
  mirrors[3] = Segment(Segment::Point(P3), Segment::Point(P0));

  // random mirrors of length >= 1
  for (int i = WALLCOUNT; i < mirrorCount; ++i) {
    do {
      mirrors[i] = Segment(rand(W), rand(H), rand(W), rand(H));
    } while (mirrors[i].norm() < 1);
  }
}

int rand(int min, int max) {
  // equal distribution - it's the details that make the difference
  int r;
  while ((r = rand()) > ((RAND_MAX / max) * max)) {}

  return r % (max - min) + min;
}