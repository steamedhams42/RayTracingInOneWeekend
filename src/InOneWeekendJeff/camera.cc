#include "camera.h"

#include <cassert>
#include <cmath>

#include "InOneWeekendJeff/hittables/hittable.h"
#include "InOneWeekendJeff/hittables/hittable_list.h"
#include "constants.h"
#include "interval.h"
#include "materials/material.h"
#include "random.h"
#include "vec3.h"

Camera::Camera(const Point3 center,
               const Point3 focal_point,
               const double focal_distance,
               const double vertical_field_of_view,
               const double image_width,
               const double aspect_width,
               const double aspect_height)
    : camera_center_(center),
      focal_point_(focal_point),
      focal_distance_(focal_distance),
      vertical_field_of_view_(vertical_field_of_view),
      image_width_(image_width),
      aspect_width_(aspect_width),
      aspect_height_(aspect_height) {}

void Camera::initialize() {
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
  viewport_height_ = 2 * focal_distance_ *
                     std::tan(degrees_to_radians(vertical_field_of_view_ / 2));
  viewport_width_ = viewport_height_ * image_width_ / image_height_;

  Vec3 viewport_vector_width = viewport_width_ * u_;
  Vec3 viewport_vector_height = viewport_height_ * -v_;

  pixel_delta_width_ = viewport_vector_width / image_width_;
  pixel_delta_height_ = viewport_vector_height / image_height_;

  // Calculate location of upper-left pixel's center.
  // Start from the camera's location, move forward toward viewport by distance
  // of focal length.
  Point3 upper_left_pixel_location =
      Ray(camera_center_, camera_direction_).at(focal_distance_) -
      viewport_vector_width / 2 - viewport_vector_height / 2;

  // Point of the top-left pixel's center in the viewport.
  viewport_top_left_pixel_center_ = upper_left_pixel_location +
                                    pixel_delta_width_ / 2 +
                                    pixel_delta_height_ / 2;

  // Calculate the camera defocus disk basis vectors.
  auto defocus_radius =
      focal_distance_ * std::tan(degrees_to_radians(defocus_angle_ / 2));
  defocus_disk_u_ = u_ * defocus_radius;
  defocus_disk_v_ = v_ * defocus_radius;

  // Anti-aliasing
  pixel_samples_scale_ = 1.0 / constants::camera::SAMPLES_PER_PIXEL;
};

void Camera::render(const HittableList& hittables) {
  std::cout << "P3" << constants::nl;
  std::cout << image_width_ << ' ' << image_height_ << constants::nl;
  std::cout << constants::BYTE - 1 << constants::nl;

  for (int y = 0; y < image_height_; y++) {
    std::clog << "\rScanlines remaining: " << image_height_ - y << " "
              << std::flush;
    for (int x = 0; x < image_width_; x++) {
      if (x == 80 and y == 21) {
        std::cout << "First quad hit" << std::endl;
      }
      Color pixel_color(0, 0, 0);
      for (int i = 0; i < constants::camera::SAMPLES_PER_PIXEL; i++) {
        Ray random_ray = get_random_ray_within_unit_square(x, y);
        pixel_color += computeRayColor(random_ray, hittables);
      }
      pixel_color *= pixel_samples_scale_;
      pixel_color.write_color(std::cout);
    };
  }
  std::clog << "\rDone                " << std::endl;
}

Color Camera::computeRayColor(const Ray& incident_ray,
                              const HittableList& hittables,
                              int light_bounces_remaining) const {
  if (light_bounces_remaining == 0) {
    return Color(0, 0, 0);
  }
  Hittable::HitResult hit_result;
  // Check if ray hits a hittable
  if (hittables.hit(incident_ray, Interval(0.001, constants::INF_DOUBLE),
                    hit_result)) {
    Ray scattered_ray;
    Color attenuation;
    if (hit_result.material->scatter(incident_ray, hit_result, attenuation,
                                     scattered_ray)) {
      return attenuation * computeRayColor(scattered_ray, hittables,
                                           light_bounces_remaining - 1);
    }
    return Color(0, 0, 0);
  }
  // Background color if ray does not hit a hittable.
  Vec3 unit_direction = incident_ray.direction().unit();
  double scale = (unit_direction.y() + 1.0) / 2.0;
  assert(scale < 256);
  return (1.0 - scale) * Color(1, 1, 1) + scale * (Color(0.5, 0.7, 1.0));
}

Ray Camera::get_random_ray_within_unit_square(int x, int y) {
  Point3 offset = get_random_point_from_unit_square();
  // This converts a (x, y) cell on the viewport back to cartesian coordinates.
  Point3 pixel_center = viewport_top_left_pixel_center_ +
                        (x + offset.x()) * pixel_delta_width_ +
                        (y + offset.y()) * pixel_delta_height_;
  Point3 ray_origin = camera_center_;
  //(defocus_angle_ <= 0) ? camera_center_ : defocus_disk_sample();
  Vec3 ray_direction(pixel_center - camera_center_);
  double ray_time = Random::random_real();
  return Ray(ray_origin, ray_direction, ray_time);
}

Point3 Camera::get_random_point_from_unit_square() const {
  return Vec3(Random::random_real(-0.5, +0.5), Random::random_real(-0.5, +0.5),
              0);
}

double Camera::degrees_to_radians(double deg) const {
  return deg * constants::PI / 180.0;
}

Vec3 Camera::defocus_disk_sample() const {
  // Returns a random point in the camera defocus disk.
  auto p = Vec3::random_vec3_on_disk();
  return Vec3(camera_center_) + (p[0] * defocus_disk_u_) +
         (p[1] * defocus_disk_v_);
}