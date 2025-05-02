#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>

#include "camera.h"
#include "constants.h"
#include "hittable_list.h"
#include "point3.h"
#include "sphere.h"

HittableList hittables;

void createAndAddHittables() {
  auto sphere = std::make_unique<Sphere>(constants::sphere::SPHERE_CENTER,
                                         constants::sphere::SPHERE_RADIUS);
  auto earth = std::make_unique<Sphere>(Point3(0, -100.5, -1), 100);
  hittables.add(std::move(sphere));
  hittables.add(std::move(earth));
}

int main() {
  createAndAddHittables();

  Camera camera(
      constants::camera::CAMERA_CENTER, constants::camera::ASPECT_WIDTH,
      constants::camera::ASPECT_HEIGHT, constants::camera::IMAGE_WIDTH,
      constants::camera::FOCAL_LENGTH, constants::camera::VIEWPORT_HEIGHT);
  camera.initialize();
  camera.render(hittables);
}
