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

void init(int argc, const char **pString, Segment segment, int n, Segment *pSegment) {

}

void drawMirrors(int n, Segment *pSegment) {

}

void drawRay(Segment segment) {

}

void reflectRay(int n, Segment *mirrors, Segment ray, Segment ray0) {

}
