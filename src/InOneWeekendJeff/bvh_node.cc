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
  // TODO
  return false;
}

BoundingBox BvhNode::bounding_box() {
  return bounding_box_;
}