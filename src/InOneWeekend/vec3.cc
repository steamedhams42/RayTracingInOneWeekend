#include "vec3.h"
#include "random.h"

Vec3 Vec3::operator+(const Vec3& rhs) {
  return Vec3(x() + rhs.x(), y() + rhs.y(), z() + rhs.z());
}

Vec3& Vec3::operator+=(const Vec3& rhs) {
  this->points_[0] += rhs.points_[0];
  this->points_[1] += rhs.points_[1];
  this->points_[2] += rhs.points_[2];
  return *this;
}

Vec3& Vec3::operator-() {
  return *this *= -1;
}

Vec3 Vec3::operator-(const Vec3& rhs) {
  return Vec3(x() - rhs.x(), y() - rhs.y(), z() - rhs.z());
}

Vec3& Vec3::operator-=(const Vec3& rhs) {
  this->points_[0] -= rhs.points_[0];
  this->points_[1] -= rhs.points_[1];
  this->points_[2] -= rhs.points_[2];
  return *this;
}

Vec3 Vec3::operator*(double t) const {
  return Vec3(t * x(), t * y(), t * z());
}

Vec3& Vec3::operator*=(double t) {
  points_[0] *= t;
  points_[1] *= t;
  points_[2] *= t;
  return *this;
}

Vec3 Vec3::operator/(double t) const {
  return *this * (1 / t);
}

Vec3& Vec3::operator/=(double t) {
  return *this *= (1 / t);
}

double Vec3::dot(const Vec3& rhs) const {
  return x() * rhs.x() + y() * rhs.y() + z() * rhs.z();
}

Vec3 Vec3::cross(const Vec3& rhs) const {
  //     x,     y,     z
  // rhs.x, rhs.y, rhs.z

  double i = y() * rhs.z() - z() * rhs.y();
  double j = x() * rhs.z() - z() * rhs.x();
  double k = x() * rhs.y() - y() * rhs.x();

  return Vec3(i, -j, k);
}

Vec3 Vec3::unit() const {
  return *this / this->norm();
}

// static
Vec3 Vec3::random_vec3() {
  return Vec3(Random::random_real(), Random::random_real(),
              Random::random_real());
}

// static
Vec3 Vec3::random_vec3(double min, double max) {
  return Vec3(Random::random_real(min, max), Random::random_real(min, max),
              Random::random_real(min, max));
}
