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
         const double aspect_width,
         const double aspect_height,
         const double image_width,
         const double focal_length,
         const double viewport_height);

  void initialize();
  void render(const HittableList&);

 private:
  friend class CameraTest;

  Color computeRayColor(const Ray& ray, const HittableList&) const;

  Point3 camera_center_;
  double focal_length_;

  double aspect_width_;
  double aspect_height_;
  double aspect_ratio_;

  // Image dimensions in pixels
  double image_width_;
  double image_height_;

  double viewport_height_;
  double viewport_width_;

  // The space between two pixels in the viewport
  Vec3 pixel_delta_width_;
  Vec3 pixel_delta_height_;

  // Location of the top left pixel's center in the viewport
  Point3 viewport_top_left_pixel_center_;

  // Anti-aliasing
  double pixel_samples_scale_ = 1.0 / constants::camera::SAMPLES_PER_PIXEL;
};
#endif