#include "InOneWeekendJeff/textures/checker_texture.h"

#include <cmath>

#include "InOneWeekendJeff/textures/solid_color_texture.h"
#include "InOneWeekendJeff/textures/texture.h"

CheckerTexture::CheckerTexture(double scale,
                               std::unique_ptr<Texture> even,
                               std::unique_ptr<Texture> odd)
    : inv_scale_(1.0 / scale), even_(std::move(even)), odd_(std::move(odd)) {}

CheckerTexture::CheckerTexture(double scale, Color even, Color odd)
    : CheckerTexture(scale,
                     std::make_unique<SolidColorTexture>(even),
                     std::make_unique<SolidColorTexture>(odd)) {}

Color CheckerTexture::value(double u, double v, const Point3& p) const {
  int x_coordinate = int(std::floor(inv_scale_ * p.x()));
  int y_coordinate = int(std::floor(inv_scale_ * p.y()));
  int z_coordinate = int(std::floor(inv_scale_ * p.z()));
  int is_odd = (x_coordinate + y_coordinate + z_coordinate) % 2;
  return is_odd ? odd_->value(u, v, p) : even_->value(u, v, p);
}