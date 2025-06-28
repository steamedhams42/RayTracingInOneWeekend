#include "InOneWeekendJeff/textures/image_texture.h"

#include <cassert>
#include "InOneWeekendJeff/interval.h"

ImageTexture::ImageTexture(const char* filename) : image_(filename) {}

Color ImageTexture::value(double u, double v, const Point3& p) const {
  if (image_.height() <= 0) {
    assert(false);
  }

  u = Interval(0, 1).clamp(u);
  v = 1.0 - Interval(0, 1).clamp(v);

  int i = int(u * image_.width());
  int j = int(v * image_.height());
  const unsigned char* pixel = image_.pixel_data(i, j);
  double color_scale = 1.0 / 255.0;
  return Color(color_scale * pixel[0], color_scale * pixel[1],
               color_scale * pixel[2]);
}