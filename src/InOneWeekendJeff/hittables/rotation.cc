#include "InOneWeekendJeff/hittables/rotation.h"

#include <cmath>

#include "InOneWeekendJeff/constants.h"
#include "InOneWeekendJeff/utils.h"

Rotation::Rotation(std::shared_ptr<Hittable> hittable,
                   double degrees_of_rotation)
    : hittable_(hittable), degrees_of_rotation_(degrees_of_rotation) {
  auto radians = utils::DegreesToRadians(degrees_of_rotation_);
  double sin_theta = std::sin(radians);
  double cos_theta = std::cos(radians);
  bounding_box_ = hittable_->bounding_box();

  Point3 min(constants::INF_DOUBLE, constants::INF_DOUBLE,
             constants::INF_DOUBLE);
  Point3 max(-constants::INF_DOUBLE, -constants::INF_DOUBLE,
             -constants::INF_DOUBLE);

  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      for (int k = 0; k < 2; k++) {
        auto x = i * bounding_box_.x_interval().max() +
                 (1 - i) * bounding_box_.x_interval().min();
        auto y = j * bounding_box_.y_interval().max() +
                 (1 - j) * bounding_box_.y_interval().min();
        auto z = k * bounding_box_.z_interval().max() +
                 (1 - k) * bounding_box_.z_interval().min();

        auto newx = cos_theta * x + sin_theta * z;
        auto newz = -sin_theta * x + cos_theta * z;

        Vec3 tester(newx, y, newz);

        for (int c = 0; c < 3; c++) {
          min[c] = std::fmin(min[c], tester[c]);
          max[c] = std::fmax(max[c], tester[c]);
        }
      }
    }
  }

  bounding_box_ = BoundingBox(min, max);
}

bool Rotation::Hit(const Ray& incident_ray,
                   Interval ival,
                   Hittable::HitResult& result) const {
  Ray ray_prime(incident_ray.RotateY(degrees_of_rotation_));

  if (!hittable_->Hit(ray_prime, ival, result)) {
    return false;
  }

  Ray hit_ray(result.incident_point, result.normal);
  hit_ray = hit_ray.RotateY(-degrees_of_rotation_);

  result.incident_point = hit_ray.origin();
  result.normal = hit_ray.direction();

  return true;
}

BoundingBox Rotation::bounding_box() {
  return bounding_box_;
}
