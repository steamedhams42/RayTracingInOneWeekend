#ifndef IMAGE_TEXTURE_H
#define IMAGE_TEXTURE_H

#include "InOneWeekendJeff/color.h"
#include "InOneWeekendJeff/rtw_stb_image.h"
#include "InOneWeekendJeff/textures/texture.h"

class ImageTexture : public Texture {
 public:
  ImageTexture(const char* filename);

  Color value(double u, double v, const Point3& p) const override;

 private:
  rtw_image image_;
};
#endif