#ifndef QUAD_H
#define QUAD_H

#include <memory>

#include "InOneWeekendJeff/Point3.h"
#include "InOneWeekendJeff/hittables/hittable.h"
#include "InOneWeekendJeff/materials/material.h"

class Quad : public Hittable {
 public:
  Quad(const Point3& q,
       const Vec3& u,
       const Vec3& v,
       std::unique_ptr<Material>);

  virtual void set_bounding_box();

  bool hit(const Ray& incident_ray,
           Interval ival,
           Hittable::HitResult& result) const override;

  BoundingBox bounding_box() override;

 private:
  // Bottom-left pivot point for the u, v vectors.
  Point3 q_;
  // u is horizontal component, v is vertical
  Vec3 u_, v_;

  std::unique_ptr<Material> material_;
  BoundingBox bounding_box_;
};

#endif