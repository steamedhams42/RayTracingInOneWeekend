#ifndef RAY_H
#define RAY_H

#include "point3.h"
#include "vec3.h"

class Ray {
 public:
  Ray() = default;
  Ray(const Point3& origin, const Vec3& direction, double time = 0);
  bool operator==(const Ray& rhs);

  const Point3& origin() const;
  const Vec3& direction() const;

  // t is the scale factor of the ray's vector.
  // e.g. If the ray is (0, 0, 3) and t is 1/6, then the ray is scales down to
  // (0, 0, 0.5). Refer to parametric equation: P(t) = Q + t * v
  Point3 at(double t) const;

  double time() const;

 private:
  Point3 origin_;
  Vec3 direction_;
  double time_;
};

#endif