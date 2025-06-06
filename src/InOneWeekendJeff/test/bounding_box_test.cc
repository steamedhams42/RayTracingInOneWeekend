#include "InOneWeekendJeff/bounding_box.h"
#include "InOneWeekendJeff/test/test_base.h"

#include <cassert>
#include <cmath>
#include "InOneWeekendJeff/constants.h"
#include "InOneWeekendJeff/interval.h"

class BoundingBoxTest : public TestBase {
 private:
  BoundingBox create_unit_bounding_box() {
    return BoundingBox(Interval(0, 1), Interval(0, 1), Interval(0, 1));
  }

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

    BoundingBox unit_bb = create_unit_bounding_box();
    Ray incident_ray(Point3(-1, 0.5, 0.5), Vec3(3, 0, 0));
    assert(unit_bb.hit(incident_ray, Interval(0, constants::INF_DOUBLE)));

    incident_ray = Ray(Point3(-1, 0.5, 0.5), Vec3(-3, 0, 0));
    assert(!unit_bb.hit(incident_ray, Interval(0, constants::INF_DOUBLE)));
  }
};