#include "InOneWeekendJeff/materials/diffuse_light.h"

#include "InOneWeekendJeff/textures/solid_color_texture.h"

DiffuseLight::DiffuseLight(std::unique_ptr<Texture> texture)
    : texture_(std::move(texture)) {}

DiffuseLight::DiffuseLight(const Color& color)
    : texture_(std::make_unique<SolidColorTexture>(color)) {}

Color DiffuseLight::Emit(double u, double v, const Point3& p) const {
  return texture_->value(u, v, p);
}
