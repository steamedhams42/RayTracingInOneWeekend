#include <iostream>

#include "color.h"
#include "constants.h"
#include "point3.h"
#include "vec3.h"

int main() {
  std::cout << "P3" << constants::nl;
  std::cout << constants::IMAGE_WIDTH << ' ' << constants::IMAGE_HEIGHT
            << constants::nl;
  std::cout << constants::BYTE - 1 << constants::nl;

  // Calculate location of upper-left pixel's center.
  // Start from the camera's location, move forward toward viewport by dist
  // focal length
  Point3 upper_left_pixel_location = constants::CAMERA_CENTER -
                                     Point3(0, 0, constants::FOCAL_LENGTH) -
                                     Point3(0, 0, constants::FOCAL_LENGTH) -
                                     Point3(0, 0, constants::FOCAL_LENGTH);

  for (int row = 0; row < constants::IMAGE_HEIGHT; row++) {
    std::clog << "\rScanlines remaining: " << constants::IMAGE_HEIGHT - row
              << " " << std::flush;
    for (int col = 0; col < constants::IMAGE_WIDTH; col++) {
      double R = 1.0 * col / constants::IMAGE_WIDTH;
      double G = 1.0 * row / constants::IMAGE_HEIGHT;
      double B = 0.0;

      std::cout << Color(R, G, B);
    }
  }
  std::clog << "\rDone                " << constants::nl;
}
