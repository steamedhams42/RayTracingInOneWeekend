#include "camera.h"

#include <cassert>
#include <cmath>

#include "InOneWeekendJeff/constants.h"
#include "InOneWeekendJeff/geometry/vec3.h"
#include "InOneWeekendJeff/hittables/hittable.h"
#include "InOneWeekendJeff/hittables/hittable_list.h"
#include "InOneWeekendJeff/interval.h"
#include "InOneWeekendJeff/materials/material.h"
#include "InOneWeekendJeff/utils.h"

Camera::Camera(Point3 center,
               Point3 focal_point,
               double focal_distance,
               double vertical_field_of_view,
               double image_width,
               double aspect_width,
               double aspect_height,
               int samples_per_pixel,
               int max_recursion_depth,
               Color background_color)
    : camera_center_(center),
      focal_point_(focal_point),
      focal_distance_(focal_distance),
      vertical_field_of_view_(vertical_field_of_view),
      image_width_(image_width),
      aspect_width_(aspect_width),
      aspect_height_(aspect_height),
      samples_per_pixel_(samples_per_pixel),
      max_recursion_depth_(max_recursion_depth),
      background_color_(background_color) {
  Initialize();
}

void Camera::Initialize() {
  aspect_ratio_ = aspect_width_ / aspect_height_;

  // Image height cannot subceed 1
  image_height_ = std::max(1, (int)(1.0 * image_width_ / aspect_ratio_));

  // Focus
  camera_direction_ = Vec3(focal_point_ - camera_center_).unit();

  // Camera basis vectors
  u_ = camera_direction_.cross(constants::Y_AXIS_BASIS).unit();
  v_ = u_.cross(camera_direction_);

  // Viewport
  // Draw a right triangle from camera to viewport.
  viewport_height_ =
      2 * focal_distance_ *
      std::tan(utils::DegreesToRadians(vertical_field_of_view_ / 2));
  viewport_width_ = viewport_height_ * image_width_ / image_height_;

  Vec3 viewport_vector_width = viewport_width_ * u_;
  Vec3 viewport_vector_height = viewport_height_ * -v_;

  pixel_delta_width_ = viewport_vector_width / image_width_;
  pixel_delta_height_ = viewport_vector_height / image_height_;

  // Calculate location of upper-left pixel's center.
  // Start from the camera's location, move forward toward viewport by
  // distance of focal length.
  Point3 upper_left_pixel_location =
      Ray(camera_center_, camera_direction_).at(focal_distance_) -
      viewport_vector_width / 2 - viewport_vector_height / 2;

  // Point of the top-left pixel's center in the viewport.
  viewport_top_left_pixel_center_ = upper_left_pixel_location +
                                    pixel_delta_width_ / 2 +
                                    pixel_delta_height_ / 2;

  // Calculate the camera defocus disk basis vectors.
  auto defocus_radius =
      focal_distance_ * std::tan(utils::DegreesToRadians(defocus_angle_ / 2));
  defocus_disk_u_ = u_ * defocus_radius;
  defocus_disk_v_ = v_ * defocus_radius;
};

void Camera::Render(const HittableList& hittables) {
  std::cout << "P3" << constants::nl;
  std::cout << image_width_ << ' ' << image_height_ << constants::nl;
  std::cout << constants::BYTE - 1 << constants::nl;

  for (int y = 0; y < image_height_; y++) {
    std::clog << "\rScanlines remaining: " << image_height_ - y << " "
              << std::flush;
    for (int x = 0; x < image_width_; x++) {
      Color pixel_color(0, 0, 0);
      for (int i = 0; i < samples_per_pixel_; i++) {
        Ray random_ray = GetRandomRayWithXY(x, y);
        pixel_color += ComputeRayColor(random_ray, hittables);
      }
      // Anti-aliasing
      double pixel_samples_scale = 1.0 / samples_per_pixel_;
      pixel_color *= pixel_samples_scale;
      pixel_color.write_color(std::cout);
    };
  }
  std::clog << "\rDone                " << std::endl;
}

Color Camera::ComputeRayColor(const Ray& incident_ray,
                              const HittableList& hittables,
                              int light_bounces) const {
  if (light_bounces == max_recursion_depth_) {
    return Color(0, 0, 0);
  }
  Hittable::HitResult hit_result;
  // Check if ray hits a hittable
  if (!hittables.Hit(incident_ray, Interval(0.001, constants::INF_DOUBLE),
                     hit_result)) {
    // If ray hits nothing, return background color.
    return background_color_;
  }
  Ray scattered_ray;
  Color attenuation;
  Color color_from_emission = hit_result.material->Emit(
      hit_result.u, hit_result.v, hit_result.incident_point);
  // If ray is reflected, recurse.
  if (!hit_result.material->Scatter(incident_ray, hit_result, attenuation,
                                    scattered_ray)) {
    return color_from_emission;
  }
  return color_from_emission + attenuation * ComputeRayColor(scattered_ray,
                                                             hittables,
                                                             light_bounces + 1);
}

Ray Camera::GetRandomRayWithXY(int x, int y) {
  Point3 offset = GetRandomPointFromUnitSquare();
  // This converts a (x, y) cell on the viewport back to cartesian
  // coordinates.
  Point3 pixel_center = viewport_top_left_pixel_center_ +
                        (x + offset.x()) * pixel_delta_width_ +
                        (y + offset.y()) * pixel_delta_height_;
  Point3 ray_origin = camera_center_;
  //(defocus_angle_ <= 0) ? camera_center_ : defocus_disk_sample();
  Vec3 ray_direction(pixel_center - camera_center_);
  double ray_time = utils::Random::random_real();
  return Ray(ray_origin, ray_direction, ray_time);
}

Point3 Camera::GetRandomPointFromUnitSquare() const {
  return Vec3(utils::Random::random_real(-0.5, +0.5),
              utils::Random::random_real(-0.5, +0.5), 0);
}

Vec3 Camera::defocus_disk_sample() const {
  // Returns a random point in the camera defocus disk.
  auto p = Vec3::random_vec3_on_disk();
  return Vec3(camera_center_) + (p[0] * defocus_disk_u_) +
         (p[1] * defocus_disk_v_);
}