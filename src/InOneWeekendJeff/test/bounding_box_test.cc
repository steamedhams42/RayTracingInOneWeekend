#include "InOneWeekendJeff/bounding_box.h"
#include "InOneWeekendJeff/test/test_base.h"

#include <cassert>
#include <cmath>
#include "InOneWeekendJeff/constants.h"
#include "InOneWeekendJeff/interval.h"

class BoundingBoxTest : public TestBase {
 private:
  BoundingBox create_unit_bounding_box() {
    return BoundingBox(Interval(0, 1), Interval(0, 1), Interval(0, 1));
  }

  void test_rays_on_the_surface_of_the_bounding_box() {
    BoundingBox unit_bb = create_unit_bounding_box();
    Vec3 direction(11, 11, 11);
    Point3 origin(1, 1, 1);
    Ray incident_ray(origin, direction);

    assert(!unit_bb.hit(incident_ray, Interval(0, constants::INF_DOUBLE)));
  }

  void test_rays_missing_the_bounding_box() {
    // Create 3 cases for a ray that is parallel to each axis and does not
    // hit the bounding box.
    BoundingBox unit_bb = create_unit_bounding_box();
    Vec3 direction(-3, 0, 0);
    Point3 origin(-1, 0.5, 0.5);
    Ray incident_ray(origin, direction);
    assert(!unit_bb.hit(incident_ray, Interval(0, constants::INF_DOUBLE)));

    direction = Vec3(0, 3, 0);
    incident_ray = Ray(origin, direction);
    assert(!unit_bb.hit(incident_ray, Interval(0, constants::INF_DOUBLE)));
    direction = Vec3(0, -3, 0);
    incident_ray = Ray(origin, direction);
    assert(!unit_bb.hit(incident_ray, Interval(0, constants::INF_DOUBLE)));

    direction = Vec3(0, 0, 3);
    incident_ray = Ray(origin, direction);
    assert(!unit_bb.hit(incident_ray, Interval(0, constants::INF_DOUBLE)));
    direction = Vec3(0, 0, -3);
    incident_ray = Ray(origin, direction);
    assert(!unit_bb.hit(incident_ray, Interval(0, constants::INF_DOUBLE)));
  }

  void test_merging_two_bounding_boxes() {
    BoundingBox a = create_unit_bounding_box();
    BoundingBox b = create_unit_bounding_box();
    auto merged = BoundingBox(b, a);
    assert(merged ==
           BoundingBox(Interval(0, 1), Interval(0, 1), Interval(0, 1)));

    BoundingBox c(Interval(-1, 2), Interval(-3, 4), Interval(5, 0));
    merged = BoundingBox(c, merged);

    assert(merged.x_interval() == Interval(-1, 2));
    assert(merged.y_interval() == Interval(-3, 4));
    assert(merged.z_interval() == Interval(0, 1));
  }

  void test_hit_detection_on_each_axis() {}

  void test_longest_axis() {
    BoundingBox a = create_unit_bounding_box();
    BoundingBox b = create_unit_bounding_box();
    BoundingBox c(Interval(-1, 2), Interval(-3, 4), Interval(5, 0));
    BoundingBox d(Interval(-3, 2.5), Interval(31, 410), Interval(-100, 1e6));
    auto merged = BoundingBox(b, a);
    merged = BoundingBox(c, merged);
    merged = BoundingBox(d, merged);
    assert(merged.x_interval() == Interval(-3, 2.5));
    assert(merged.y_interval() == Interval(-3, 410));
    assert(merged.z_interval() == Interval(-100, 1e6));
  }

 public:
  void RunTest() override {
    BoundingBox empty_bb;
    assert(empty_bb.x_interval() == constants::interval::EMPTY);
    assert(empty_bb.y_interval() == constants::interval::EMPTY);
    assert(empty_bb.z_interval() == constants::interval::EMPTY);

    Point3 a = CreateRandomPoint();
    Point3 b = CreateRandomPoint();
    BoundingBox bb = BoundingBox(a, b);
    assert(bb.x_interval() ==
           Interval(std::min(a.x(), b.x()), std::max(a.x(), b.x())));
    assert(bb.y_interval() ==
           Interval(std::min(a.y(), b.y()), std::max(a.y(), b.y())));
    assert(bb.z_interval() ==
           Interval(std::min(a.z(), b.z()), std::max(a.z(), b.z())));

    BoundingBox unit_bb = create_unit_bounding_box();
    Vec3 direction(3, 0, 0);
    Point3 origin(-1, 0.5, 0.5);
    Ray incident_ray(origin, direction);
    assert(unit_bb.hit(incident_ray, Interval(0, constants::INF_DOUBLE)));

    test_rays_missing_the_bounding_box();
    test_rays_on_the_surface_of_the_bounding_box();
    test_merging_two_bounding_boxes();
    test_hit_detection_on_each_axis();
    test_longest_axis();
  }
};