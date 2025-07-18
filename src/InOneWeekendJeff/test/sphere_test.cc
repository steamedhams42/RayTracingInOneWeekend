#include <cassert>

#include "InOneWeekendJeff/geometry/ray.h"
#include "InOneWeekendJeff/hittables/sphere.h"
#include "InOneWeekendJeff/materials/lambertian.h"
#include "test_base.h"

class SphereTest : public TestBase {
 public:
  SphereTest() = default;

  void test_default_sphere_is_static() {
    Point3 sphere_center(0, 0, 1);
    double radius(0.5);
    Sphere sphere(sphere_center, radius);

    assert(sphere.center_.origin() == sphere_center);
    assert(sphere.center_.direction() == Vec3(0, 0, 0));
  }

  void test_sphere_is_moving_up() {
    Point3 sphere_center(0, 0, 1);
    Point3 sphere_terminal(0, 1, 1);
    double radius(0.1);
    Sphere sphere(sphere_center, sphere_terminal, radius);

    // Cast a ray at the sphere for each 0.1 time tick
    Point3 origin(0, 0, 0);
    Vec3 direction(0, 0, 1);
    for (double time = 0; time <= 1; time += 0.1) {
      Ray ray(origin, direction, time);
      Hittable::HitResult result;
      Interval intv(-1, 1);
      if (time >= 0.1) {
        assert(!sphere.Hit(ray, intv, result));
      } else {
        assert(sphere.Hit(ray, intv, result));
      }
    }

    // Fire a ray at sphere's center as it moves up.
    for (double time = 0; time <= 1; time += 0.1) {
      Ray ray(origin, Vec3(sphere.center_.at(time) - origin), time);
      Hittable::HitResult result;
      Interval intv(-1, 1);
      assert(sphere.Hit(ray, intv, result));
    }
  }

  void RunTest() override {
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

    assert(!sphere.Hit(ray, intv, result));

    // Emit ray externally, towards sphere.
    Hittable::HitResult result2;
    Vec3 direction2(0, 0, 3);
    Ray ray2(origin, direction2);
    assert(sphere.Hit(ray2, intv, result2));
    assert(result2.incident_point == Point3(0, 0, 0.5));
    assert(result2.t > 0);
    assert(result2.front_face == true);

    // Emit ray from origin of sphere, internally away from the camera
    Hittable::HitResult result3;
    Vec3 direction3(0, 0, 5);
    Ray ray3(sphere_center, direction3);
    // The ray's acceptable range must be positive otherwise the negative
    // t-value (behind the origin of the sphere) will be chosen.
    assert(sphere.Hit(ray3, Interval(0, 1), result3));
    assert(result3.incident_point == Point3(0, 0, 1.5));
    assert(result3.t > 0);
    assert(result3.front_face == false);

    // Emit ray from origin of sphere, internally towards the camera
    Hittable::HitResult result4;
    Vec3 direction4(0, 0, -4);
    Ray ray4(sphere_center, direction4);
    assert(sphere.Hit(ray4, Interval(0, 1), result4));
    assert(result4.incident_point == Point3(0, 0, 0.5));
    assert(result4.t > 0);
    assert(result4.front_face == false);

    // Emit a ray from surface of the sphere outwards.
    Hittable::HitResult result5;
    Point3 surface_point = Point3(0, 0, radius);
    Vec3 v5 = Vec3::random_vec3_on_surface(Vec3(surface_point - sphere_center));
    Ray ray5(surface_point, v5);
    assert(!sphere.Hit(ray5, Interval(0, 1), result5));

    test_default_sphere_is_static();
    test_sphere_is_moving_up();
  }
};