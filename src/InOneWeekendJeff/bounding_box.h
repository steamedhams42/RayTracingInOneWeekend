#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "InOneWeekendJeff/interval.h"
#include "InOneWeekendJeff/point3.h"

// 3D axis-aligned bounding box.
class BoundingBox {
 public:
  // No-arg c'tor BoundingBox() are 3 empty intervals
  BoundingBox();
  BoundingBox(Interval&&, Interval&&, Interval&&);
  BoundingBox(const BoundingBox&) = delete;
  BoundingBox& operator=(const BoundingBox&) = delete;
  ~BoundingBox();

  const Interval& x_interval();
  const Interval& y_interval();
  const Interval& z_interval();

  // Takes two points in R3 and returns the smallest axis-aligned bounding box.
  static BoundingBox CreateBoundingBoxFromTwoPoints(const Point3&,
                                                    const Point3&);

 private:
  Interval x_, y_, z_;
};

#endif