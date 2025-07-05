#include "InOneWeekendJeff/bounding_box.h"

#include <cmath>

#include "InOneWeekendJeff/constants.h"

BoundingBox::BoundingBox() {}

template <typename T>
BoundingBox::BoundingBox(T&& x, T&& y, T&& z)
    : x_(std::forward<T>(x)), y_(std::forward<T>(y)), z_(std::forward<T>(z)) {}

BoundingBox::~BoundingBox() = default;

bool BoundingBox::operator==(const BoundingBox& rhs) const {
  return x_ == rhs.x_ and y_ == rhs.y_ and z_ == rhs.z_;
}

BoundingBox::BoundingBox(const Point3& a, const Point3& b)
    : BoundingBox(Interval(std::min(a.x(), b.x()), std::max(a.x(), b.x())),
                  Interval(std::min(a.y(), b.y()), std::max(a.y(), b.y())),
                  Interval(std::min(a.z(), b.z()), std::max(a.z(), b.z()))) {}

BoundingBox::BoundingBox(const BoundingBox& lhs, const BoundingBox& rhs)
    : BoundingBox(Interval::EncloseTwoIntervals(lhs.x_, rhs.x_),
                  Interval::EncloseTwoIntervals(lhs.y_, rhs.y_),
                  Interval::EncloseTwoIntervals(lhs.z_, rhs.z_)) {}

const Interval& BoundingBox::x_interval() const {
  return this->x_;
}

const Interval& BoundingBox::y_interval() const {
  return this->y_;
}

const Interval& BoundingBox::z_interval() const {
  return this->z_;
}

const Interval& BoundingBox::get_axis(int i) const {
  if (i == 0) {
    return x_interval();
  } else if (i == 1) {
    return y_interval();
  } else {
    return z_interval();
  }
}

bool BoundingBox::Hit(const Ray& incident_ray, Interval ray_t_interval) const {
  const Point3 origin = incident_ray.origin();
  const Vec3 ray_direction = incident_ray.direction();

  for (int axis = 0; axis < 3; axis++) {
    Interval current_axis = get_axis(axis);
    // Expands an interval by an epsilon if it is close to zero. This is to
    // give quadrilaterals an "infinitesimal" width for hit detection.
    if (current_axis.width() < constants::EPS_BB_PADDING) {
      current_axis = current_axis.expand(constants::EPS_BB_PADDING / 2.0);
    }
    double vector_component = ray_direction[axis];

    double t_close = (current_axis.min() - origin[axis]) / vector_component;
    double t_far = (current_axis.max() - origin[axis]) / vector_component;

    // DO NOT try to simplify this mess. Source of a nasty bug regarding NaNs.
    ray_t_interval.set_min(
        std::max(ray_t_interval.min(),
                 std::min(std::min(t_far, t_close), ray_t_interval.max())));

    ray_t_interval.set_max(
        std::min(ray_t_interval.max(),
                 std::max(std::max(t_far, t_close), ray_t_interval.min())));

    if (ray_t_interval.is_empty()) {
      return false;
    }
  }

  return true;
}

int BoundingBox::longest_axis() {
  if (x_.width() >= y_.width() and x_.width() >= z_.width()) {
    // (x >= y >= z) or (x >= z >= y)
    return 0;
  } else if (y_.width() >= x_.width() and y_.width() >= z_.width()) {
    // (y >= x >= z) or (y >= z >= x)
    return 1;
  }
  return 2;
}

bool BoundingBox::is_empty() {
  return x_.is_empty() and y_.is_empty() and z_.is_empty();
}