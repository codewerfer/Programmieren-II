// ---------------------------------------------------------
// Ex01.cpp
// class File for file manipulation and associated operations.
//
// Author: Jürgen Vogl <codewerfer>
// Last Modification: 31.03.2019
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

void init(const int option, const char *filename[],
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
      fileInit(filename[1], ray, mirrorCount, mirrors);
      break;
    default:
      cout << "Invalid argument count." << endl <<
           "Usage: Ex01 [filename]" << endl <<
           "    filename: filename with inputdata" << endl << endl <<
           "Example(s):" << endl <<
           "Ex01" << endl <<
           "Ex01 input.txt" << endl;
      exit(1);
  }
  // output of values to stdout
  printValues(ray, mirrorCount, mirrors);
}

void printValues(const Segment &ray, const int count, const Segment *mirrors) {
  // output of ray - watch out, second pair is a vector if VEC_SPEC is set
  // therefore x1 - x0 and y1 - y0.
#ifdef VEC_SPEC
  cout << (SegmentVec) ray << endl;
#else
  cout << ray << endl;
#endif
  cout << count << endl;
  // print mirrors
  for (int i = 0; i < count; ++i) {
    cout << mirrors[i] << endl;
  }
}

void fileInit(const string &filename,
              Segment &ray, int &mirrorCount, Segment *&mirrors) {
  ifstream stream(filename);
  if (stream.is_open()) {
    string line;

    // read ray
    getline(stream, line);
#ifdef VEC_SPEC
    ray = SegmentVec(line);
#else
    ray = Segment(line);
#endif
    // read mirrorCount
    getline(stream, line);
    istringstream(line) >> mirrorCount;

    // read mirrors
    mirrors = new Segment[mirrorCount];
    for (int i = 0; i < mirrorCount; ++i) {
      getline(stream, line);
      mirrors[i] = Segment(line);
    }

    // close file and return
    stream.close();
  } else {
    cout << "Unable to open file.";
    exit(2);
  }
}

void drawMirrors(const int mirrorCount, const Segment mirrors[]) {
  // fill with white rectangle
  fillRectangle(0, 0, W - 1, H - 1, WHITE);

  // draw mirrors
  for (int i = 0; i < mirrorCount; ++i) {
    drawLine(mirrors[i].startPoint.x, mirrors[i].startPoint.y,
             mirrors[i].endPoint.x, mirrors[i].endPoint.y, BLUE);
  }
}

void drawRay(const Segment &ray) {
  // from the midpoint algorithm (Pittway 1967, van Aken and Novak 1985) we know
  // that a line from (x0, y0) to (x1, y1) has max(|x1-x0|,|y1-y0|) pixels on a
  // raster image. Because the specification of this Exercise says we should
  // draw (exactly) D pixels, we use this length (r) and not the real euclidean
  // length. Every subpart of a midpoint algorithm line is also again a midpoint
  // algorithm line, down to single dot size.

  Segment::Point vec = ray.vec();
  const int r = max(abs((int) vec.x), abs((int) vec.y));
  vec /= r; // per pixel vector

  int steps = r / D;
  Segment::Point start = ray.startPoint;
  Segment::Point end;

  for (int i = 0; i < steps; ++i) {
    end = start + vec * (D - 1);
    drawLine(lround(start.x), lround(start.y),
             lround(end.x), lround(end.y), RED);
    start = end + vec;
    // it's running very fast on my computer, therefore, I have to slow it down
    //this_thread::sleep_for(chrono::milliseconds(5));
  }

  if (r % D != 0) // final step if missing
    drawLine(lround(start.x), lround(start.y),
             ray.endPoint.x, ray.endPoint.y, RED);

  // draw red dot
  fillEllipse(ray.endPoint.x - R / 2, ray.endPoint.y - R / 2, R, R, RED);
}

void reflectRay(const int mirrorCount, const Segment mirrors[],
                Segment &ray, Segment &rayflection) {
  // Only wall version, walls are always 0 to 3. We will hit a wall with t > 0.
  static int lastMirror = -1;
  int i;
  double t;
  Segment::Point poi;
  bool found = false;
  cout << "RayNorm1: " << ray.vec() / ray.norm() << endl;
  for (i = 0; i < 4; ++i) {
    if (i == lastMirror) {
      // we need not to check again last hitted mirror - and this is the only
      // point here where we have a tolerance problem for the next compare
      continue;
    }
    if (ray.intersectVec(mirrors[i], t, poi) && t >= (0/*+ TOLERANCE*/)) {
      found = true;
      break;
    }
  }
  if (!found) {
    cout << "No wall found. Abort.";
    exit(3);
  }

  ray.endPoint = poi;
  cout << "RayNorm2: " << ray.vec() / ray.norm() << endl;
  lastMirror = i;

  // reflect on wall, easy version
  if (mirrors[i].vec().x == 0) {
    rayflection = SegmentVec(poi, Segment::Point(ray.vec().x, -ray.vec().y));
  } else {
    rayflection = SegmentVec(poi, Segment::Point(-ray.vec().x, ray.vec().y));
  }
}

void reflectRayOld(const int mirrorCount, const Segment mirrors[],
                   Segment &ray, Segment &rayflection) {
  // Only wall version, walls are always 0 to 3. We will hit a wall with t > 0.
  static int lastMirror = -1;
  int i;
  double t;
  Segment::Point poi;
  bool found = false;
  for (i = 0; i < WALLCOUNT; ++i) {
    if (i == lastMirror) {
      // we need not to check again last hitted mirror - and this is the only
      // point here where we have a tolerance problem
      continue;
    }
    if (ray.intersectVec(mirrors[i], t, poi) && t > (0/*+ TOLERANCE*/)) {
      found = true;
      break;
    }
  }
  if (!found) {
    cout << "No wall found. Abort.";
    exit(3);
  }

  ray.endPoint = poi;
  lastMirror = i;

  // reflect on wall, easy version
  if (mirrors[i].vec().x == 0) {
    rayflection = SegmentVec(poi, Segment::Point(ray.vec().x, -ray.vec().y));
  } else {
    rayflection = SegmentVec(poi, Segment::Point(-ray.vec().x, ray.vec().y));
  }
}

void randomInit(Segment &ray, int &mirrorCount, Segment *&mirrors) {
  // init rand
  srand(time(0));

  // create ray with length >= 1
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
