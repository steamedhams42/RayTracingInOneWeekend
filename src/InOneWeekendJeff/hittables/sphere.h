#ifndef SPHERE_H
#define SPHERE_H

#include <memory>

#include "InOneWeekendJeff/bounding_box.h"
#include "InOneWeekendJeff/hittables/hittable.h"
#include "InOneWeekendJeff/interval.h"
#include "InOneWeekendJeff/materials/lambertian.h"
#include "InOneWeekendJeff/materials/material.h"
#include "InOneWeekendJeff/point3.h"

class Ray;
class SphereTest;

class Sphere : public Hittable {
 public:
  // Stationary sphere
  Sphere(Point3 center, double radius);
  Sphere(Point3 center, double radius, std::unique_ptr<Material>);

  // Moving sphere
  Sphere(Point3 center_init,
         Point3 center_final,
         double radius,
         std::unique_ptr<Material> = std::make_unique<Lambertian>());
  ~Sphere() override;

  bool hit(const Ray& ray, Interval intval, HitResult& result) const override;
  // Calculates and sets the (u, v) coordinates from the surface normal of
  // the incidence point. Transforms 3D coordinates to a (u, v) projection.
  void setUvCoordinates(const Vec3& surface_normal, HitResult& result) const;

  BoundingBox bounding_box() override;

 private:
  friend SphereTest;

  // The sphere's center travels linearly from init to final described by a
  // ray on the interval t = [0, 1)
  Ray center_;
  double radius_;
  std::unique_ptr<Material> material_;
  BoundingBox bounding_box_;
};

#endif