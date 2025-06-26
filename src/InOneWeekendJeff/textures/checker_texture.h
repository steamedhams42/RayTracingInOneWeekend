#ifndef CHECKER_TEXTURE_H
#define CHECKER_TEXTURE_H

#include <memory>

#include "InOneWeekendJeff/textures/solid_color_texture.h"
#include "InOneWeekendJeff/textures/texture.h"

class Color;

class CheckerTexture : public Texture {
 public:
  CheckerTexture(double scale,
                 std::unique_ptr<Texture> even,
                 std::unique_ptr<Texture> odd);
  CheckerTexture(double scale, Color even, Color odd);

  Color value(double u, double v, const Point3& p) const override;

 private:
  // Controls the size of the checkered pattern i.e. larger/smaller squares.
  double inv_scale_;

  // Textures for even and odd cells of the checkerboard.
  std::unique_ptr<Texture> even_;
  std::unique_ptr<Texture> odd_;
};

#endif