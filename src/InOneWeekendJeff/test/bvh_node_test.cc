#include "test_base.h"

#include <memory>
#include <vector>

#include "InOneWeekendJeff/hittables/bvh_node.h"

class BvhNodeTest : public TestBase {
 public:
  void RunTest() override {
    std::vector<std::unique_ptr<Hittable>> hittables;
    BvhNode bvh(hittables, 0, hittables.size());
  }
};