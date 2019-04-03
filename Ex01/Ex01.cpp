// ---------------------------------------------------------
// Ex01.cpp
// Source file for Exercise 1
//
// Author: Jürgen Vogl <k1355432>
// Last Modification: 03.02.2019
//
// (c) Jürgen Vogl, 2019
// ----------------------------------------------------------

#include "Ex01.h"

int main(int argc, const char *argv[]) {
#ifdef _DEBUG
  beginDrawing(W + 150, H + 50, "Laser", 0xFFFFFF);
#else
  beginDrawing(W, H, "Laser", 0xFFFFFF);
#endif
  Segment ray{};
  int n;
  Segment *mirrors;
  init(argc, argv, ray, n, mirrors);
  drawMirrors(n, mirrors);
  for (int i = 0; i < T; i++) {
    Segment ray0;
#ifdef WALLVERSION
    reflectRayOld(n, mirrors, ray, ray0);
#else
    reflectRay(n, mirrors, ray, ray0);
#endif
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
    drawLine((int) mirrors[i].startPoint.x, (int) mirrors[i].startPoint.y,
             (int) mirrors[i].endPoint.x, (int) mirrors[i].endPoint.y, BLUE);
  }
}

void drawRay(const Segment &ray, unsigned int color)
{
  // from the midpoint algorithm (Pittway 1967, van Aken and Novak 1985) we know
  // that a line from (x0, y0) to (x1, y1) has max(|x1-x0|,|y1-y0|) pixels on a
  // raster image. Because the specification of this Exercise says we should
  // draw (exactly) D pixels, we use this length (r) and not the real euclidean
  // length. Every subpart of a midpoint algorithm line is also again a midpoint
  // algorithm line, down to single dot size.

  Segment::Point vec = ray.vec();
  const double r = max(abs(vec.x), abs(vec.y));
  vec /= r; // per pixel vector

  int steps = r / D;
  Segment::Point start = ray.startPoint;
  Segment::Point end{};

  for (int i = 0; i < steps; ++i) {
    end = start + vec * (D - 1);
    drawLine(lround(start.x), lround(start.y),
             lround(end.x), lround(end.y), color);
    start = end + vec;
#ifdef SLOWDOWN
    // it's running very fast on my computer, therefore, I have to slow it down
    this_thread::sleep_for(chrono::milliseconds(5));
#endif
  }

  if ((int) r % D != 0) { // final step if missing
    drawLine(lround(start.x), lround(start.y),
             (int) ray.endPoint.x, (int) ray.endPoint.y, color);
}

  // draw dot
  fillEllipse((int) ray.endPoint.x - R / 2, (int) ray.endPoint.y - R / 2,
              R, R, color);
}

void reflectRay(const int mirrorCount, const Segment mirrors[],
                Segment &ray, Segment &rayflection) {
  // Only wall version, walls are always 0 to 3. We will hit a wall with t > 0.
  static int lastMirror = -1;
  Segment::Point poi{};
  bool found = false;
  int nearstIndex = 0;
  double nearestNorm = HUGE_VAL;
  auto *points = new Segment::Point[mirrorCount];
#ifdef _DEBUG
  drawRay(ray, GREEN);
#endif
  for (int i = 0; i < mirrorCount; ++i) {
#ifdef _DEBUG
    {
      //draw "normal"to ray
      drawRay(SegmentVec(ray.startPoint,
                         Segment::Point(-ray.vec().y, ray.vec().x)), YELLOW);
      stringstream s1, s2;
      // print distance of mirrors[i] start and endpoint to ray
      s1 << ray.distance(mirrors[i].startPoint) << " (" << mirrors[i].startPoint << ")";
      s2 << ray.distance(mirrors[i].endPoint) << " (" << mirrors[i].endPoint << ")";
      drawText((int)mirrors[i].startPoint.x + R,
              (int)mirrors[i].startPoint.y,
               s1.str().c_str());
      drawText((int)mirrors[i].endPoint.x + R,
              (int)mirrors[i].endPoint.y,
               s2.str().c_str());
    }
#endif
    if (i == lastMirror) {
      // we need not to check again last hit mirror - this is the only
      // point here where we have a tolerance problem for the next compare
      continue;
    }
    if (ray.intersectVec(mirrors[i], poi)) {
#ifdef _DEBUG
      {
        stringstream s3;
        // draw possible hits on rays way
        drawRectangle((int)poi.x - R / 2, (int)poi.y - R / 2, R, R, BLACK);

        s3 << ray.orthoDist(poi) << " (" << poi << ")";
        drawText((int)poi.x + R, (int)poi.y, s3.str().c_str());
      }
#endif
      found = true;
      double d = ray.orthoDistFast(poi);
      if (d > 0 && d < nearestNorm) {
        nearestNorm = d;
        nearstIndex = i;
        points[i] = poi;
      }
    }
  }
  if (!found) {
    cout << "No wall found. Abort." << endl <<
         "You may be too tolerant ;)";
    exit(3);
  }

  ray.endPoint = points[nearstIndex];
  lastMirror = nearstIndex;

  // reflect on mirror
  if (!mirrors[lastMirror].reflect(ray, rayflection, true)) {
    cout << "Refection failed, ray doesn't intersect mirror on intersection"
            "point." << endl;
    exit(4);
  }
#ifdef _DEBUG
  {
    // draw reflected ray
    drawRay(rayflection, CYAN);
    stringstream s4;
    // print distance of mirrors[i] start and endpoint to ray
    s4 << ray.distance(rayflection.endPoint)
    << " (" << rayflection.endPoint << ")";

    drawText((int) rayflection.endPoint.x + R,
             (int) rayflection.endPoint.y,
             s4.str().c_str());
  }
#endif

  delete[] points;
}

void reflectRayOld(const int mirrorCount, const Segment mirrors[],
                   Segment &ray, Segment &rayflection) {
  // Only wall version, walls are always 0 to 3. We will hit a wall with t > 0.
  static int lastMirror = -1;
  int i;
  Segment::Point poi{};
  bool found = false;
#ifdef _DEBUG
  drawRay(ray, GREEN);
#endif
  for (i = 0; i < 4; ++i) {
    if (i == lastMirror) {
      // we need not to check again last hitted mirror - and this is the only
      // point here where we have a tolerance problem for the next compare
      continue;
    }
    if (ray.intersectVecOld(mirrors[i], poi)) {
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

  // reflect on wall, easy version, just flip sign of x/y - depends what we hit
  if (mirrors[i].startPoint.x == mirrors[i].endPoint.x) {
    rayflection = SegmentVec(poi, Segment::Point(-ray.vec().x, ray.vec().y));
  } else {
    rayflection = SegmentVec(poi, Segment::Point(ray.vec().x, -ray.vec().y));
  }
}


void randomInit(Segment &ray, int &mirrorCount, Segment *&mirrors) {
  // init rand
  srand((unsigned int) time(0));

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
