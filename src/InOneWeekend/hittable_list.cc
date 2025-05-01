#include "hittable_list.h"
#include "hittable.h"

#include <cmath>

HittableList::HittableList() {}

HittableList::~HittableList() = default;

void HittableList::clearAll() {
  hittables_.clear();
}

void HittableList::add(std::weak_ptr<Hittable> h) {
  hittables_.push_back(h);
}

bool HittableList::hit(const Ray& ray,
                       double ray_tmin,
                       double ray_tmax,
                       Hittable::HitResult& result) const {
  bool hit_anything = false;
  double closest_so_far = ray_tmax;

  for (const auto& hittable : hittables_) {
    if (hittable.expired()) {
      continue;
    }
    HitResult temp_result;
    if (hittable.lock()->hit(ray, ray_tmin, closest_so_far, temp_result)) {
      hit_anything = true;
      closest_so_far = std::fmin(closest_so_far, temp_result.t);
      result = temp_result;
    }
  }
  return hit_anything;
}
