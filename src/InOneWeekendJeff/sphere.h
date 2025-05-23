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
  Sphere(Point3 center, double radius);
  Sphere(Point3 center, double radius, std::unique_ptr<Material>&&);

  // Moving sphere
  Sphere(Point3 center_init,
         Point3 center_final,
         double radius,
         std::unique_ptr<Material>&&);
  ~Sphere() override;

  bool hit(const Ray& ray, Interval intval, HitResult& result) const override;

 private:
  // The sphere's center travels linearly from init to final described by a
  // ray on the interval t = [0, 1)
  Ray center_;
  double radius_;
  std::unique_ptr<Material> material_;
};

#endif