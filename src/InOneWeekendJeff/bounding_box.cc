#include "InOneWeekendJeff/bounding_box.h"

#include <cmath>

BoundingBox::BoundingBox() {}

BoundingBox::BoundingBox(const Interval& x,
                         const Interval& y,
                         const Interval& z)
    : x_(x), y_(y), z_(z) {}

// static
BoundingBox BoundingBox::CreateBoundingBoxFromTwoPoints(const Point3& a,
                                                        const Point3& b) {
  Interval x_interval(std::min(a.x(), b.x()), std::max(a.x(), b.x()));
  Interval y_interval(std::min(a.y(), b.y()), std::max(a.y(), b.y()));
  Interval z_interval(std::min(a.z(), b.z()), std::max(a.z(), b.z()));
  return BoundingBox(x_interval, y_interval, z_interval);
}