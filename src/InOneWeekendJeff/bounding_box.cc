#include "InOneWeekendJeff/bounding_box.h"

#include <cmath>

BoundingBox::BoundingBox() {}

BoundingBox::BoundingBox(Interval&& x, Interval&& y, Interval&& z)
    : x_(std::move(x)), y_(std::move(y)), z_(std::move(z)) {}

BoundingBox::~BoundingBox() = default;

// static
BoundingBox BoundingBox::CreateBoundingBoxFromTwoPoints(const Point3& a,
                                                        const Point3& b) {
  Interval x_interval(std::min(a.x(), b.x()), std::max(a.x(), b.x()));
  Interval y_interval(std::min(a.y(), b.y()), std::max(a.y(), b.y()));
  Interval z_interval(std::min(a.z(), b.z()), std::max(a.z(), b.z()));
  return BoundingBox(std::move(x_interval), std::move(y_interval),
                     std::move(z_interval));
}

const Interval& BoundingBox::x_interval() {
  return this->x_;
}

const Interval& BoundingBox::y_interval() {
  return this->y_;
}

const Interval& BoundingBox::z_interval() {
  return this->z_;
}
