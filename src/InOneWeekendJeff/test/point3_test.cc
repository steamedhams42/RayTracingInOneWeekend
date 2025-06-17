#include "InOneWeekendJeff/point3.h"
#include "InOneWeekendJeff/random.h"
#include "InOneWeekendJeff/test/test_base.h"

#include <cassert>
#include <cmath>

class Point3Test : public TestBase {
 public:
  void RunTest() override {
    Point3 zed;
    Point3 v(0, 0, 0);
    assert(zed == v);

    v = CreateRandomPoint();
    assert(v.points_[0] == v.x());
    assert(v.points_[1] == v.y());
    assert(v.points_[2] == v.z());

    // addition
    assert(v == zed + v);
    v += zed;
    assert(v == zed + v);

    // subtraction
    assert(v == v - zed);
    assert(v - v == zed);

    // multiplication
    assert(v * 1 == v);
    assert(v * 0 == zed);
    double x = Random::random_real();
    Point3 before = v;
    v *= x;
    assert(v.x() == before.x() * x);
    assert(v.y() == x * before.y());
    assert(v.z() == x * before.z() * 1);
    v *= 0;
    assert(v == zed);

    // division
    v = CreateRandomPoint();
    x = Random::random_real();
    before = v;
    v /= x;
    assert(v.x() <= before.x() * (1 / x));
    assert(v.y() <= before.y() * (1 / x));
    assert(v.z() <= before.z() * (1 / x));

    assert(v.norm_squared() == (v.x() * v.x() + v.y() * v.y() + v.z() * v.z()));

    assert(v.norm() <= sqrt(v.norm_squared()));
  }
};
