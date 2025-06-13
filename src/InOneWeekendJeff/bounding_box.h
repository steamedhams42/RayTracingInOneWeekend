#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "InOneWeekendJeff/interval.h"
#include "InOneWeekendJeff/point3.h"
#include "InOneWeekendJeff/ray.h"

// 3D axis-aligned bounding box.
class BoundingBox {
 public:
  // No-arg c'tor creates 3 empty intervals
  BoundingBox();
  BoundingBox(Interval&&, Interval&&, Interval&&);
  BoundingBox(const BoundingBox&) = default;
  BoundingBox& operator=(const BoundingBox&) = default;
  ~BoundingBox();

  const Interval& x_interval();
  const Interval& y_interval();
  const Interval& z_interval();

  // Utilizes the slab method algorithm to determine if a ray intersects a BB.
  // https://en.wikipedia.org/wiki/Slab_method
  bool hit(const Ray& incident_ray, Interval ray_t_interval) const;

  // Takes two points in R3 and returns the smallest axis-aligned bounding box.
  static BoundingBox CreateBoundingBoxFromTwoPoints(const Point3&,
                                                    const Point3&);

 private:
  Interval x_, y_, z_;
};

#endif