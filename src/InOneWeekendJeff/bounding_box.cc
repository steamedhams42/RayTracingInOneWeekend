#include "InOneWeekendJeff/bounding_box.h"

#include <cmath>

BoundingBox::BoundingBox() {}

BoundingBox::BoundingBox(Interval&& x, Interval&& y, Interval&& z)
    : x_(std::move(x)), y_(std::move(y)), z_(std::move(z)) {}

BoundingBox::~BoundingBox() = default;

bool BoundingBox::operator==(const BoundingBox& rhs) const {
  return x_ == rhs.x_ and y_ == rhs.y_ and z_ == rhs.z_;
}

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

bool BoundingBox::hit(const Ray& incident_ray, Interval ray_t_interval) const {
  const Point3 origin = incident_ray.origin();
  const Vec3 ray_direction = incident_ray.direction();

  for (int axis = 0; axis < 3; axis++) {
    double vector_component = ray_direction[axis];

    double t_close = (ray_t_interval.min() - origin[axis]) / vector_component;
    double t_far = (ray_t_interval.max() - origin[axis]) / vector_component;

    // Workaround for NaNs
    ray_t_interval.set_min(std::max(
        t_close, std::min(std::min(t_far, t_close), ray_t_interval.max())));

    ray_t_interval.set_max(std::min(
        t_far, std::max(std::max(t_far, t_close), ray_t_interval.min())));

    if (ray_t_interval.is_empty()) {
      return false;
    }
  }

  return true;
}

// static
BoundingBox BoundingBox::CreateBoundingBoxFromTwoBoundingBoxes(
    const BoundingBox& lhs,
    const BoundingBox& rhs) {
  auto x = Interval::EncloseTwoIntervals(lhs.x_, rhs.x_);
  auto y = Interval::EncloseTwoIntervals(lhs.y_, rhs.y_);
  auto z = Interval::EncloseTwoIntervals(lhs.z_, rhs.z_);
  return BoundingBox(std::move(x), std::move(y), std::move(z));
}
