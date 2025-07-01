#include "InOneWeekendJeff/hittables/quad.h"

#include <cmath>

#include "InOneWeekendJeff/constants.h"

Quad::Quad(const Point3& q,
           const Vec3& u,
           const Vec3& v,
           std::unique_ptr<Material> mat)
    : Q_(q), u_(u), v_(v), material_(std::move(mat)) {
  set_bounding_box();
  auto cross = u_.cross(v_);
  normal_ = cross / cross.norm();

  // Ax + By + Cz = D
  D_ = normal_.dot(Vec3(Q_));
  w_ = normal_ / (normal_.dot(normal_));
}

void Quad::set_bounding_box() {
  BoundingBox diagonal(Q_, Q_ + u_ + v_);
  BoundingBox diagonal2(Q_ + u_, Q_ + v_);
  bounding_box_ = BoundingBox(diagonal, diagonal2);
}

bool Quad::hit(const Ray& incident_ray,
               Interval hit_ival,
               Hittable::HitResult& result) const {
  Vec3 incident_direction = incident_ray.direction();
  double nd = normal_.dot(incident_direction);
  if (nd < constants::EPS_ERROR) {
    // Incident ray is parallel to the plane.
    return false;
  }
  double t = (D_ - normal_.dot(Vec3(Q_))) / nd;
  if (!hit_ival.contains(t)) {
    // t is not in the hit interval.
    return false;
  }
  result.t = t;
  result.incident_point = incident_ray.at(result.t);
  result.setFaceNormal(incident_ray, normal_);
  result.material = material_.get();
  return true;
}

BoundingBox Quad::bounding_box() {
  return bounding_box_;
}
