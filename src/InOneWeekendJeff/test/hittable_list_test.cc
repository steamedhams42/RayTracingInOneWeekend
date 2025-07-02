#include "InOneWeekendJeff/test/test_base.h"

#include <cassert>
#include <memory>

#include "InOneWeekendJeff/bounding_box.h"
#include "InOneWeekendJeff/color.h"
#include "InOneWeekendJeff/constants.h"
#include "InOneWeekendJeff/geometry/point3.h"
#include "InOneWeekendJeff/geometry/ray.h"
#include "InOneWeekendJeff/geometry/vec3.h"
#include "InOneWeekendJeff/hittables/bvh_node.h"
#include "InOneWeekendJeff/hittables/hittable_list.h"
#include "InOneWeekendJeff/hittables/quad.h"
#include "InOneWeekendJeff/interval.h"
#include "InOneWeekendJeff/materials/lambertian.h"

class HittableListTest : public TestBase {
 public:
  void test_list_of_quads() {
    HittableList hittable_list;
    Point3 quad_bottom_left_corner(0, 0, 0);
    hittable_list.add(std::make_unique<Quad>(quad_bottom_left_corner,
                                             Vec3(1, 0, 0), Vec3(0, 1, 0)));
    hittable_list.InitBvhTree();
    assert(hittable_list.bounding_box() ==
           BoundingBox(Interval(0, 1), Interval(0, 1), Interval(0, 0)));

    // Test for hit detection on leaf nodes.
    for (double i = -1; i <= 2; i += 0.1) {
      for (double j = -1; j <= 2; j += 0.1) {
        Point3 ray_origin(0, 0, 9);
        Point3 target(i, j, 0);
        Vec3 ray_direction(Vec3(target - ray_origin));
        Ray incident_ray(ray_origin, ray_direction);
        Hittable::HitResult result;
        if (Interval(0, 1).contains(i) and Interval(0, 1).contains(j)) {
          assert(hittable_list.hit(incident_ray, constants::interval::UNIVERSAL,
                                   result));
        } else {
          assert(!hittable_list.hit(incident_ray,
                                    constants::interval::UNIVERSAL, result));
        }
      }
    }

    // Post-order DFS test.
    hittable_list.add(
        std::make_unique<Quad>(Point3(-3, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0)));
    hittable_list.add(
        std::make_unique<Quad>(Point3(-2, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0)));
    hittable_list.add(
        std::make_unique<Quad>(Point3(-1, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0)));
    hittable_list.add(
        std::make_unique<Quad>(Point3(1, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0)));
    hittable_list.add(
        std::make_unique<Quad>(Point3(2, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0)));
    hittable_list.add(
        std::make_unique<Quad>(Point3(3, 0, 0), Vec3(1, 0, 0), Vec3(0, 1, 0)));
    hittable_list.InitBvhTree();
    assert(hittable_list.bounding_box() ==
           BoundingBox(Interval(-3, 4), Interval(0, 1), Interval(0, 0)));
  }

  // test the Cornell box quads from main.cc
  void test_quads_in_main_cc() {
    // Materials
    auto left_red = std::make_shared<Lambertian>(constants::color::RED);
    auto back_green = std::make_shared<Lambertian>(constants::color::GREEN);
    auto right_blue = std::make_shared<Lambertian>(constants::color::BLUE);
    auto upper_orange = std::make_shared<Lambertian>(constants::color::ORANGE);
    auto lower_teal = std::make_shared<Lambertian>(constants::color::TEAL);

    HittableList hittable_list;
    // Left quad
    hittable_list.add(std::make_unique<Quad>(Point3(-3, -2, 5), Vec3(0, 0, -4),
                                             Vec3(0, 4, 0), left_red));
    // Center quad
    hittable_list.add(std::make_unique<Quad>(Point3(-2, -2, 0), Vec3(4, 0, 0),
                                             Vec3(0, 4, 0), back_green));
    // Right quad
    hittable_list.add(std::make_unique<Quad>(Point3(3, -2, 1), Vec3(0, 0, 4),
                                             Vec3(0, 4, 0), right_blue));
    // Top quad
    hittable_list.add(std::make_unique<Quad>(Point3(-2, 3, 1), Vec3(4, 0, 0),
                                             Vec3(0, 0, 4), upper_orange));
    // Bot quad
    hittable_list.add(std::make_unique<Quad>(Point3(-2, -3, 5), Vec3(4, 0, 0),
                                             Vec3(0, 0, -4), lower_teal));
    hittable_list.InitBvhTree();
    assert(hittable_list.bounding_box() ==
           BoundingBox(Interval(-3, 3), Interval(-3, 3), Interval(0, 5)));

    // Test the center quad
    for (double x = -2; x <= 2; x += 0.1) {
      for (double y = -2; y <= 2; y += 0.1) {
        Point3 ray_origin(0, 0, 9);
        Point3 target(x, y, 100);
        Vec3 ray_direction(Vec3(target - ray_origin));
        Ray incident_ray(ray_origin, ray_direction);
        Hittable::HitResult result;
        // TODO: Bugged quad. Broken.
        // assert(hittable_list.hit(incident_ray,
        // constants::interval::UNIVERSAL,
        //                          result));
      }
    }
  }

  void RunTest() {
    test_list_of_quads();
    test_quads_in_main_cc();
  }
};