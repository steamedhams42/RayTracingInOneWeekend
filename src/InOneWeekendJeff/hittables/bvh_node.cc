#include "bvh_node.h"

#include <algorithm>

#include "InOneWeekendJeff/random.h"

BvhNode::BvhNode() {}

BvhNode::~BvhNode() {
  hittable_ = nullptr;
}

// static
BvhNode BvhNode::CreateBvhTree(
    std::vector<std::unique_ptr<Hittable>>& hittables) {
  return CreateBvhTreeImpl(hittables, 0, hittables.size());
}

// static
BvhNode BvhNode::CreateBvhTreeImpl(
    std::vector<std::unique_ptr<Hittable>>& hittables,
    int start,
    int end) {
  // Construction overview: Use divide and conquer to construct a binary tree
  // of bounding boxes each which partions the space in two (not necessarily
  // half). The spaces will be divided by one randomly selected axis of three.
  int length = end - start;
  BvhNode result;
  if (length <= 0) {
    return result;
  } else if (length == 1) {
    result.hittable_ = hittables[start].get();
    result.bounding_box_ = result.hittable_->bounding_box();
    return result;
  } else {
    // Sorts by a longest axis of the bounding box that contains the hittables.
    result.bounding_box_ = BoundingBox::empty();
    for (int i = start; i < end; i++) {
      result.bounding_box_ =
          BoundingBox(result.bounding_box_, hittables[i]->bounding_box());
    }
    int sort_axis = result.bounding_box().longest_axis();
    std::sort(hittables.begin() + start, hittables.begin() + end,
              [&](const std::unique_ptr<Hittable>& lhs,
                  const std::unique_ptr<Hittable>& rhs) {
                if (sort_axis == 0) {
                  return lhs->bounding_box().x_interval().min() <
                         rhs->bounding_box().x_interval().min();
                } else if (sort_axis == 1) {
                  return lhs->bounding_box().y_interval().min() <
                         rhs->bounding_box().y_interval().min();
                } else {
                  return lhs->bounding_box().z_interval().min() <
                         rhs->bounding_box().z_interval().min();
                }
              });
    int mid = start + (length / 2);
    // Recurse on the two left and right partitions.
    result.left_ =
        std::make_unique<BvhNode>(CreateBvhTreeImpl(hittables, start, mid));
    result.right_ =
        std::make_unique<BvhNode>(CreateBvhTreeImpl(hittables, mid, end));
    return result;
  }
}

bool BvhNode::hit(const Ray& incident_ray,
                  Interval ival,
                  Hittable::HitResult& result) const {
  if (!bounding_box_.hit(incident_ray, ival)) {
    return false;
  }
  // Do not recurse on leaf nodes. Leaf nodes contain the hittable objects.
  if (!left_ and !right_) {
    return hittable_->hit(incident_ray, ival, result);
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
