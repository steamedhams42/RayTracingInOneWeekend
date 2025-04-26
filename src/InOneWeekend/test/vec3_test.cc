#include "InOneWeekend/vec3.h"

#include <cassert>

#include "InOneWeekend/test/test_base.h"

class Vec3Test : public TestBase {
 private:
  Vec3 createVec() {
    double a = 0, b = 0, c = 0;
    a = random_real();
    b = random_real();
    c = random_real();
    return Vec3(a, b, c);
  }

 public:
  void run_test() override {
    Vec3 zed;
    Vec3 v(0, 0, 0);
    assert(zed == v);

    v = createVec();
    assert(v.points_[0] == v.x());
    assert(v.points_[1] == v.y());
    assert(v.points_[2] == v.z());

    // addition
    assert(v == zed + v);

    // subtraction
    assert(v == v - zed);
    assert(v - v == zed);

    // multiplication
    assert(v * 1 == v);
    assert(v * 0 == zed);
    double x = random_real();
    Vec3 before = v;
    v *= x;
    assert(v.x() == before.x() * x);
    assert(v.y() == x * before.y());
    assert(v.z() == x * before.z() * 1);
    v *= 0;
    assert(v == zed);

    // division
    v = createVec();
    x = random_real();
    before = v;
    v /= x;
    assert(v.x() <= before.x() * (1 / x));
    assert(v.y() <= before.y() * (1 / x));
    assert(v.z() <= before.z() * (1 / x));

    assert(v.norm_squared() == (v.x() * v.x() + v.y() * v.y() + v.z() * v.z()));

    assert(v.norm() == sqrt(v.norm_squared()));
  }
};