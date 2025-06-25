#include "InOneWeekendJeff/textures/solid_color_texture.h"

#include <utility>

SolidColorTexture::SolidColorTexture(const Color& albedo) : albedo_(albedo) {}

SolidColorTexture::SolidColorTexture(Color&& albedo)
    : albedo_(std::move(albedo)) {}

template <typename T>
SolidColorTexture::SolidColorTexture(T&& r, T&& g, T&& b)
    : SolidColorTexture(
          Color(std::forward<T>(r), std::forward<T>(g), std::forward<T>(b))) {}

Color SolidColorTexture::value(double u, double v, const Point3& p) const {
  return Color();
}