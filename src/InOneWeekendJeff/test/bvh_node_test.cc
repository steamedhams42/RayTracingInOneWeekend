#include "test_base.h"

#include <cassert>
#include <memory>
#include <vector>

#include "InOneWeekendJeff/hittables/bvh_node.h"
#include "InOneWeekendJeff/hittables/hittable_list.h"
#include "InOneWeekendJeff/hittables/sphere.h"

class BvhNodeTest : public TestBase {
 public:
  void RunTest() override {
    HittableList hittable_list;
    hittable_list.add(std::make_unique<Sphere>(Point3(0, 0, 0), 1));
    hittable_list.add(std::make_unique<Sphere>(Point3(1, 1, 1), 1));
    hittable_list.add(std::make_unique<Sphere>(Point3(2, 2, 2), 1));
    hittable_list.add(std::make_unique<Sphere>(Point3(3, 3, 3), 1));
    auto bvh = BvhNode::CreateBvhTree(hittable_list.hittables());

    bvh.bounding_box();
  }
};