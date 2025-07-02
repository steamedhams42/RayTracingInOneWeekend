#include "InOneWeekendJeff/hittables/box.h"

#include <cmath>
#include <vector>

#include "InOneWeekendJeff/geometry/point3.h"
#include "InOneWeekendJeff/geometry/ray.h"
#include "InOneWeekendJeff/interval.h"
#include "InOneWeekendJeff/materials/material.h"

Box::Box(const Point3& front_bottom_left,
         const Point3& back_top_right,
         std::shared_ptr<Material>) {
  double dx = std::fabs(front_bottom_left.x() - back_top_right.x());
  double dy = std::fabs(front_bottom_left.y() - back_top_right.y());
  double dz = std::fabs(front_bottom_left.z() - back_top_right.z());

  front_ =
      std::make_unique<Quad>(front_bottom_left, Vec3(dx, 0, 0), Vec3(0, dy, 0));
  left_ =
      std::make_unique<Quad>(front_bottom_left, Vec3(0, 0, dz), Vec3(0, dy, 0));
  bottom_ =
      std::make_unique<Quad>(front_bottom_left, Vec3(dx, 0, 0), Vec3(0, 0, dz));
  back_ =
      std::make_unique<Quad>(back_top_right, Vec3(-dx, 0, 0), Vec3(0, -dy, 0));
  right_ =
      std::make_unique<Quad>(back_top_right, Vec3(0, 0, -dz), Vec3(0, -dy, 0));
  top_ =
      std::make_unique<Quad>(back_top_right, Vec3(-dx, 0, 0), Vec3(0, 0, -dz));

  bounding_box_ = BoundingBox(front_bottom_left, back_top_right);
}

bool Box::hit(const Ray& incident_ray,
              Interval ival,
              Hittable::HitResult& result) const {
  // Checks all sides of the box. Returns the interval with smallest ray_t
  // scalar.
  bool did_hit = false;
  Quad* all_sides[] = {left_.get(),   right_.get(), top_.get(),
                       bottom_.get(), front_.get(), back_.get()};
  for (Quad* side : all_sides) {
    if (side->hit(incident_ray, ival, result)) {
      ival = Interval(ival.min(), result.t);
      did_hit = true;
    }
  }

  return did_hit;
}

BoundingBox Box::bounding_box() {
  return bounding_box_;
}
