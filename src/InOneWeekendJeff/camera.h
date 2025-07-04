#ifndef CAMERA_H
#define CAMERA_H

#include "InOneWeekendJeff/geometry/point3.h"
#include "InOneWeekendJeff/geometry/ray.h"
#include "color.h"
#include "constants.h"
#include "hittables/hittable_list.h"

class CameraTest;

class Camera {
 public:
  Camera(const Point3 center,
         Point3 focal_point,
         double focal_distance,
         double image_width,
         double aspect_width,
         double aspect_height,
         double vertical_field_of_view,
         int samples_per_pixel,
         int max_recursion_depth);

  void Initialize();
  void Render(const HittableList&);

 private:
  friend class CameraTest;

  // Uses recursion to bounce light off hittable surfaces (diffuse reflection)
  Color ComputeRayColor(const Ray& ray,
                        const HittableList&,
                        int light_bounces = 0) const;

  // Returns a random ray originating from camera center pointed at
  // [x, y] + [+/-0.5, +/-0.5] unit square.
  Ray GetRandomRayWithXY(int x, int y);

  // Returns a random point in the [+/-0.5, +/-0.5] unit square.
  Point3 GetRandomPointFromUnitSquare() const;

  Vec3 defocus_disk_sample() const;

  Point3 camera_center_;
  // The point at which the camera's focus is optimal.
  Point3 focal_point_;
  // Normal vector of the camera's plane.
  Vec3 camera_direction_;
  // Distance between camera and focus point
  double focal_distance_;
  // Camera's vertical angle of view. Name is confusing.
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

  // Basis vector of the camera plane's width
  Vec3 u_;
  // Basis vector of the camera plane's height
  Vec3 v_;

  // Basis vector of the disk's width
  Vec3 defocus_disk_u_;
  // Basis vector of the disk's height
  Vec3 defocus_disk_v_;
  // Variation angle of rays through each pixel (degrees).
  // Values > 0,0 adds a blurring effect
  double defocus_angle_ = 0.0;

  // Number of random rays sampled per pixel. Increases fidelity and computation
  int samples_per_pixel_;
  int max_recursion_depth_;
};
#endif