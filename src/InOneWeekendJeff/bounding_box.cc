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

bool BoundingBox::hit(const Ray& incident_ray, Interval ray_t_interval) {
  const Point3 origin = incident_ray.origin();
  const Vec3 ray_direction = incident_ray.direction();

  for (int axis = 0; axis < 3; axis++) {
    double vector_component = ray_direction[axis];

    double t_close = (ray_t_interval.min() - origin[axis]) / vector_component;
    double t_far = (ray_t_interval.max() - origin[axis]) / vector_component;

    if (t_close > t_far) {
      std::swap(t_close, t_far);
    }

    ray_t_interval.min(std::max(ray_t_interval.min(), t_close));
    ray_t_interval.max(std::min(ray_t_interval.max(), t_far));

    if (ray_t_interval.is_empty())
      return false;
  }

  return true;
}