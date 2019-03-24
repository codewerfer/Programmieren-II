// ---------------------------------------------------------
// Ex01.cpp
// class File for file manipulation and associated operations.
//
// Author: Jürgen Vogl <codewerfer>
// Last Modification: 23.03.2019
//
// (c) Jürgen Vogl, 2019
// ----------------------------------------------------------

#include "Ex01.h"

using namespace std;
using namespace compsys;

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

void init(options option, const char **filename, Segment ray,
          int n, Segment *mirrors) {
  switch (option) {
    case RANDOM_INPUT:
      // random end points for ray
      // N + 4 mirrors
      //   first 4 represent wall (0, W-1, H-1)
      //   rest is random (can intersect)
      // Ray and mirrors must stay inside the room.
      // Lenght of vectors must be at least 1.

      break;
    case FILE_INPUT:
      // load from filename.
      break;
    default:
      cout << "Invalid argument count.";
  }
}

void drawMirrors(int n, Segment *pSegment) {

}

void drawRay(Segment segment) {

}

void reflectRay(int n, Segment *mirrors, Segment ray, Segment ray0) {

}
