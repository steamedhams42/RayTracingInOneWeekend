#include "InOneWeekendJeff/materials/isotropic.h"

#include "InOneWeekendJeff/textures/solid_color_texture.h"

Isotropic::Isotropic(const Color& albedo)
    : Isotropic(std::make_unique<SolidColorTexture>(albedo)) {}

Isotropic::Isotropic(std::unique_ptr<Texture> texture)
    : texture_(std::move(texture)) {}

bool Isotropic::Scatter(const Ray& incident_ray,
                        const Hittable::HitResult& result,
                        Color& attenuation,
                        Ray& scattered) const {
  scattered =
      Ray(result.incident_point, Vec3::random_unit_vec3(), incident_ray.time());
  attenuation = texture_->value(result.u, result.v, result.incident_point);
  return true;
}
