#ifndef TRANSLATION_H
#define TRANSLATION_H

#include <memory>

#include "InOneWeekendJeff/geometry/vec3.h"
#include "InOneWeekendJeff/hittables/hittable.h"

class Translation : public Hittable {
 public:
  Translation(std::shared_ptr<Hittable> hittable, const Vec3& offset);

  bool Hit(const Ray& incident_ray,
           Interval ival,
           Hittable::HitResult& result) const override;

  BoundingBox bounding_box() override;

 private:
  std::shared_ptr<Hittable> hittable_;
  Vec3 translation_offset_;
  BoundingBox bounding_box_;
};

#endif