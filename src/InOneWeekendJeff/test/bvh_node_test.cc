#include "test_base.h"

#include <cassert>
#include <memory>
#include <vector>

#include "InOneWeekendJeff/bounding_box.h"
#include "InOneWeekendJeff/hittables/bvh_node.h"
#include "InOneWeekendJeff/hittables/hittable.h"
#include "InOneWeekendJeff/hittables/hittable_list.h"
#include "InOneWeekendJeff/hittables/sphere.h"
#include "InOneWeekendJeff/interval.h"
#include "InOneWeekendJeff/point3.h"
#include "InOneWeekendJeff/ray.h"

class BvhNodeTest : public TestBase {
 public:
  void RunTest() override {
    HittableList hittable_list;
    // hittable_list.add(std::make_unique<Sphere>(Point3(-3, 1, 0), 1));
    // hittable_list.add(std::make_unique<Sphere>(Point3(-2, 1, 0), 1));
    hittable_list.add(std::make_unique<Sphere>(Point3(-1, 1, 0), 1));
    hittable_list.add(std::make_unique<Sphere>(Point3(0, 1, 0), 1));
    hittable_list.add(std::make_unique<Sphere>(Point3(1, 1, 0), 1));
    // hittable_list.add(std::make_unique<Sphere>(Point3(2, 1, 0), 1));
    // hittable_list.add(std::make_unique<Sphere>(Point3(3, 1, 0), 1));
    auto bvh = BvhNode::CreateBvhTree(hittable_list.hittables());
    assert(bvh.bounding_box() ==
           BoundingBox(Interval(-2, 2), Interval(0, 2), Interval(-1, 1)));

    Point3 origin(0, 0, -10);
    Vec3 direction(0, 1, 0);
    Ray incident_ray(origin, direction);
    Hittable::HitResult hit_result;
    assert(bvh.hit(incident_ray, Interval(0, 1000), hit_result));
  }
};