#include "bvh_node.h"

#include <algorithm>

BvhNode::BvhNode(HittableList list) {}

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
    // std::sort(hittables.begin() + start, hittables.begin() + end,
    //           [&](const Hittable& lhs, const Hittable& rhs) {
    //             // TODO: write a comparator to sort 2 hittables by an axis.
    //             return false;
    //           });
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

  return hit_left || hit_right;
}

BoundingBox BvhNode::bounding_box() {
  return bounding_box_;
}
