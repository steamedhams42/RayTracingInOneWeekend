#include <cassert>
#include <iostream>

#include "color.h"
#include "constants.h"
#include "point3.h"
#include "ray.h"
#include "vec3.h"

bool doesRayHitSphere(const Ray& ray) {
  Vec3 CQ = constants::SPHERE_CENTER - ray.origin();
  double a = ray.direction().dot(ray.direction());
  double b = -2 * ray.direction().dot(CQ);
  double c = CQ.dot(CQ) - constants::SPHERE_RADIUS * constants::SPHERE_RADIUS;
  double discriminant = b * b - 4 * a * c;
  return discriminant >= 0;
}

color::Color computeRayColor(const Ray& ray) {
  if (doesRayHitSphere(ray)) {
    // return color::RED;
  }
  Vec3 unit_direction = ray.direction().unit();
  double scale = (unit_direction.y() + 1.0) / 2.0;
  assert(scale < 256);
  return (1.0 - scale) * color::Color(1, 1, 1) +
         scale * (color::Color(0.5, 0.7, 1.0));
}

int main() {
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

      color::Color ray_color = computeRayColor(ray);

      color::write_color(std::cout, ray_color);
    }
  }
  std::clog << "\rDone                " << constants::nl;
}
