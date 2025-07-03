#include "test_base.h"

#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

#include "InOneWeekendJeff/bounding_box.h"
#include "InOneWeekendJeff/constants.h"
#include "InOneWeekendJeff/geometry/point3.h"
#include "InOneWeekendJeff/geometry/ray.h"
#include "InOneWeekendJeff/hittables/bvh_node.h"
#include "InOneWeekendJeff/hittables/hittable.h"
#include "InOneWeekendJeff/hittables/hittable_list.h"
#include "InOneWeekendJeff/hittables/quad.h"
#include "InOneWeekendJeff/hittables/sphere.h"
#include "InOneWeekendJeff/interval.h"

class BvhNodeTest : public TestBase {
 private:
  const double UNIT_LENGTH = 1.0;

 public:
  void test_list_of_spheres() {
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
    assert(bvh.Hit(incident_ray, Interval(0, 1000), hit_result));

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

  void test_list_of_quads() {
    HittableList hittable_list;
    Point3 quad_bottom_left_corner(0, 0, 0);
    hittable_list.add(std::make_unique<Quad>(quad_bottom_left_corner,
                                             Vec3(1, 0, 0), Vec3(0, 1, 0)));
    auto bvh = BvhNode::CreateBvhTree(hittable_list.hittables());
    assert(bvh.bounding_box() ==
           BoundingBox(Interval(0, 1), Interval(0, 1), Interval(0, 0)));

    // Test for hit detection on leaf nodes.
    for (double i = -1; i <= 2; i += 0.1) {
      for (double j = -1; j <= 2; j += 0.1) {
        Point3 ray_origin(0, 0, 9);
        Point3 target(i, j, 0);
        Vec3 ray_direction(Vec3(target - ray_origin));
        Ray incident_ray(ray_origin, ray_direction);
        Hittable::HitResult result;
        if (Interval(0, 1).contains(i) and Interval(0, 1).contains(j)) {
          assert(bvh.Hit(incident_ray, constants::interval::UNIVERSAL, result));
        } else {
          assert(
              !bvh.Hit(incident_ray, constants::interval::UNIVERSAL, result));
        }
      }
    }

    // Post-order DFS test.
    hittable_list.add(
        std::make_unique<Quad>(Point3(-3, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0)));
    hittable_list.add(
        std::make_unique<Quad>(Point3(-2, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0)));
    hittable_list.add(
        std::make_unique<Quad>(Point3(-1, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0)));
    hittable_list.add(
        std::make_unique<Quad>(Point3(1, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0)));
    hittable_list.add(
        std::make_unique<Quad>(Point3(2, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0)));
    hittable_list.add(
        std::make_unique<Quad>(Point3(3, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0)));
    bvh = BvhNode::CreateBvhTree(hittable_list.hittables());
    assert(bvh.bounding_box() ==
           BoundingBox(Interval(-3, 4), Interval(0, 1), Interval(0, 0)));

    int iter = 0;
    std::function<void(const BvhNode&)> dfs = [&](const BvhNode& node) {
      if (node.left_)
        dfs(*node.left_);
      if (node.right_)
        dfs(*node.right_);
      if (!node.left_ and !node.right_) {
        // Assert the leaf nodes are in the same as above since they are
        // sorted  by longest axis (x-axis).
        assert(node.hittable_ == hittable_list.hittables()[iter++].get());
      }
    };

    dfs(bvh);
  }

  void RunTest() override {
    test_list_of_spheres();
    test_list_of_quads();
  }
};