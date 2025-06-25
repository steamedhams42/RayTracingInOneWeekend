#ifndef SOLID_COLOR_TEXTURE_H
#define SOLID_COLOR_TEXTURE_H

#include "InOneWeekendJeff/color.h"
#include "texture.h"

class Point3;

class SolidColorTexture : public Texture {
 public:
  SolidColorTexture(const Color&);
  SolidColorTexture(Color&&);

  template <typename T>
  SolidColorTexture(T&&, T&&, T&&);

  Color value(double u, double v, const Point3& p) const override;

 private:
  Color albedo_;
};

#endif