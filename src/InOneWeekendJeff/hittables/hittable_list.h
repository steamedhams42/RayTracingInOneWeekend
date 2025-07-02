#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>
#include "InOneWeekendJeff/bounding_box.h"
#include "InOneWeekendJeff/geometry/ray.h"
#include "InOneWeekendJeff/hittables/bvh_node.h"
#include "InOneWeekendJeff/hittables/hittable.h"
#include "InOneWeekendJeff/interval.h"

class HittableListTest;

class HittableList : public Hittable {
 public:
  HittableList();
  ~HittableList();

  void clearAll();
  void add(std::unique_ptr<Hittable>);

  bool hit(const Ray& ray,
           Interval i,
           Hittable::HitResult& result) const override;

  BoundingBox bounding_box() override;
  std::vector<std::unique_ptr<Hittable>>& hittables();
  void InitBvhTree();

 private:
  friend class HittableListTest;

  std::vector<std::unique_ptr<Hittable>> hittables_;
  BoundingBox bounding_box_;
  std::unique_ptr<BvhNode> bvh_;
};

#endif