#ifndef BVH_NODE_H
#define BVH_NODE_H

#include <memory>

#include "bounding_box.h"
#include "hittable.h"
#include "hittable_list.h"
#include "interval.h"
#include "ray.h"

class BvhNode : public Hittable {
 public:
  BvhNode(HittableList hittables);

  // Start and end represent half-open intervals (right-exclusive)
  BvhNode(std::vector<std::unique_ptr<Hittable>>& objects, int start, int end);

  bool hit(const Ray& incident_ray,
           Interval ival,
           Hittable::HitResult& result) const override;

  BoundingBox bounding_box() override;

 private:
  BoundingBox bounding_box_;
  // Only leaf nodes will point to an actual hittable.
  Hittable* payload_ = nullptr;
  std::unique_ptr<BvhNode> left_;
  std::unique_ptr<BvhNode> right_;
};

#endif