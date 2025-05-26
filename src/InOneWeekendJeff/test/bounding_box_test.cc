#include "InOneWeekendJeff/bounding_box.h"
#include "InOneWeekendJeff/test/test_base.h"

class BoundingBoxTest : public TestBase {
 public:
  void RunTest() override {
    Point3 a = CreateRandomPoint();
    Point3 b = CreateRandomPoint();
    BoundingBox bb = BoundingBox::CreateBoundingBoxFromTwoPoints(a, b);
  }
};