#include "InOneWeekend/vec3.h"
#include "InOneWeekend/random.h"

#include <cassert>
#include <vector>

#include "InOneWeekend/test/test_base.h"

class Vec3Test : public TestBase {
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
    RandomNumber rand;
    assert(v * 1 == v);
    assert(v * 0 == zed);
    double x = rand.random_real();
    Vec3 before = v;
    v *= x;
    assert(v.x() == before.x() * x);
    assert(v.y() == x * before.y());
    assert(v.z() == x * before.z() * 1);
    v *= 0;
    assert(v == zed);

    // division
    v = createVec();
    x = rand.random_real();
    before = v;
    v /= x;
    assert(v.x() <= before.x() * (1 / x));
    assert(v.y() <= before.y() * (1 / x));
    assert(v.z() <= before.z() * (1 / x));

    // dot product
    v = createVec();
    assert(v.dot(v) == v.norm_squared());

    // cross product
    std::vector<Vec3> xs = {Vec3(1, 0, 0), Vec3(-1, 0, 0)};
    std::vector<Vec3> ys = {Vec3(0, 1, 0), Vec3(0, -1, 0)};
    std::vector<Vec3> zs = {Vec3(0, 0, 1), Vec3(0, 0, -1)};

    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        assert(xs[i].cross(ys[j]) == zs[(i + j) % 2]);
        assert(ys[i].cross(xs[j]) == zs[(i + j + 1) % 2]);
      }
    }

    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        assert(ys[i].cross(zs[j]) == xs[(i + j) % 2]);
        assert(zs[i].cross(ys[j]) == xs[(i + j + 1) % 2]);
      }
    }

    for (int i = 0; i < 2; i++) {
      for (int j = 0; j < 2; j++) {
        assert(zs[i].cross(xs[j]) == ys[(i + j) % 2]);
        assert(xs[i].cross(zs[j]) == ys[(i + j + 1) % 2]);
      }
    }

    // unit vector
    v = createVec();
    Vec3 unit = v.unit();
    double norm = v.norm();
    assert(unit.x() == (v / norm).x());
    assert(unit.y() == (v / norm).y());
    assert(unit.z() == (v / norm).z());
    ASSERT(unit.norm() <= 1 + EPS, "unit norm greater than 1 + EPS");
    ASSERT(unit.norm() >= 1 - EPS, "unit norm less than 1 - EPS");
  }
};