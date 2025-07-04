#ifndef CONSTANT_MEDIUM_H
#define CONSTANT_MEDIUM_H

#include <memory>

#include "InOneWeekendJeff/bounding_box.h"
#include "InOneWeekendJeff/color.h"
#include "InOneWeekendJeff/hittables/hittable.h"
#include "InOneWeekendJeff/textures/texture.h"

class ConstantMedium : public Hittable {
 public:
  ConstantMedium(std::unique_ptr<Hittable> boundary,
                 std::unique_ptr<Texture> texture,
                 double density);

  ConstantMedium(std::unique_ptr<Hittable> boundary,
                 const Color& albedo,
                 double density);

  bool Hit(const Ray& incident_ray,
           Interval ival,
           Hittable::HitResult& result) const override;

  BoundingBox bounding_box() override;

 private:
  // The  medium must be bounded/enclosed by another hittable e.g. sphere or
  // box.
  std::unique_ptr<Hittable> boundary_;
  // Phase function.
  std::unique_ptr<Material> texture_;
  // How dense the medium is. Higher density, higher occlusion.
  double density_;
};

#endif