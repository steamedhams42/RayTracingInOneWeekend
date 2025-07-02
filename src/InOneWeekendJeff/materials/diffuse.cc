#include "InOneWeekendJeff/materials/diffuse.h"

#include "InOneWeekendJeff/textures/solid_color_texture.h"

Diffuse::Diffuse(std::unique_ptr<Texture> texture)
    : texture_(std::move(texture)) {}

Diffuse::Diffuse(const Color& color)
    : texture_(std::make_unique<SolidColorTexture>(color)) {}

Color Diffuse::Emit(double u, double v, const Point3& p) {
  return texture_->value(u, v, p);
}
