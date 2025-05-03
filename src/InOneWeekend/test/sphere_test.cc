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
    Hittable::HitResult result;
    Sphere sphere(sphere_center, radius);
    Interval intv(-1, 1);

    assert(!sphere.hit(ray, intv, result));

    // Emit ray externally, towards sphere.
    Hittable::HitResult result2;
    Vec3 direction2(0, 0, 3);
    Ray ray2(origin, direction2);
    assert(sphere.hit(ray2, intv, result2));
    assert(result2.p == Point3(0, 0, 0.5));
    assert(result2.t > 0);
    assert(result2.front_face == true);

    // Emit ray from origin of sphere, internally away from the camera
    Hittable::HitResult result3;
    Vec3 direction3(0, 0, 5);
    Ray ray3(sphere_center, direction3);
    // The ray's acceptable range must be positive otherwise the negative
    // t-value (behind the origin of the sphere) will be chosen.
    assert(sphere.hit(ray3, Interval(0, 1), result3));
    assert(result3.p == Point3(0, 0, 1.5));
    assert(result3.t > 0);
    assert(result3.front_face == false);

    // Emit ray from origin of sphere, internally towards the camera
    Hittable::HitResult result4;
    Vec3 direction4(0, 0, -4);
    Ray ray4(sphere_center, direction4);
    assert(sphere.hit(ray4, Interval(0, 1), result4));
    assert(result4.p == Point3(0, 0, 0.5));
    assert(result4.t > 0);
    assert(result4.front_face == false);

    // Emit a ray from surface of the sphere outwards.
    Hittable::HitResult result5;
    Point3 surface_point = Point3(0, 0, radius);
    Vec3 v5 = Vec3::random_vec3_on_surface(Vec3(surface_point - sphere_center));
    Ray ray5(surface_point, v5);
    assert(!sphere.hit(ray5, Interval(0, 1), result5));
  }
};