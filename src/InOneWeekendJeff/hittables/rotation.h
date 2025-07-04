#ifndef ROTATION_H
#define ROTATION_H

#include <memory>

#include "InOneWeekendJeff/hittables/hittable.h"

class Rotation : public Hittable {
 public:
  Rotation(std::unique_ptr<Hittable> hittable, double degrees_of_rotation);

  bool Hit(const Ray& incident_ray,
           Interval ival,
           Hittable::HitResult& result) const override;

  BoundingBox bounding_box() override;

 private:
  std::unique_ptr<Hittable> hittable_;
  BoundingBox bounding_box_;
  double degrees_of_rotation_;
};

#endif
