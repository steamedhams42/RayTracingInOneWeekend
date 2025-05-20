#include "test_base.h"

#include <memory>
#include "InOneWeekend/camera.h"
#include "InOneWeekend/constants.h"
#include "InOneWeekend/hittable.h"
#include "InOneWeekend/hittable_list.h"
#include "InOneWeekend/point3.h"
#include "InOneWeekend/sphere.h"

class CameraTest : public TestBase {
 public:
  void run_test() {
    HittableList hittables;
    Point3 sphere_center(0, 0, 1.0);
    double sphere_radius = 1.0;
    auto sphere = std::make_unique<Sphere>(sphere_center, sphere_radius);
    hittables.add(std::move(sphere));
    Point3 camera_center(0, 0, 0);

    Camera camera(
        constants::camera::CAMERA_CENTER, constants::camera::FOCAL_LENGTH,
        constants::camera::ASPECT_WIDTH, constants::camera::IMAGE_WIDTH,
        constants::camera::ASPECT_HEIGHT,
        constants::camera::VERTICAL_FIELD_OF_VIEW);
    camera.initialize();

    // Vec3 ray_direction(pixel_center);
    // Ray ray(camera_center, ray_direction);
    // camera.computeRayColor(ray, hittables);
  }
};