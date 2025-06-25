#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "InOneWeekendJeff/constants.h"
#include "InOneWeekendJeff/interval.h"
#include "InOneWeekendJeff/point3.h"
#include "InOneWeekendJeff/ray.h"

// 3D axis-aligned bounding box.
class BoundingBox {
 public:
  // No-arg c'tor creates 3 empty intervals
  BoundingBox();
  template <typename T>
  BoundingBox(T&&, T&&, T&&);
  BoundingBox(const BoundingBox&) = default;
  BoundingBox& operator=(const BoundingBox&) = default;
  ~BoundingBox();

  bool operator==(const BoundingBox&) const;

  const Interval& x_interval() const;
  const Interval& y_interval() const;
  const Interval& z_interval() const;

  // Utilizes the slab method algorithm to determine if a ray intersects a BB.
  // https://en.wikipedia.org/wiki/Slab_method
  bool hit(const Ray& incident_ray, Interval ray_t_interval) const;

  // Returns the longest axis (0 == x, 1 == y, 2 == z) of this bounding box.
  int longest_axis();

  // Takes two points in R3 and returns the smallest bounding box.
  static BoundingBox CreateBoundingBoxFromTwoPoints(const Point3&,
                                                    const Point3&);

  // Returns the smallest bounding box that encloses two bounding boxes.
  static BoundingBox CreateBoundingBoxFromTwoBoundingBoxes(const BoundingBox&,
                                                           const BoundingBox&);

  static BoundingBox empty();

 private:
  Interval x_, y_, z_;

  friend std::ostream& operator<<(std::ostream& out, const BoundingBox& bbox) {
    return out << "x_interval: " << bbox.x_ << "y_interval: " << bbox.y_
               << "z_interval: " << bbox.z_;
  }

  // Returns the interval for the requested axis (0 == x, 1 == y, 2 == z)
  const Interval& get_axis(int) const;
};

#endif