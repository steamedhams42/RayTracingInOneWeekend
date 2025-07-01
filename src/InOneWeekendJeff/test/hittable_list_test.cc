#include "InOneWeekendJeff/test/test_base.h"

#include <cassert>
#include <memory>

#include "InOneWeekendJeff/bounding_box.h"
#include "InOneWeekendJeff/constants.h"
#include "InOneWeekendJeff/hittables/bvh_node.h"
#include "InOneWeekendJeff/hittables/hittable_list.h"
#include "InOneWeekendJeff/hittables/quad.h"
#include "InOneWeekendJeff/interval.h"
#include "InOneWeekendJeff/point3.h"
#include "InOneWeekendJeff/ray.h"
#include "InOneWeekendJeff/vec3.h"

class HittableListTest : public TestBase {
 public:
  void RunTest() {
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
};