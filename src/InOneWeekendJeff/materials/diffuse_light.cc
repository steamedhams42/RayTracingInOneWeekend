#include "InOneWeekendJeff/materials/diffuse_light.h"

#include "InOneWeekendJeff/textures/solid_color_texture.h"

DiffuseLight::DiffuseLight(std::unique_ptr<Texture> texture, double intensity)
    : texture_(std::move(texture)), intensity_(intensity) {}

DiffuseLight::DiffuseLight(const Color& color, double intensity)
    : DiffuseLight(std::make_unique<SolidColorTexture>(color), intensity) {}

void DiffuseLight::set_intensity(double i) {
  intensity_ = i;
}

Color DiffuseLight::Emit(double u, double v, const Point3& p) const {
  return intensity_ * texture_->value(u, v, p);
}
