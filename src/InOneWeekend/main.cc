#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>

#include "camera.h"
#include "constants.h"
#include "hittable_list.h"
#include "materials/dielectric.h"
#include "materials/lambertian.h"
#include "materials/metal.h"
#include "point3.h"
#include "sphere.h"

HittableList hittables;

void createAndAddHittables() {
  // Main sphere in the center
  auto sphere = std::make_unique<Sphere>(
      constants::sphere::SPHERE_CENTER, constants::sphere::SPHERE_RADIUS,
      std::make_unique<Lambertian>(Color(0.1, 0.2, 0.5)));
  // the "grounded" sphere in the foreground
  auto earth = std::make_unique<Sphere>(
      Point3(0, -100.5, -1), 100,
      std::make_unique<Lambertian>(Color(0.8, 0.8, 0)));
  // glass metallic
  auto left_sphere = std::make_unique<Sphere>(
      Point3(-1.0, 0.0, -1.0), 0.5, std::make_unique<Dielectric>(2.0));
  // yellow metallic
  auto right_sphere =
      std::make_unique<Sphere>(Point3(1.0, 0.0, -1.0), 0.5,
                               std::make_unique<Metal>(Color(0.8, 0.6, 0.2)));

  hittables.add(std::move(sphere));
  hittables.add(std::move(earth));
  hittables.add(std::move(left_sphere));
  hittables.add(std::move(right_sphere));
}

int main() {
  createAndAddHittables();

  Camera camera(
      constants::camera::CAMERA_CENTER, constants::camera::FOCAL_LENGTH,
      constants::camera::IMAGE_WIDTH, constants::camera::ASPECT_WIDTH,
      constants::camera::ASPECT_HEIGHT, constants::camera::VIEWPORT_HEIGHT);
  camera.initialize();
  camera.render(hittables);
}
