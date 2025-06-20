#ifndef BVH_NODE_H
#define BVH_NODE_H

#include <memory>
#include <vector>

#include "InOneWeekendJeff/bounding_box.h"
#include "InOneWeekendJeff/hittables/hittable.h"
#include "InOneWeekendJeff/interval.h"
#include "InOneWeekendJeff/ray.h"

class BvhNodeTest;

class BvhNode : public Hittable {
 public:
  BvhNode();

  // Rule of 5
  BvhNode(const BvhNode&) = default;
  BvhNode(BvhNode&&) = default;
  BvhNode& operator=(const BvhNode&) = default;
  BvhNode& operator=(BvhNode&&) = default;
  ~BvhNode();

  bool hit(const Ray& incident_ray,
           Interval ival,
           Hittable::HitResult& result) const override;

  BoundingBox bounding_box() override;

  // Recursively constructs a Bvh tree given a list of hittables.
  static BvhNode CreateBvhTree(
      std::vector<std::unique_ptr<Hittable>>& hittables);

 private:
  friend class BvhNodeTest;

  // Start and end represent half-open intervals (right-exclusive)
  static BvhNode CreateBvhTreeImpl(
      std::vector<std::unique_ptr<Hittable>>& hittables,
      int start,
      int end);

  BoundingBox bounding_box_;
  // Only leaf nodes will point to an actual hittable.
  Hittable* payload_ = nullptr;
  std::unique_ptr<BvhNode> left_;
  std::unique_ptr<BvhNode> right_;
};

#endif