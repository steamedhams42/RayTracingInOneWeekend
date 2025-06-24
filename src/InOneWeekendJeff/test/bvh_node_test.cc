#include "test_base.h"

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "InOneWeekendJeff/bounding_box.h"
#include "InOneWeekendJeff/hittables/bvh_node.h"
#include "InOneWeekendJeff/hittables/hittable.h"
#include "InOneWeekendJeff/hittables/hittable_list.h"
#include "InOneWeekendJeff/hittables/sphere.h"
#include "InOneWeekendJeff/interval.h"
#include "InOneWeekendJeff/point3.h"
#include "InOneWeekendJeff/ray.h"

class BvhNodeTest : public TestBase {
 private:
  const double UNIT_LENGTH = 1.0;

 public:
  void RunTest() override {
    HittableList hittable_list;
    Point3 sphere_center(0, 1, 0);
    hittable_list.add(std::make_unique<Sphere>(sphere_center, UNIT_LENGTH));
    auto bvh = BvhNode::CreateBvhTree(hittable_list.hittables());
    assert(bvh.bounding_box() ==
           BoundingBox(Interval(-1, 1), Interval(0, 2), Interval(-1, 1)));

    // Test for hit detection on leaf nodes.
    Point3 ray_origin(0, 0, 10);
    Vec3 ray_direction(sphere_center - ray_origin);
    Ray incident_ray(ray_origin, ray_direction);
    Hittable::HitResult hit_result;
    assert(bvh.hit(incident_ray, Interval(0, 1000), hit_result));

    // Post-order DFS test.
    hittable_list.add(std::make_unique<Sphere>(Point3(-3, 1, 0), UNIT_LENGTH));
    hittable_list.add(std::make_unique<Sphere>(Point3(-2, 1, 0), UNIT_LENGTH));
    hittable_list.add(std::make_unique<Sphere>(Point3(-1, 1, 0), UNIT_LENGTH));
    hittable_list.add(std::make_unique<Sphere>(Point3(1, 1, 0), UNIT_LENGTH));
    hittable_list.add(std::make_unique<Sphere>(Point3(2, 1, 0), UNIT_LENGTH));
    hittable_list.add(std::make_unique<Sphere>(Point3(3, 1, 0), UNIT_LENGTH));
    bvh = BvhNode::CreateBvhTree(hittable_list.hittables());
    assert(bvh.bounding_box() ==
           BoundingBox(Interval(-4, 4), Interval(0, 2), Interval(-1, 1)));

    int iter = 0;
    std::function<void(const BvhNode&)> dfs = [&](const BvhNode& node) {
      if (node.left_)
        dfs(*node.left_);
      if (node.right_)
        dfs(*node.right_);
      if (!node.left_ and !node.right_) {
        // Assert the leaf nodes are in the same as above since they are sorted
        // by longest axis (x-axis).
        assert(node.hittable_ == hittable_list.hittables()[iter++].get());
      }
    };

    dfs(bvh);
  }
};