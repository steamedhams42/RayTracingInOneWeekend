#include "sphere.h"

#include <cassert>
#include "constants.h"
#include "ray.h"

Sphere::Sphere(Point3 center, double r) : center_(center), radius_(r) {
  assert(radius_ >= 0);
}

Sphere::~Sphere() {}

bool Sphere::hit(const Ray& ray,
                 double ray_tmin,
                 double ray_tmax,
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
  auto is_within_bounds = [&](double value) -> bool {
    return ray_tmin <= value and value <= ray_tmax;
  };
  t_minus = is_within_bounds(t_minus) ? t_minus : constants::INF_DOUBLE;
  t_plus = is_within_bounds(t_plus) ? t_plus : constants::INF_DOUBLE;
  double t = std::fmin(t_plus, t_minus);
  if (t == constants::INF_DOUBLE) {
    return false;
  }

  // TODO: Refactor the HitResult class and the setNormal method. Footgun.
  result.t = t;
  result.p = ray.at(t);
  Vec3 normal = (result.p - this->center_) / this->radius_;
  result.setFaceNormal(ray, normal);

  return true;
}
