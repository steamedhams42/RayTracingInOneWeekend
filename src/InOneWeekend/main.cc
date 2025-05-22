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
#include "random.h"
#include "sphere.h"

HittableList hittables;

void createAndAddHittables() {
  // the "grounded" sphere in the foreground
  auto earth = std::make_unique<Sphere>(
      Point3(0, -1000, 0), 1000,
      std::make_unique<Lambertian>(Color(0.5, 0.5, 0.5)));
  hittables.add(std::move(earth));

  for (int x = -11; x < 11; x++) {
    for (int z = -11; z < 11; z++) {
      auto choose_mat = Random::random_real();
      Point3 center(x + 0.9 * Random::random_real(), 0.2,
                    z + 0.9 * Random::random_real());
      if (Vec3(center - Point3(4, -0.2, 0)).norm() > 0.9) {
        std::unique_ptr<Material> sphere_material;
        std::unique_ptr<Sphere> sphere;

        if (choose_mat < 0.8) {
          // diffuse
          auto albedo = Color::random_color() * Color::random_color();
          sphere_material = std::make_unique<Lambertian>(albedo);
        } else if (choose_mat < 0.95) {
          // metal
          auto albedo =
              Color(Random::random_real(0.5, 1), Random::random_real(0.5, 1),
                    Random::random_real(0.5, 1));
          sphere_material = std::make_unique<Metal>(albedo);
        } else {
          // glass
          sphere_material = std::make_unique<Dielectric>(1.5);
        }
        hittables.add(
            std::make_unique<Sphere>(center, 0.2, std::move(sphere_material)));
      }
    }
  }

  // glass metallic
  auto left_sphere = std::make_unique<Sphere>(
      Point3(0, 1, 0), 1, std::make_unique<Dielectric>(1.5));

  // Main sphere in the center
  auto center_sphere = std::make_unique<Sphere>(
      Point3(-4, 1, 0), 1.0,
      std::make_unique<Lambertian>(Color(0.4, 0.2, 0.1)));

  // yellow metallic
  auto right_sphere = std::make_unique<Sphere>(Point3(4, 1.0, 0.0), 1.0,
                                               std::make_unique<Metal>());

  hittables.add(std::move(center_sphere));
  hittables.add(std::move(left_sphere));
  hittables.add(std::move(right_sphere));
}

int main() {
  createAndAddHittables();

  Camera camera(
      constants::camera::CAMERA_CENTER, constants::camera::FOCAL_POINT,
      constants::camera::VERTICAL_FIELD_OF_VIEW, constants::camera::IMAGE_WIDTH,
      constants::camera::ASPECT_WIDTH, constants::camera::ASPECT_HEIGHT);
  camera.initialize();
  camera.render(hittables);
}
