#include "InOneWeekend/ray.h"
#include "InOneWeekend/random.h"
#include "test_base.h"

#include <cassert>

class RayTest : public TestBase {
 public:
  void run_test() override {
    Point3 origin = createPoint();
    Vec3 direction = createVec();
    Ray ray(origin, direction);

    double t = 0.0;
    assert(ray.at(t) == ray.origin());

    t = RandomNumber::random_real();
    assert(ray.at(t) == Point3(direction * t) + origin);
  }
};