#include "InOneWeekend/materials/metal.h"
#include "InOneWeekend/sphere.h"
#include "InOneWeekend/test/test_base.h"

class MetalTest : public TestBase {
 public:
  void run_test() override {
    Point3 sphere_center(0, 0, -1);
    Sphere sphere(sphere_center, 0.5);

    Metal metal(Color(1, 1, 1));

    Point3 light_origin(0, 0, 0);
    Vec3 light_direction(sphere_center);

    // Ray incident_ray(light_origin, );
    // metal.scatter()
  }
};