#include "camera.h"

#include <cassert>
#include <cmath>

#include "constants.h"
#include "hittable.h"
#include "hittable_list.h"
#include "interval.h"
#include "random.h"
#include "vec3.h"

Camera::Camera(Point3 center,
               const double focal_length,
               const double image_width,
               const double aspect_width,
               const double aspect_height,
               const double viewport_height)
    : camera_center_(center),
      focal_length_(focal_length),
      image_width_(image_width),
      aspect_width_(aspect_width),
      aspect_height_(aspect_height),
      viewport_height_(viewport_height) {}

void Camera::initialize() {
  aspect_ratio_ = aspect_width_ / aspect_height_;
  // image height cannot subceed 1
  image_height_ = std::max(1, (int)(1.0 * image_width_ / aspect_ratio_));
  viewport_width_ = viewport_height_ * image_width_ / image_height_;

  Vec3 viewport_vector_width = Vec3(viewport_width_, 0, 0);
  Vec3 viewport_vector_height = Vec3(0, -viewport_height_, 0);

  pixel_delta_width_ = viewport_vector_width / image_width_;
  pixel_delta_height_ = viewport_vector_height / image_height_;

  // Calculate location of upper-left pixel's center.
  // Start from the camera's location, move forward toward viewport by distance
  // of focal length.
  Point3 upper_left_pixel_location =
      camera_center_ - Point3(0, 0, focal_length_) - viewport_vector_width / 2 -
      viewport_vector_height / 2;

  // Point of the top-left pixel's center in the viewport.
  viewport_top_left_pixel_center_ = upper_left_pixel_location +
                                    pixel_delta_width_ / 2 +
                                    pixel_delta_height_ / 2;

  // Anti-aliasing
  pixel_samples_scale_ = 1.0 / constants::camera::SAMPLES_PER_PIXEL;
};

void Camera::render(const HittableList& hittables) {
  std::cout << "P3" << constants::nl;
  std::cout << image_width_ << ' ' << image_height_ << constants::nl;
  std::cout << constants::BYTE - 1 << constants::nl;

  for (int row = 0; row < image_height_; row++) {
    std::clog << "\rScanlines remaining: " << image_height_ - row << " "
              << std::flush;
    for (int col = 0; col < image_width_; col++) {
      Color pixel_color(0, 0, 0);
      for (int i = 0; i < constants::camera::SAMPLES_PER_PIXEL; i++) {
        Ray sample_ray = get_ray(col, row);
        pixel_color += computeRayColor(sample_ray, hittables);
      }
      pixel_color.write_color(std::cout);
    };
  }
  std::clog << "\rDone                " << std::endl;
}

Color Camera::computeRayColor(const Ray& ray,
                              const HittableList& hittables) const {
  Hittable::HitResult hit_result;
  // Check if ray hits a hittable
  if (hittables.hit(ray, Interval(0, constants::INF_DOUBLE), hit_result)) {
    // Why add +1 and divide 2?
    // Unit vector components will always be between [-1, +1], we want to map
    // to [0, 1] so we do the appropriate affine transformation.
    hit_result.normal += Vec3(1, 1, 1);
    hit_result.normal /= 2.0;
    return Color(hit_result.normal);
  }
  // Background color if ray does not hit a hittable.
  Vec3 unit_direction = ray.direction().unit();
  double scale = (unit_direction.y() + 1.0) / 2.0;
  assert(scale < 256);
  return (1.0 - scale) * Color(1, 1, 1) + scale * (Color(0.5, 0.7, 1.0));
}

Ray Camera::get_ray(int x, int y) {
  Point3 offset = sample_square();
  Point3 pixel_center = viewport_top_left_pixel_center_ +
                        (x + offset.x()) * pixel_delta_width_ +
                        (y + offset.y()) * pixel_delta_height_;
  Vec3 ray_direction(pixel_center - camera_center_);
  return Ray(camera_center_, ray_direction);
}

Point3 Camera::sample_square() const {
  return Vec3(RandomNumber::random_real(-0.5, +0.5),
              RandomNumber::random_real(-0.5, +0.5), 0);
}
