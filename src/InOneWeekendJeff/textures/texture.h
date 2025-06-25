#ifndef TEXTURE_H
#define TEXTURE_H

#include "InOneWeekendJeff/color.h"
#include "InOneWeekendJeff/point3.h"

class Texture {
 public:
  virtual ~Texture() = default;

  virtual Color value(double u, double v, const Point3& p) const = 0;
};

#endif