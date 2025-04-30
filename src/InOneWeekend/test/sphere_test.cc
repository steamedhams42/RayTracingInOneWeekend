#include "InOneWeekend/sphere.h"
#include "InOneWeekend/ray.h"
#include "test_base.h"

class SphereTest : public TestBase {
 public:
  SphereTest() = default;
  void run_test() override {
    Point3 origin;
    Vec3 direction;
    Ray ray(origin, direction);

    Point3 sphere_center(0, 0, 1);
    double radius(1);
    Sphere sphere(sphere_center, radius);
  }
};