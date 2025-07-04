#include "ray.h"

#include <cmath>

#include "InOneWeekendJeff/utils.h"

Ray::Ray(const Point3& point, const Vec3& dir, double time)
    : origin_(point), direction_(dir), time_(time) {}

bool Ray::operator==(const Ray& rhs) {
  return this->origin_ == rhs.origin_ and this->direction_ == rhs.direction_;
}

const Point3& Ray::origin() const {
  return origin_;
}

Ray Ray::Translate(const Vec3& translation_offset) const {
  Ray result(*this);
  result.origin_ += translation_offset;
  return result;
}

Ray Ray::RotateY(double degrees_of_rotation) const {
  Ray result(*this);
  double cos_theta = std::cos(utils::DegreesToRadians(degrees_of_rotation));
  double sin_theta = std::sin(utils::DegreesToRadians(degrees_of_rotation));

  result.origin_ =
      Point3(cos_theta * result.origin().x() - sin_theta * result.origin().z(),
             result.origin().y(),
             sin_theta * result.origin().x() + cos_theta * result.origin().z());

  result.direction_ = Vec3(
      cos_theta * result.direction().x() - sin_theta * result.direction().z(),
      result.direction().y(),
      sin_theta * result.direction().x() + cos_theta * result.direction().z());

  return result;
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
