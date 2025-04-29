#ifndef HITTABLE_H
#define HITTABLE_H

#include "point3.h"
#include "vec3.h"

class Ray;

class HitRecord {
 public:
  Point3 p;
  Vec3 normal;
  double t;
};

class Hittable {
 public:
  virtual ~Hittable() = default;
  virtual bool hit(const Ray& r,
                   double ray_tmin,
                   double ray_tmax,
                   HitRecord& rec) const = 0;
};

#endif