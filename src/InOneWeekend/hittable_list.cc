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
                       Interval intvl,
                       Hittable::HitResult& result) const {
  bool hit_anything = false;

  for (const auto& hittable : hittables_) {
    if (hittable.expired()) {
      continue;
    }
    HitResult temp_result;
    if (hittable.lock()->hit(ray, intvl, temp_result)) {
      hit_anything = true;
      // Reset max t value so only the foreground-most hittable is rendered.
      intvl = std::move(Interval(intvl.min(), temp_result.t));
      result = temp_result;
    }
  }
  return hit_anything;
}
