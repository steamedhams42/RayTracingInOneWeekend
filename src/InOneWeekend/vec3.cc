#include "vec3.h"
#include "constants.h"
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
Vec3 Vec3::random_vec3(double min, double max) {
  return Vec3(Random::random_real(min, max), Random::random_real(min, max),
              Random::random_real(min, max));
}

// static
Vec3 Vec3::random_unit_vec3() {
  while (true) {
    Vec3 v = random_vec3(-1, 1);
    double f = v.norm_squared();
    if (constants::EPS_ZERO <= f and f <= 1) {
      // Due to floating point errors, the length^2 of the vector must be
      // greater than an EPS otherwise sqrt(f) == 0 and cause division by zero.
      return v / sqrt(f);
    }
  }
}

// static
Vec3 Vec3::random_vec3_on_surface(const Vec3& surface_norm) {
  Vec3 random_unit_vec = Vec3::random_unit_vec3();
  if (random_unit_vec.dot(surface_norm) > 0) {
    return random_unit_vec;
  } else {
    return -random_unit_vec;
  }
}

// static
Vec3 Vec3::reflect(const Vec3& incident, const Vec3& surface_norm) {
  return incident - 2 * (incident.dot(surface_norm)) * surface_norm;
}

bool Vec3::is_near_zero() const {
  double s = 1e-8;
  return std::fabs(points_[0] < s) and std::fabs(points_[1] < s) and
         std::fabs(points_[2] < s);
}
