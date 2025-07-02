#include "InOneWeekendJeff/geometry/point3.h"

#include <cmath>

double Point3::operator[](int i) const {
  return points_[i];
}

double Point3::norm() const {
  return std::sqrt(norm_squared());
}

double Point3::norm_squared() const {
  return points_[0] * points_[0] + points_[1] * points_[1] +
         points_[2] * points_[2];
}
