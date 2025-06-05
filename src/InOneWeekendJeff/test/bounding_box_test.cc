#include "InOneWeekendJeff/bounding_box.h"
#include "InOneWeekendJeff/test/test_base.h"

#include <cassert>
#include <cmath>
#include "InOneWeekendJeff/interval.h"

class BoundingBoxTest : public TestBase {
 public:
  void RunTest() override {
    BoundingBox empty_bb;
    assert(empty_bb.x_interval() == Interval::empty);
    assert(empty_bb.y_interval() == Interval::empty);
    assert(empty_bb.z_interval() == Interval::empty);

    Point3 a = CreateRandomPoint();
    Point3 b = CreateRandomPoint();
    BoundingBox bb = BoundingBox::CreateBoundingBoxFromTwoPoints(a, b);
    assert(bb.x_interval() ==
           Interval(std::min(a.x(), b.x()), std::max(a.x(), b.x())));
    assert(bb.y_interval() ==
           Interval(std::min(a.y(), b.y()), std::max(a.y(), b.y())));
    assert(bb.z_interval() ==
           Interval(std::min(a.z(), b.z()), std::max(a.z(), b.z())));
  }
};