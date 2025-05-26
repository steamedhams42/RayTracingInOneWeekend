#include "InOneWeekendJeff/bounding_box.h"
#include "InOneWeekendJeff/test/test_base.h"

class BoundingBoxTest : public TestBase {
 public:
  void RunTest() override {
    BoundingBox bb = BoundingBox::CreateBoundingBoxFromTwoPoints(
        CreateRandomPoint(), CreateRandomPoint());
  }
};