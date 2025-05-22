#include "InOneWeekendJeff/materials/dielectric.h"

#include <cmath>

#include "InOneWeekendJeff/color.h"
#include "InOneWeekendJeff/hittable.h"
#include "InOneWeekendJeff/ray.h"

Dielectric::Dielectric(const double refraction_index)
    : refraction_index_(refraction_index) {}

bool Dielectric::scatter(const Ray& incident_ray,
                         const Hittable::HitResult& result,
                         Color& attenuation,
                         Ray& scattered) const {
  attenuation = Color(1.0, 1.0, 1.0);
  double ri = result.front_face ? (1.0 / refraction_index_) : refraction_index_;

  Vec3 unit_direction = incident_ray.direction().unit();
  Vec3 refracted = refract(unit_direction, result.normal, ri);

  scattered = Ray(result.p, refracted);
  return true;
}

Vec3 Dielectric::refract(
    const Vec3& uv,
    const Vec3& n,
    double ingress_over_egress_refractive_index_ratio) const {
  double r = ingress_over_egress_refractive_index_ratio;
  double c = -n.dot(uv);
  auto y = std::max(0.0, 1 - r * r * (1 - c * c));
  return r * uv + (r * c - std::sqrt(y)) * n;
}
