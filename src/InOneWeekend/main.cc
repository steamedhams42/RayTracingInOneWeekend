#include <cassert>
#include <cmath>
#include <iostream>

#include "color.h"
#include "constants.h"
#include "point3.h"
#include "ray.h"
#include "sphere.h"
#include "vec3.h"

Color computeRayColor(const Ray& ray) {
  Sphere sphere(constants::SPHERE_CENTER, constants::SPHERE_RADIUS);
  Sphere::HitResult hit_result;
  if (sphere.hit(ray, -1, 1, hit_result)) {
    Point3 hit = ray.at(hit_result.t) - constants::SPHERE_CENTER;
    // Why add +1 and divide 2?
    // Unit vector components will always be between [-1, +1], we want to map it
    // to [0, 1] so we do the appropriate affine transformation.
    hit_result.normal += Vec3(1, 1, 1);
    hit_result.normal /= 2.0;
    return Color(hit_result.normal);
  }
  Vec3 unit_direction = ray.direction().unit();
  double scale = (unit_direction.y() + 1.0) / 2.0;
  assert(scale < 256);
  return (1.0 - scale) * Color(1, 1, 1) + scale * (Color(0.5, 0.7, 1.0));
}

int main() {
  // main2();
  std::cout << "P3" << constants::nl;
  std::cout << constants::IMAGE_WIDTH << ' ' << constants::IMAGE_HEIGHT
            << constants::nl;
  std::cout << constants::BYTE - 1 << constants::nl;

  for (int row = 0; row < constants::IMAGE_HEIGHT; row++) {
    std::clog << "\rScanlines remaining: " << constants::IMAGE_HEIGHT - row
              << " " << std::flush;
    for (int col = 0; col < constants::IMAGE_WIDTH; col++) {
      Point3 pixel_center = constants::VIEWPORT_TOP_LEFT_PIXEL_CENTER +
                            col * constants::PIXEL_DELTA_WIDTH +
                            row * constants::PIXEL_DELTA_HEIGHT;

      Vec3 ray_direction(pixel_center);
      Ray ray(constants::CAMERA_CENTER, ray_direction);

      Color ray_color = computeRayColor(ray);

      ray_color.write_color(std::cout);
    }
  }
  std::clog << "\rDone                " << std::endl;
}
