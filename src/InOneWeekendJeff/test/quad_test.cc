#include <cassert>
#include <memory>

#include "InOneWeekendJeff/constants.h"
#include "InOneWeekendJeff/geometry/vec3.h"
#include "InOneWeekendJeff/hittables/quad.h"
#include "InOneWeekendJeff/materials/lambertian.h"
#include "InOneWeekendJeff/test/test_base.h"

class QuadTest : public TestBase {
 public:
  Quad CreateUnitQuad() {
    return Quad(Point3(0, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0),
                std::make_shared<Lambertian>());
  }

  void test_one_quad() {
    // Tests a "ceiling" faced quad.
    // Think top ceiling of a cornell box.
    Quad quad(Point3(-2, 3, 1), Vec3(4, 0, 0), Vec3(0, 0, 4));
    for (double x = -3; x <= 3; x += 0.1) {
      for (double z = 6; z >= 0; z -= 0.1) {
        Point3 ray_origin(0, 0, 9);
        Point3 target(x, 3, z);
        Vec3 ray_direction(Vec3(target - ray_origin));
        Ray incident_ray(ray_origin, ray_direction);
        Hittable::HitResult result;
        if (Interval(-2, 2).contains(x) and Interval(1, 5).contains(z)) {
          assert(
              quad.hit(incident_ray, constants::interval::UNIVERSAL, result));
        } else {
          assert(
              !quad.hit(incident_ray, constants::interval::UNIVERSAL, result));
        }
      }
    }
  }

  void test_quads_from_main() {
    // Left quad
    Quad(Point3(-3, -2, 5), Vec3(0, 0, -4), Vec3(0, 4, 0));
    // Center quad
    Quad(Point3(-2, -2, 0), Vec3(4, 0, 0), Vec3(0, 4, 0));
    // Right quad
    Quad(Point3(3, -2, 1), Vec3(0, 0, 4), Vec3(0, 4, 0));
    // Top quad
    Quad(Point3(-2, 3, 1), Vec3(4, 0, 0), Vec3(0, 0, 4));
    // Bot quad
    Quad(Point3(-2, -3, 5), Vec3(4, 0, 0), Vec3(0, 0, -4));

    // Test the center quad
    for (double x = -2; x <= 2; x += 0.1) {
      for (double y = -2; y <= 2; y += 0.1) {
        Point3 ray_origin(0, 0, 9);
        Point3 target(x, y, 100);
        Vec3 ray_direction(Vec3(target - ray_origin));
        Ray incident_ray(ray_origin, ray_direction);
        Hittable::HitResult result;
      }
    }
  }

  void RunTest() override {
    test_one_quad();
    test_quads_from_main();
  }
};