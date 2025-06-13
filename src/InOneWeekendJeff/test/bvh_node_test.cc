#include "test_base.h"

#include <cassert>
#include <memory>
#include <vector>

#include "InOneWeekendJeff/hittables/bvh_node.h"
#include "InOneWeekendJeff/hittables/sphere.h"

class BvhNodeTest : public TestBase {
 public:
  void RunTest() override {
    std::vector<std::unique_ptr<Hittable>> hittables;
    hittables.push_back(std::make_unique<Sphere>(Point3(0, 0, 0), 1));
    hittables.push_back(std::make_unique<Sphere>(Point3(1, 1, 1), 1));
    BvhNode bvh(hittables, 0, hittables.size());
    bvh.bounding_box();
  }
};