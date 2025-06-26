#ifndef TEXTURE_H
#define TEXTURE_H

#include "InOneWeekendJeff/color.h"
#include "InOneWeekendJeff/point3.h"

class Texture {
 public:
  virtual ~Texture() = default;

  // Returns a color from the projection mapping defined by each implementer.
  // For a constant texture, every (u,v) pair yields a constant color, so we can
  // ignore the 3D coordinates. However, other texture types will need these
  // coordinates, so we keep these in the method interface.
  virtual Color value(double u, double v, const Point3& p) const = 0;
};

#endif