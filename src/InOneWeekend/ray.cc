#include "ray.h"

Ray::Ray(Point3 point, Vec3 dir) : origin_(point), dir_(dir) {}

const Point3& Ray::origin() const {
  return origin_;
}

const Vec3& Ray::direction() const {
  return dir_;
}

Point3 Ray::at(double t) const {
  return static_cast<Point3>(dir_) * t + origin_;
}
