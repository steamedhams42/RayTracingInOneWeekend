#include "bvh_node.h"

BvhNode::BvhNode(HittableList list) {}

BvhNode::BvhNode(std::vector<std::unique_ptr<Hittable>>& hittables,
                 int start,
                 int end) {
  // TODO
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
