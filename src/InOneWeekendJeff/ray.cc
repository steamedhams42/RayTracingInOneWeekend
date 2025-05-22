#include "ray.h"

Ray::Ray(const Point3& point, const Vec3& dir, double time)
    : origin_(point), direction_(dir), time_(time) {}

bool Ray::operator==(const Ray& rhs) {
  return this->origin_ == rhs.origin_ and this->direction_ == rhs.direction_;
}

const Point3& Ray::origin() const {
  return origin_;
}

const Vec3& Ray::direction() const {
  return direction_;
}

double Ray::time() const {
  return time_;
}

Point3 Ray::at(double t) const {
  return static_cast<Point3>(direction_) * t + origin_;
}
