#include "InOneWeekend/test/test_base.h"

#include <cassert>

#include "InOneWeekend/constants.h"
#include "InOneWeekend/materials/lambertian.h"
#include "InOneWeekend/sphere.h"
#include "InOneWeekend/test/test_base.h"

class LambertianTest : public TestBase {
 public:
  void run_test() override {
    Point3 sphere_center(0, 0, -1);
    Sphere sphere(sphere_center, 0.5, std::make_unique<Lambertian>());

    Point3 light_origin(0, 0, 0);
    Vec3 light_direction(sphere_center);

    Ray incident_ray(light_origin, sphere_center);
    Hittable::HitResult hit_result;
    Ray scattered_ray;
    Color attenuation;

    // Trace a single ray of light at the center of the metallic sphere
    assert(sphere.hit(incident_ray, Interval(0.001, constants::INF_DOUBLE),
                      hit_result));

    // Assert the hit occurred.
    assert(hit_result.p == Point3(0, 0, -0.5));

    // Scatter the incident ray using the appropriate material (metal).
    hit_result.material->scatter(incident_ray, hit_result, attenuation,
                                 scattered_ray);

    assert(attenuation == Color(0.5, 0.5, 0.5));
    // since lambertian material scatter semi randomly, best I can do is check
    // the direction is correct (reflected away from surface).
    assert(scattered_ray.direction().dot(Vec3(hit_result.p - sphere_center)) >
           0);
  }
};