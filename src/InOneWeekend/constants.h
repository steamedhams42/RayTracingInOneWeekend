#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>
#include <limits>

#include "point3.h"

namespace constants {

const double INF_DOUBLE = std::numeric_limits<double>::infinity();
const double INF_INT = std::numeric_limits<int>::infinity();
const double PI = acos(-1);
const double EPS_ZERO = 1e-160;
const double EPS_ERROR = 1e-5;

const char nl = '\n';

// 1 Byte = 8 bits represented in decimal.
const int BYTE = 1 << 8;

// Camera
namespace camera {

const Point3 CAMERA_CENTER = Point3(0, 0, 0);

const double ASPECT_WIDTH = 16.0;
const double ASPECT_HEIGHT = 9.0;

const int IMAGE_WIDTH = 400;

const double FOCAL_LENGTH = 1.0;

// Viewport
const double VIEWPORT_HEIGHT = 2.0;

// Anti-aliasing. Set to 1 to turn off AA.
// setting lower than 100 will leave 'noise' in the form of black dots
const int SAMPLES_PER_PIXEL = 75;

// Speeds up rendering by limiting the number of light ray bounces and
// recursive calls
const int MAX_LIGHT_BOUNCES = 10;

}  // namespace camera

// Sphere
namespace sphere {

const Point3 SPHERE_CENTER = Point3(0, 0, -1.2);
const double SPHERE_RADIUS = 0.5;

}  // namespace sphere

}  // namespace constants

#endif
