#ifndef BOX_H
#define BOX_

#include <memory>

#include "InOneWeekendJeff/bounding_box.h"
#include "InOneWeekendJeff/hittables/hittable.h"
#include "InOneWeekendJeff/hittables/quad.h"

class Ray;
class Point3;
class Material;
class Interval;

// Constructs a box using two points (front-bot-left, back-top-right).
// Encapsulates 6 quads.
class Box : public Hittable {
 public:
  Box(const Point3& front_bottom_left,
      const Point3& back_top_right,
      std::shared_ptr<Material> material);

  bool Hit(const Ray& incident_ray,
           Interval ival,
           Hittable::HitResult& result) const override;

  BoundingBox bounding_box() override;

 private:
  std::unique_ptr<Quad> left_;
  std::unique_ptr<Quad> right_;
  std::unique_ptr<Quad> top_;
  std::unique_ptr<Quad> bottom_;
  std::unique_ptr<Quad> front_;
  std::unique_ptr<Quad> back_;

  BoundingBox bounding_box_;
};

#endif