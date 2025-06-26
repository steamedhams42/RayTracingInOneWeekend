#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>
#include <limits>

#include "InOneWeekendJeff/color.h"
#include "InOneWeekendJeff/interval.h"
#include "InOneWeekendJeff/point3.h"
#include "InOneWeekendJeff/vec3.h"

namespace constants {

const double INF_DOUBLE = std::numeric_limits<double>::infinity();
const double INF_INT = std::numeric_limits<int>::infinity();
const double PI = acos(-1);
const double EPS_ZERO = 1e-160;
const double EPS_ERROR = 1e-5;

const char nl = '\n';

// 1 Byte = 8 bits represented in decimal.
const int BYTE = 1 << 8;

const Vec3 X_AXIS_BASIS{1, 0, 0};
const Vec3 Y_AXIS_BASIS{0, 1, 0};
const Vec3 Z_AXIS_BASIS{0, 0, 1};

// Camera
namespace camera {

const Point3 CAMERA_CENTER{13, 2, 3};
const Point3 FOCAL_POINT{0, 0, 0};
// Distance formula between camera center and focal point.
const double FOCAL_DISTANCE = Point3(CAMERA_CENTER - FOCAL_POINT).norm();

const double ASPECT_WIDTH = 16.0;
const double ASPECT_HEIGHT = 9.0;

const int IMAGE_WIDTH = 400;

// The vertical angle (degrees) of the camera's FoV.
const double VERTICAL_FIELD_OF_VIEW = 20;

// Anti-aliasing. Set to 1 to turn off AA.
// setting lower than 100 will leave 'noise' in the form of black dots
const int SAMPLES_PER_PIXEL = 1000;

// Speeds up rendering by limiting the number of light ray bounces and
// recursive calls
const int MAX_LIGHT_BOUNCES = 50;

// Variation angle of rays through each pixel (degrees)
// values > 0,0 adds a blurring effect
// double DEFOCUS_ANGLE = 0.0;

}  // namespace camera

namespace interval {
const Interval EMPTY = Interval();
const Interval UNIVERSAL =
    Interval(-constants::INF_DOUBLE, constants::INF_DOUBLE);
}  // namespace interval

namespace color {
const Color WHITE(1, 1, 1);
const Color BLACK(0, 0, 0);
}  // namespace color

}  // namespace constants

#endif
