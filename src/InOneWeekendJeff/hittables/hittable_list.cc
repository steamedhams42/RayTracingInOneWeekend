#include "InOneWeekendJeff/hittables/hittable_list.h"
#include "InOneWeekendJeff/hittables/hittable.h"

#include <cassert>
#include <cmath>

HittableList::HittableList() {}

HittableList::~HittableList() = default;

void HittableList::clearAll() {
  hittables_.clear();
}

void HittableList::add(std::unique_ptr<Hittable> hittable) {
  bounding_box_ = BoundingBox(bounding_box_, hittable->bounding_box());
  hittables_.push_back(std::move(hittable));
}

void HittableList::add(std::vector<std::unique_ptr<Hittable>>& hittables) {
  for (auto& hittable : hittables) {
    add(std::move(hittable));
  }
}

void HittableList::InitBvhTree() {
  bvh_ = std::make_unique<BvhNode>(BvhNode::CreateBvhTree(this->hittables_));
}

bool HittableList::Hit(const Ray& ray,
                       Interval interval,
                       Hittable::HitResult& result) const {
  bool hit_anything = false;

  HitResult temp_result;
  if (!bvh_) {
    std::cout
        << "CHECK FAILED: Did you forget to call HittableList::InitBvhTree()?"
        << std::endl;
    assert(bvh_);
  }
  if (bvh_->Hit(ray, interval, temp_result)) {
    hit_anything = true;
    // Reset max t-value so only the foreground-most hittable is rendered
    // (unnessary to check beyond that).
    interval = Interval(interval.min(), temp_result.t);
    result = temp_result;
  }
  return hit_anything;
}

BoundingBox HittableList::bounding_box() {
  return bounding_box_;
}

std::vector<std::unique_ptr<Hittable>>& HittableList::hittables() {
  return hittables_;
}
