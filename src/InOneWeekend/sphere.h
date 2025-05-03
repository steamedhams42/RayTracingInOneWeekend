#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "interval.h"
#include "point3.h"
#include "vec3.h"

class Ray;

class Sphere : public Hittable {
 public:
  Sphere(Point3, double);
  ~Sphere() override;

  // Returns a random unit vector in the same direction as |surface_norm|
  static Vec3 random_vec3_on_surface(const Vec3& surface_norm);

  bool hit(const Ray& ray, Interval intval, HitResult& result) const override;

 private:
  Point3 center_;
  double radius_;
};

#endif