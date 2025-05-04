#include "sphere.h"

#include <cassert>
#include "constants.h"
#include "ray.h"

Sphere::Sphere(Point3 center, double r) : center_(center), radius_(r) {
  assert(radius_ >= 0);
  // TODO: init *material_
}

Sphere::~Sphere() {}

bool Sphere::hit(const Ray& ray,
                 Interval intval,
                 Hittable::HitResult& result) const {
  // TODO: Put into a "find discriminant" method.
  Vec3 QC = center_ - ray.origin();
  double a = ray.direction().dot(ray.direction());
  double b = -2 * ray.direction().dot(QC);
  double c = QC.dot(QC) - radius_ * radius_;
  double discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    return false;
  }

  // Try both discriminants, pick the one that is within bounds and minimal.
  // TODO: Put into a "find closest discriminant" method.
  const double sqrtd = std::sqrt(discriminant);
  double t_minus = (-b - sqrtd) / (2 * a);
  double t_plus = (-b + sqrtd) / (2 * a);

  // Must use surrounds (exclusve) rather than contains (inclusive) to reject
  // ray's that are originate exactly on the surface of the hittable.
  t_minus = intval.surrounds(t_minus) ? t_minus : constants::INF_DOUBLE;
  t_plus = intval.surrounds(t_plus) ? t_plus : constants::INF_DOUBLE;
  double t = std::fmin(t_plus, t_minus);
  if (t == constants::INF_DOUBLE) {
    return false;
  }

  result.t = t;
  result.p = ray.at(t);
  Vec3 normal = (result.p - this->center_) / this->radius_;
  result.setFaceNormal(ray, normal);
  result.material = material_;

  return true;
}