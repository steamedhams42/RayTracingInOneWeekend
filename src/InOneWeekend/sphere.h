#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "point3.h"

class Ray;

class Sphere : public Hittable {
 public:
  Sphere(Point3, double);
  ~Sphere() override;

  bool hit(const Ray& r,
           double ray_tmin,
           double ray_tmax,
           HitResult& rec) const override;

 private:
  Point3 center_;
  double radius_;
};

#endif