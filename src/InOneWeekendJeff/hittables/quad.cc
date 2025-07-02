#include "InOneWeekendJeff/hittables/quad.h"

#include <cmath>

#include "InOneWeekendJeff/constants.h"
#include "InOneWeekendJeff/materials/lambertian.h"

Quad::Quad(const Point3& q, const Vec3& u, const Vec3& v)
    : Quad(q, u, v, std::make_unique<Lambertian>()) {}

Quad::Quad(const Point3& q,
           const Vec3& u,
           const Vec3& v,
           std::unique_ptr<Material> mat)
    : Q_(q), u_(u), v_(v), material_(std::move(mat)) {
  SetBoundingBox();

  auto n = u_.cross(v_);
  normal_ = n.unit();

  // Ax + By + Cz = D
  D_ = normal_.dot(Vec3(Q_));
  w_ = n / (n.dot(n));
}

void Quad::SetBoundingBox() {
  BoundingBox diagonal(Q_, Q_ + u_ + v_);
  BoundingBox diagonal2(Q_ + u_, Q_ + v_);
  bounding_box_ = BoundingBox(diagonal, diagonal2);
}

bool Quad::hit(const Ray& incident_ray,
               Interval hit_ival,
               Hittable::HitResult& result) const {
  Vec3 incident_direction = incident_ray.direction();
  double nd = normal_.dot(incident_direction);
  if (std::fabs(nd) < constants::EPS_ERROR) {
    // Incident ray is parallel to the plane.
    return false;
  }

  double t = (D_ - normal_.dot(Vec3(incident_ray.origin()))) / nd;
  if (!hit_ival.contains(t)) {
    return false;
  }

  auto incident_point = incident_ray.at(t);
  Vec3 planar_hit_vector(incident_point - Q_);
  double alpha = w_.dot(planar_hit_vector.cross(v_));
  double beta = w_.dot(u_.cross(planar_hit_vector));

  if (!DoesHitQuad(alpha, beta)) {
    return false;
  }
  result.u = alpha;
  result.v = beta;
  result.t = t;
  result.incident_point = incident_point;
  result.setFaceNormal(incident_ray, normal_);
  result.material = material_.get();
  return true;
}

bool Quad::DoesHitQuad(double alpha, double beta) const {
  Interval unit(0, 1);
  if (!unit.contains(alpha) or !unit.contains(beta)) {
    return false;
  }
  return true;
}

BoundingBox Quad::bounding_box() {
  return bounding_box_;
}
