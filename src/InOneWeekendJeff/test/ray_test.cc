#include "InOneWeekendJeff/geometry/ray.h"
#include "InOneWeekendJeff/random.h"
#include "test_base.h"

#include <cassert>

class RayTest : public TestBase {
 public:
  void RunTest() override {
    Point3 origin = CreateRandomPoint();
    Vec3 direction = CreateRandomVec();
    Ray ray(origin, direction);

    assert(ray.time() == 0);

    double t = 0.0;
    assert(ray.at(t) == ray.origin());

    t = Random::random_real();
    assert(ray.at(t) == Point3(direction * t) + origin);

    ray = Ray(origin, direction, 1.0);
    assert(ray.time() == 1.0);
  }
};