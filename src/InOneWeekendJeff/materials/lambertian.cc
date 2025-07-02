#include "InOneWeekendJeff/materials/lambertian.h"

#include <memory>

#include "InOneWeekendJeff/color.h"
#include "InOneWeekendJeff/geometry/vec3.h"
#include "InOneWeekendJeff/hittables/hittable.h"
#include "InOneWeekendJeff/materials/material.h"
#include "InOneWeekendJeff/textures/solid_color_texture.h"

Lambertian::Lambertian() : Lambertian(Color(0.5, 0.5, 0.5)) {}

Lambertian::Lambertian(const Color& color)
    : albedo_(std::make_unique<SolidColorTexture>(color)) {}

Lambertian::Lambertian(std::unique_ptr<Texture> texture)
    : albedo_(std::move(texture)) {}

Lambertian::~Lambertian() = default;

bool Lambertian::Scatter(const Ray& incident_ray,
                         const Hittable::HitResult& hit_result,
                         Color& attenuation,
                         Ray& scattered) const {
  auto v = Vec3::random_unit_vec3() + hit_result.normal;
  if (v.is_near_zero()) {
    v = hit_result.normal;
  }
  scattered = Ray(hit_result.incident_point, v, incident_ray.time());
  attenuation =
      albedo_->value(hit_result.u, hit_result.v, hit_result.incident_point);
  return true;
}
