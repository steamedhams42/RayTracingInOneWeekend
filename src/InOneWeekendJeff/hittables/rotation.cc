#include "InOneWeekendJeff/hittables/rotation.h"

Rotation::Rotation(std::shared_ptr<Hittable> hittable,
                   double degrees_of_rotation)
    : hittable_(hittable), degrees_of_rotation_(degrees_of_rotation) {}

bool Rotation::Hit(const Ray& incident_ray,
                   Interval ival,
                   Hittable::HitResult& result) const {}

BoundingBox Rotation::bounding_box() {
  return bounding_box_;
}
