#ifndef SPHERE_H
#define SPHERE_H

#include <memory>

#include "hittable.h"
#include "interval.h"
#include "materials/material.h"
#include "point3.h"

class Ray;

class Sphere : public Hittable {
 public:
  Sphere(Point3, double);
  Sphere(Point3, double, std::unique_ptr<Material>&&);
  ~Sphere() override;

  bool hit(const Ray& ray, Interval intval, HitResult& result) const override;

 private:
  Point3 center_;
  double radius_;
  std::unique_ptr<Material> material_;
};

#endif