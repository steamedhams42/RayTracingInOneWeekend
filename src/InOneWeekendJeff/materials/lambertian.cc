#include "InOneWeekendJeff/materials/lambertian.h"

#include "InOneWeekendJeff/color.h"
#include "InOneWeekendJeff/hittable.h"
#include "InOneWeekendJeff/materials/material.h"
#include "InOneWeekendJeff/vec3.h"

Lambertian::Lambertian() : albedo_(Color(0.5, 0.5, 0.5)) {}

Lambertian::Lambertian(const Color& albedo) : albedo_(albedo) {}

Lambertian::~Lambertian() = default;

bool Lambertian::scatter(const Ray& incident_ray,
                         const Hittable::HitResult& hit_result,
                         Color& attenuation,
                         Ray& scattered) const {
  auto v = Vec3::random_unit_vec3() + hit_result.normal;
  if (v.is_near_zero()) {
    v = hit_result.normal;
  }
  scattered = Ray(hit_result.incident_point, v);
  attenuation = albedo_;
  return true;
}
