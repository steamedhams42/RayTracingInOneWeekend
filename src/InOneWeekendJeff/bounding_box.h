#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "InOneWeekendJeff/interval.h"
#include "InOneWeekendJeff/point3.h"

// 3D axis-aligned bounding box.
class BoundingBox {
 public:
  // Default BoundingBox are 3 empty intervals
  BoundingBox();
  BoundingBox(const Interval&, const Interval&, const Interval&);
  BoundingBox(const BoundingBox&) = delete;
  BoundingBox& operator=(const BoundingBox&) = delete;
  ~BoundingBox() = default;

  static BoundingBox CreateBoundingBoxFromTwoPoints(const Point3&,
                                                    const Point3&);

 private:
  Interval x_, y_, z_;
};

#endif