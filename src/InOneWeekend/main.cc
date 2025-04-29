#include <cassert>
#include <cmath>
#include <iostream>

#include "color.h"
#include "constants.h"
#include "point3.h"
#include "ray.h"
#include "vec3.h"

double getRayScaleFactorToSphere(const Ray& ray) {
  Vec3 CQ = constants::SPHERE_CENTER - ray.origin();
  double a = ray.direction().dot(ray.direction());
  double b = -2 * ray.direction().dot(CQ);
  double c = CQ.dot(CQ) - constants::SPHERE_RADIUS * constants::SPHERE_RADIUS;
  double discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    return -1;
  } else {
    return (-b + std::sqrt(discriminant)) / (2 * a);
  }
}

Color computeRayColor(const Ray& ray) {
  double t = getRayScaleFactorToSphere(ray);
  if (t > 0.0) {
    Point3 hit = ray.at(t) - constants::SPHERE_CENTER;
    Vec3 unit = Vec3(hit).unit();
    return 0.5 * Color(unit.x() + 1, unit.y() + 1, unit.z() + 1);
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
  std::clog << "\rDone                " << constants::nl;
}