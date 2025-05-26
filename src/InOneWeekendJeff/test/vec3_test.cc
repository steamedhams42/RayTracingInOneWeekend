#include "InOneWeekendJeff/vec3.h"
#include "InOneWeekendJeff/constants.h"
#include "InOneWeekendJeff/interval.h"
#include "InOneWeekendJeff/random.h"
#include "InOneWeekendJeff/test/test_base.h"

#include <cassert>
#include <vector>

class Vec3Test : public TestBase {
 public:
  void RunTest() override {
    Vec3 zed;
    Vec3 v(0, 0, 0);
    assert(zed == v);

    v = CreateRandomVec();
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
    double x = Random::random_real();
    Vec3 before = v;
    v *= x;
    assert(v.x() == before.x() * x);
    assert(v.y() == x * before.y());
    assert(v.z() == x * before.z() * 1);
    v *= 0;
    assert(v == zed);

    // division
    v = CreateRandomVec();
    x = Random::random_real();
    before = v;
    v /= x;
    assert(v.x() <= before.x() * (1 / x));
    assert(v.y() <= before.y() * (1 / x));
    assert(v.z() <= before.z() * (1 / x));

    // dot product
    v = CreateRandomVec();
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
    v = CreateRandomVec();
    Vec3 unit = v.unit();
    double norm = v.norm();
    assert(unit.x() == (v / norm).x());
    assert(unit.y() == (v / norm).y());
    assert(unit.z() == (v / norm).z());
    ASSERT(unit.norm() <= 1 + constants::EPS_ERROR,
           "unit norm greater than 1 + constants::EPS_ERROR");
    ASSERT(unit.norm() >= 1 - constants::EPS_ERROR,
           "unit norm less than 1 - constants::EPS_ERROR");

    for (int i = 0; i < 100; i++) {
      double bound = 100;
      Vec3 v = Vec3::random_vec3(-bound, bound);
      Interval intv(-bound, bound);
      assert(intv.contains(v.x()));
      assert(intv.contains(v.y()));
      assert(intv.contains(v.z()));
    }

    for (int i = 0; i < 100; i++) {
      Vec3 v = Vec3::random_unit_vec3();
      Interval intv(-1, 1);
      assert(intv.contains(v.x()));
      assert(intv.contains(v.y()));
      assert(intv.contains(v.z()));

      double norm = v.norm();

      ASSERT(norm <= 1 + constants::EPS_ERROR,
             "unit norm greater than 1 + constants::EPS_ERROR");
      ASSERT(norm >= 1 - constants::EPS_ERROR,
             "unit norm less than 1 - constants::EPS_ERROR");
    }
  }
};