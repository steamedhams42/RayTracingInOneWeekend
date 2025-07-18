#ifndef QUAD_H
#define QUAD_H

#include <memory>

#include "InOneWeekendJeff/geometry/point3.h"
#include "InOneWeekendJeff/hittables/hittable.h"
#include "InOneWeekendJeff/materials/material.h"

class Quad : public Hittable {
 public:
  Quad(const Point3& q,
       const Vec3& u,
       const Vec3& v,
       std::shared_ptr<Material>);

  Quad(const Point3& q, const Vec3& u, const Vec3& v);

  virtual void SetBoundingBox();

  bool Hit(const Ray& incident_ray,
           Interval hit_ival,
           Hittable::HitResult& result) const override;

  virtual bool DoesHitQuad(double, double) const;

  BoundingBox bounding_box() override;

 private:
  // Bottom-left pivot point for the u, v vectors.
  Point3 Q_;
  // u is horizontal component, v is vertical
  Vec3 u_, v_;
  Vec3 w_;

  // A normalized vector orthogonal to the quad.
  Vec3 normal_;

  //  Constant from the equation of a plane:
  // Ax + By + Cz = D
  double D_;

  std::shared_ptr<Material> material_;
  BoundingBox bounding_box_;
};

#endif