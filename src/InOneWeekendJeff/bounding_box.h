#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "InOneWeekendJeff/geometry/point3.h"
#include "InOneWeekendJeff/geometry/ray.h"
#include "InOneWeekendJeff/interval.h"

// 3D axis-aligned bounding box.
class BoundingBox {
 public:
  // No-arg c'tor creates 3 empty intervals
  BoundingBox();
  template <typename T>
  BoundingBox(T&&, T&&, T&&);
  // Takes two points in R3 and returns the smallest bounding box.
  BoundingBox(const Point3&, const Point3&);
  // Returns the smallest bounding box that encloses two bounding boxes.
  BoundingBox(const BoundingBox&, const BoundingBox&);

  BoundingBox(const BoundingBox&) = default;
  BoundingBox& operator=(const BoundingBox&) = default;
  ~BoundingBox();

  bool operator==(const BoundingBox&) const;
  friend BoundingBox operator+(const BoundingBox& lhs, const Vec3& rhs);
  friend BoundingBox operator+(const Vec3& lhs, const BoundingBox& rhs);

  const Interval& x_interval() const;
  const Interval& y_interval() const;
  const Interval& z_interval() const;

  // Utilizes the slab method algorithm to determine if a ray intersects a BB.
  // https://en.wikipedia.org/wiki/Slab_method
  bool Hit(const Ray& incident_ray, Interval ray_t_interval) const;

  // Returns the longest axis (0 == x, 1 == y, 2 == z) of this bounding box.
  int longest_axis();

  bool is_empty();

 private:
  Interval x_, y_, z_;

  // Returns the interval for the requested axis (0 == x, 1 == y, 2 == z)
  const Interval& get_axis(int) const;

  friend std::ostream& operator<<(std::ostream& out, const BoundingBox& bbox) {
    return out << "x_interval: " << bbox.x_ << "y_interval: " << bbox.y_
               << "z_interval: " << bbox.z_;
  }
};

inline BoundingBox operator+(const BoundingBox& lhs, const Vec3& rhs) {
  return BoundingBox(Interval(lhs.x_interval().min() + rhs.x(),
                              lhs.x_interval().max() + rhs.x()),
                     Interval(lhs.y_interval().min() + rhs.y(),
                              lhs.y_interval().max() + rhs.y()),
                     Interval(lhs.z_interval().min() + rhs.z(),
                              lhs.z_interval().max() + rhs.z()));
}

inline BoundingBox operator+(const Vec3& lhs, const BoundingBox& rhs) {
  return rhs + lhs;
}

#endif