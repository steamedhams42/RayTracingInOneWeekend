#include "sphere.h"

#include <cassert>
#include <cmath>

#include "InOneWeekendJeff/constants.h"
#include "InOneWeekendJeff/geometry/ray.h"
#include "InOneWeekendJeff/materials/lambertian.h"

// Stationary sphere
Sphere::Sphere(Point3 center, double r, std::shared_ptr<Material> material)
    : Sphere(center, center, r, material) {
  bounding_box_ = BoundingBox(Interval(center.x() - r, center.x() + r),
                              Interval(center.y() - r, center.y() + r),
                              Interval(center.z() - r, center.z() + r));
}

// Moving sphere
Sphere::Sphere(Point3 center_init,
               Point3 center_final,
               double radius,
               std::shared_ptr<Material> material)
    : center_(Ray(center_init, center_final - center_init)),
      radius_(radius),
      material_(material) {
  assert(radius > 0);
}

Sphere::~Sphere() {}

bool Sphere::Hit(const Ray& ray,
                 Interval intval,
                 Hittable::HitResult& result) const {
  // TODO: Put into a "find discriminant" method.
  Point3 current_center = center_.at(ray.time());
  Vec3 QC = current_center - ray.origin();
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
  // ray's that originate exactly on the surface of the hittable.
  // This causes a bug when reflecting a ray off a surface and the ray is
  // counted as a 'hit'.
  t_minus = intval.surrounds(t_minus) ? t_minus : constants::INF_DOUBLE;
  t_plus = intval.surrounds(t_plus) ? t_plus : constants::INF_DOUBLE;
  double t = std::fmin(t_plus, t_minus);
  if (t == constants::INF_DOUBLE) {
    return false;
  }

  result.t = t;
  result.incident_point = ray.at(t);
  Vec3 normal = (result.incident_point - current_center) / this->radius_;
  result.SetFaceNormal(ray, normal);
  result.material = material_.get();
  setUvCoordinates(normal, result);

  return true;
}

void Sphere::setUvCoordinates(const Vec3& surface_normal,
                              HitResult& result) const {
  // theta is the angle between y-axis and xz plane (polar angle).
  // phi is the angle between x and z-axis (azimuthal angle).
  // u, v in [0, 1]
  // u is the horizontal component of the (u, v) projection represented as a
  // ratio. v is the vertical.
  double theta = std::acos(-surface_normal.y());
  double phi =
      std::atan2(-surface_normal.z(), surface_normal.x()) + constants::PI;
  result.u = phi / (2 * constants::PI);
  result.v = theta / constants::PI;
}

BoundingBox Sphere::bounding_box() {
  return bounding_box_;
}