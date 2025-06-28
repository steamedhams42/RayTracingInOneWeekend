#include "InOneWeekendJeff/hittables/quad.h"

#include <cmath>

Quad::Quad(const Point3& q,
           const Vec3& u,
           const Vec3& v,
           std::unique_ptr<Material> mat)
    : q_(q), u_(u), v_(v), material_(std::move(mat)) {
  set_bounding_box();
}

void Quad::set_bounding_box() {
  BoundingBox diagonal(q_, q_ + u_ + v_);
  BoundingBox diagonal2(q_ + u_, q_ + v_);
  bounding_box_ = BoundingBox(diagonal, diagonal2);
}

bool Quad::hit(const Ray& incident_ray,
               Interval ival,
               Hittable::HitResult& result) const {
  // TODO: impl later
  return false;
}

BoundingBox Quad::bounding_box() {
  return bounding_box_;
}
