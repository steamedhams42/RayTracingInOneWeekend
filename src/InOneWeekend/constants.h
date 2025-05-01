#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <cmath>
#include <limits>

#include "point3.h"
#include "vec3.h"

namespace constants {

const double INF_DOUBLE = std::numeric_limits<double>::infinity();
const double INF_INT = std::numeric_limits<int>::infinity();
const double PI = acos(-1);

const char nl = '\n';

// 1 Byte = 8 bits represented in decimal.
const int BYTE = 1 << 8;

const double ASPECT_WIDTH = 16.0;
const double ASPECT_HEIGHT = 9.0;
const double ASPECT_RATIO = ASPECT_WIDTH / ASPECT_HEIGHT;

const int IMAGE_WIDTH = 1000;
// image height cannot subceed 1
const int IMAGE_HEIGHT = std::fmax(1, (int)(1.0 * IMAGE_WIDTH / ASPECT_RATIO));

// Camera
const double FOCAL_LENGTH = 1.0;
const double VIEWPORT_HEIGHT = 2.0;
const double VIEWPORT_WIDTH = VIEWPORT_HEIGHT * IMAGE_WIDTH / IMAGE_HEIGHT;
const Point3 CAMERA_CENTER = Point3(0, 0, 0);

// Viewport
const Vec3 VIEWPORT_VECTOR_WIDTH = Vec3(VIEWPORT_WIDTH, 0, 0);
const Vec3 VIEWPORT_VECTOR_HEIGHT = Vec3(0, -VIEWPORT_HEIGHT, 0);

const Vec3 PIXEL_DELTA_WIDTH = VIEWPORT_VECTOR_WIDTH / IMAGE_WIDTH;
const Vec3 PIXEL_DELTA_HEIGHT = VIEWPORT_VECTOR_HEIGHT / IMAGE_HEIGHT;

// Calculate location of upper-left pixel's center.
// Start from the camera's location, move forward toward viewport by distance
// of focal length.
const Point3 upper_left_pixel_location =
    constants::CAMERA_CENTER - Point3(0, 0, FOCAL_LENGTH) -
    VIEWPORT_VECTOR_WIDTH / 2 - VIEWPORT_VECTOR_HEIGHT / 2;

// Point of the top-left pixel's center in the viewport.
const Point3 VIEWPORT_TOP_LEFT_PIXEL_CENTER =
    upper_left_pixel_location + PIXEL_DELTA_WIDTH / 2 + PIXEL_DELTA_HEIGHT / 2;

// Sphere
const Point3 SPHERE_CENTER = Point3(0, 0, -FOCAL_LENGTH);
const double SPHERE_RADIUS = 0.5;

}  // namespace constants

#endif
