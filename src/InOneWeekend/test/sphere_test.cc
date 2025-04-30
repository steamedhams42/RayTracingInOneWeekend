#include "InOneWeekend/sphere.h"
#include <cassert>
#include "InOneWeekend/ray.h"
#include "test_base.h"

class SphereTest : public TestBase {
 public:
  SphereTest() = default;

  void run_test() override {
    // Camera
    Point3 origin(0, 0, 0);

    Point3 sphere_center(0, 0, 1);
    double radius(0.5);

    // Emit ray that misses sphere.
    Vec3 direction(0, 2, 3);
    Ray ray(origin, direction);
    Sphere::HitResult result;
    Sphere sphere(sphere_center, radius);

    assert(!sphere.hit(ray, -1, 1, result));

    // Emit ray directly towards sphere.
    Vec3 direction2(0, 0, 3);
    Ray ray2(origin, direction2);
    assert(sphere.hit(ray2, -1, 1, result));
    assert(result.p == Point3(0, 0, 0.5));
    assert(result.t > 0);

    // Emit ray from origin of sphere, towards camera
    Vec3 direction3(0, 0, 1);
    Ray ray3(sphere_center, direction3);
    assert(sphere.hit(ray3, -1, 1, result));
    assert(result.p == Point3(0, 0, 0.5));
    assert(result.t < 0);
  }
};