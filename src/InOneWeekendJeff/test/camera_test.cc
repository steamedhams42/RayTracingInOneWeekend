#include "test_base.h"

#include <memory>
#include "InOneWeekendJeff/camera.h"
#include "InOneWeekendJeff/constants.h"
#include "InOneWeekendJeff/geometry/point3.h"
#include "InOneWeekendJeff/hittables/hittable.h"
#include "InOneWeekendJeff/hittables/hittable_list.h"
#include "InOneWeekendJeff/hittables/sphere.h"

class CameraTest : public TestBase {
 public:
  void RunTest() {
    HittableList hittables;
    Point3 sphere_center(0, 0, 1.0);
    double sphere_radius = 1.0;
    auto sphere = std::make_unique<Sphere>(sphere_center, sphere_radius);
    hittables.add(std::move(sphere));
    Point3 camera_center(0, 0, 0);

    Camera camera(
        constants::camera::CAMERA_CENTER, constants::camera::FOCAL_POINT,
        constants::camera::FOCAL_DISTANCE, constants::camera::ASPECT_WIDTH,
        constants::camera::IMAGE_WIDTH, constants::camera::ASPECT_HEIGHT,
        constants::camera::VERTICAL_FIELD_OF_VIEW,
        constants::camera::SAMPLES_PER_PIXEL,
        constants::camera::MAX_LIGHT_BOUNCES);
    camera.Initialize();

    // Vec3 ray_direction(pixel_center);
    // Ray ray(camera_center, ray_direction);
    // camera.computeRayColor(ray, hittables);
  }
};