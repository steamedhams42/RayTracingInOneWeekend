#ifndef BVH_NODE_H
#define BVH_NODE_H

#include <memory>
#include <vector>

#include "InOneWeekendJeff/bounding_box.h"
#include "InOneWeekendJeff/geometry/ray.h"
#include "InOneWeekendJeff/hittables/hittable.h"
#include "InOneWeekendJeff/interval.h"

class BvhNodeTest;

class BvhNode : public Hittable {
 public:
  BvhNode();

  // Rule of 5
  BvhNode(const BvhNode&) = delete;
  BvhNode(BvhNode&&) = default;
  BvhNode& operator=(const BvhNode&) = delete;
  BvhNode& operator=(BvhNode&&) = default;
  ~BvhNode();

  bool Hit(const Ray& incident_ray,
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

  // Represents the minimal bounding box of the union of all nodes.
  BoundingBox bounding_box_;

  // Only leaf nodes will point to an actual hittable.
  Hittable* hittable_ = nullptr;

  std::unique_ptr<BvhNode> left_;
  std::unique_ptr<BvhNode> right_;
};

#endif