#include "InOneWeekendJeff/hittables/constant_medium.h"

#include "InOneWeekendJeff/constants.h"
#include "InOneWeekendJeff/materials/isotropic.h"
#include "InOneWeekendJeff/utils.h"

ConstantMedium::ConstantMedium(std::unique_ptr<Hittable> boundary,
                               std::unique_ptr<Texture> texture,
                               double density)
    : boundary_(std::move(boundary)),
      texture_(std::make_unique<Isotropic>(std::move(texture))),
      density_(density) {}

ConstantMedium::ConstantMedium(std::unique_ptr<Hittable> boundary,
                               const Color& albedo,
                               double density)
    : boundary_(std::move(boundary)),
      texture_(std::make_unique<Isotropic>(albedo)),
      density_(density) {}

bool ConstantMedium::Hit(const Ray& incident_ray,
                         Interval ival,
                         Hittable::HitResult& result) const {
  HitResult result1, result2;

  if (!boundary_->Hit(incident_ray, constants::interval::UNIVERSAL, result1)) {
    return false;
  }

  if (!boundary_->Hit(incident_ray,
                      Interval(result1.t + 0.0001, constants::INF_DOUBLE),
                      result2)) {
    return false;
  }

  result1.t = std::fmin(result1.t, ival.min());
  result2.t = std::fmax(result2.t, ival.max());

  if (result1.t >= result2.t) {
    return false;
  }

  result1.t = std::fmax(0, result1.t);

  auto ray_length = incident_ray.direction().norm();
  auto distance_inside_boundary = (result2.t - result1.t) * ray_length;
  auto hit_distance = (-1 / density_) * std::log(utils::Random::random_real());

  if (hit_distance > distance_inside_boundary)
    return false;

  result.t = result1.t + hit_distance / ray_length;
  result.incident_point = incident_ray.at(result.t);

  result.normal = Vec3(1, 0, 0);  // arbitrary
  result.front_face = true;       // also arbitrary
  result.material = texture_.get();

  return true;
}

BoundingBox ConstantMedium::bounding_box() {
  return boundary_->bounding_box();
}