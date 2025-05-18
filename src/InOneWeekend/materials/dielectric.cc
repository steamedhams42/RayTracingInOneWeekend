#include "InOneWeekend/materials/dielectric.h"

#include <cmath>

#include "InOneWeekend/color.h"
#include "InOneWeekend/hittable.h"
#include "InOneWeekend/ray.h"

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

Vec3 Dielectric::refract(const Vec3& uv,
                         const Vec3& n,
                         double etai_over_etat) const {
  // auto cos_theta = std::fmin(-uv.dot(n), 1.0);
  // Vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
  // Vec3 r_out_parallel =
  //     -std::sqrt(std::fabs(1.0 - r_out_perp.norm_squared())) * n;
  // return r_out_perp + r_out_parallel;

  double r = etai_over_etat;
  double c = -n.dot(uv);
  return r * uv + (r * c - std::sqrt(1 - r * r * (1 - c * c))) * n;
}
