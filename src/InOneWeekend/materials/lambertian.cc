#include "InOneWeekend/materials/lambertian.h"

#include "InOneWeekend/color.h"
#include "InOneWeekend/hittable.h"
#include "InOneWeekend/materials/material.h"
#include "InOneWeekend/vec3.h"

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
  scattered = Ray(hit_result.p, v);
  attenuation = albedo_;
  return true;
}
