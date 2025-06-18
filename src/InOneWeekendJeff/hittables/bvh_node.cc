#include "bvh_node.h"

#include <algorithm>

#include "InOneWeekendJeff/random.h"

BvhNode::BvhNode(HittableList& list)
    : BvhNode(list.hittables(), 0, list.hittables().size()) {}

BvhNode::~BvhNode() {
  payload_ = nullptr;
}

BvhNode::BvhNode(std::vector<std::unique_ptr<Hittable>>& hittables,
                 int start,
                 int end) {
  // Construction overview: Use divide and conquer to construct a binary tree
  // of bounding boxes each which partions the space in two (not necessarily
  // half). The spaces will be divided by one randomly selected axis of three.
  int length = end - start;
  if (length <= 0) {
    return;
  } else if (length == 1) {
    payload_ = hittables[start].get();
  } else {
    // Sorts by a randomly chosen axis
    int sort_by_axis = Random::random_int(0, 2);
    std::sort(hittables.begin() + start, hittables.begin() + end,
              [&](const std::unique_ptr<Hittable>& lhs,
                  const std::unique_ptr<Hittable>& rhs) {
                if (sort_by_axis == 0) {
                  return lhs->bounding_box().x_interval().min() <
                         rhs->bounding_box().x_interval().min();
                } else if (sort_by_axis == 1) {
                  return lhs->bounding_box().y_interval().min() <
                         rhs->bounding_box().y_interval().min();
                } else {
                  return lhs->bounding_box().z_interval().min() <
                         rhs->bounding_box().z_interval().min();
                }
              });
    int mid = start + (length / 2);
    // Recurse on the two left and right partitions.
    left_ = std::make_unique<BvhNode>(hittables, start, mid);
    right_ = std::make_unique<BvhNode>(hittables, mid, end);
  }
}

bool BvhNode::hit(const Ray& incident_ray,
                  Interval ival,
                  Hittable::HitResult& result) const {
  if (!bounding_box_.hit(incident_ray, ival)) {
    return false;
  }

  bool hit_left = left_->hit(incident_ray, ival, result);
  bool hit_right = right_->hit(
      incident_ray, Interval(ival.min(), hit_left ? result.t : ival.max()),
      result);

  return hit_left or hit_right;
}

BoundingBox BvhNode::bounding_box() {
  return bounding_box_;
}
