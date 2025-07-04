
#include "InOneWeekendJeff/hittables/translation.h"

Translation::Translation(std::unique_ptr<Hittable> hittable, const Vec3& offset)
    : hittable_(std::move(hittable)), translation_offset_(offset) {
  bounding_box_ = hittable_->bounding_box() + translation_offset_;
}

bool Translation::Hit(const Ray& incident_ray,
                      Interval ival,
                      Hittable::HitResult& result) const {
  Ray translated_ray(incident_ray.origin() - translation_offset_,
                     incident_ray.direction());
  if (hittable_->Hit(translated_ray, ival, result)) {
    return false;
  }
  result.incident_point += translation_offset_;
  return true;
}

BoundingBox Translation::bounding_box() {
  return bounding_box_;
}
