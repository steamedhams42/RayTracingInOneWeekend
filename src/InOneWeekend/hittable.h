#ifndef HITTABLE_H
#define HITTABLE_H

#include "point3.h"
#include "vec3.h"

class Ray;

class Hittable {
 public:
  struct HitResult {
    // This struct encapsulates the parameters that define a ray's point of
    // intersection on a Hittable object based on the following equation:
    // P(t) = O + t*d
    // Where O is the origin, t is the scale factor, d is the vector of the ray.

    // The point at which an object hits the Hittable.
    Point3 p;

    // The normalized vector on the surface of the hittable at the point of
    // intersection.
    Vec3 normal;

    // The scale factor of the ray that hits the Hittable.
    double t;
  };

  virtual ~Hittable() = default;
  virtual bool hit(const Ray& ray,
                   double ray_tmin,
                   double ray_tmax,
                   HitResult& result) const = 0;
};

#endif