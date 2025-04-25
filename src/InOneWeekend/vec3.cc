#include "vec3.h"

Vec3 Vec3::operator+(const Vec3& rhs) {
  return Vec3(x() + rhs.x(), y() + rhs.y(), z() + rhs.z());
}

Vec3 Vec3::operator-(const Vec3& rhs) {
  return Vec3(x() - rhs.x(), y() - rhs.y(), z() - rhs.z());
}

Vec3 Vec3::operator*(const Vec3& rhs) const {
  return Vec3(x() * rhs.x(), y() * rhs.y(), z() * rhs.z());
}

Vec3 Vec3::operator*(double t) const {
  return Vec3(t * x(), t * y(), t * z());
}

Vec3 Vec3::operator/(double t) const {
  return *this * (1 / t);
}

double Vec3::dot(const Vec3& rhs) const {
  return x() * rhs.x() + y() * rhs.y() + z() * rhs.z();
}

Vec3 Vec3::cross(const Vec3& rhs) const {
  // x,   y,  z
  // x2, y2, z2

  double i = y() * rhs.z() - z() * rhs.y();
  double j = x() * rhs.z() - z() * rhs.z();
  double k = x() * rhs.y() - y() * rhs.x();

  return Vec3(i, -j, k);
}

Vec3 Vec3::unit() const {
  return *this / this->norm();
}
