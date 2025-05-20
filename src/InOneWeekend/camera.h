#ifndef CAMERA_H
#define CAMERA_H

#include "color.h"
#include "constants.h"
#include "hittable_list.h"
#include "point3.h"
#include "ray.h"

class CameraTest;

class Camera {
 public:
  Camera(Point3 center,
         const double focal_length,
         const double image_width,
         const double aspect_width,
         const double aspect_height,
         const double vertical_field_of_view);

  void initialize();
  void render(const HittableList&);

 private:
  friend class CameraTest;

  // Uses recursion to bounce light off hittable surfaces (diffuse reflection)
  Color computeRayColor(
      const Ray& ray,
      const HittableList&,
      int light_bounces_remaining = constants::camera::MAX_LIGHT_BOUNCES) const;

  // Returns a random sampled ray cenetered at [x, y]
  Ray get_sampled_ray(int x, int y);

  // Returns a random point in the [-.5,-.5]-[+.5,+.5] unit square.
  Point3 sample_square() const;

  double degrees_to_radians(double deg) const;

  Point3 camera_center_;
  double focal_length_;
  double vertical_field_of_view_;

  // Image dimensions in pixels
  double image_width_;
  double image_height_;

  double aspect_width_;
  double aspect_height_;
  double aspect_ratio_;

  double viewport_height_;
  double viewport_width_;

  // The space between two pixels in the viewport
  Vec3 pixel_delta_width_;
  Vec3 pixel_delta_height_;

  // Location of the top left pixel's center in the viewport
  Point3 viewport_top_left_pixel_center_;

  // Anti-aliasing
  double pixel_samples_scale_;
};
#endif