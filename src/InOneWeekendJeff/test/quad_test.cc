#include <cassert>
#include <memory>

#include "InOneWeekendJeff/constants.h"
#include "InOneWeekendJeff/hittables/quad.h"
#include "InOneWeekendJeff/materials/lambertian.h"
#include "InOneWeekendJeff/test/test_base.h"
#include "InOneWeekendJeff/vec3.h"

class QuadTest : public TestBase {
 public:
  Quad CreateUnitQuad() {
    return Quad(Point3(0, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0),
                std::make_unique<Lambertian>());
  }

  void RunTest() override {
    auto quad = CreateUnitQuad();
    for (double i = -1; i <= 2; i += 0.1) {
      for (double j = -1; j <= 2; j += 0.1) {
        Point3 ray_origin(0, 0, 9);
        Point3 target(i, j, 0);
        Vec3 ray_direction(Vec3(target - ray_origin));
        Ray incident_ray(ray_origin, ray_direction);
        Hittable::HitResult result;
        if (Interval(0, 1).contains(i) and Interval(0, 1).contains(j)) {
          assert(
              quad.hit(incident_ray, constants::interval::UNIVERSAL, result));
        } else {
          assert(
              !quad.hit(incident_ray, constants::interval::UNIVERSAL, result));
        }
      }
    }
  }
};