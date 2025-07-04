#include <cassert>
#include <cmath>
#include <iostream>
#include <memory>

#include "InOneWeekendJeff/camera.h"
#include "InOneWeekendJeff/constants.h"
#include "InOneWeekendJeff/geometry/point3.h"
#include "InOneWeekendJeff/hittables/box.h"
#include "InOneWeekendJeff/hittables/bvh_node.h"
#include "InOneWeekendJeff/hittables/hittable_list.h"
#include "InOneWeekendJeff/hittables/quad.h"
#include "InOneWeekendJeff/hittables/rotation.h"
#include "InOneWeekendJeff/hittables/sphere.h"
#include "InOneWeekendJeff/hittables/translation.h"
#include "InOneWeekendJeff/materials/dielectric.h"
#include "InOneWeekendJeff/materials/diffuse_light.h"
#include "InOneWeekendJeff/materials/lambertian.h"
#include "InOneWeekendJeff/materials/metal.h"
#include "InOneWeekendJeff/textures/checker_texture.h"
#include "InOneWeekendJeff/textures/image_texture.h"
#include "InOneWeekendJeff/textures/solid_color_texture.h"
#include "InOneWeekendJeff/utils.h"

HittableList hittables;

void CreateAndAddHittables() {
  // The "grounded" sphere in the foreground
  auto earth = std::make_unique<Sphere>(
      Point3(0, -1000, 0), 1000,
      std::make_shared<Lambertian>(
          std::make_unique<SolidColorTexture>(Color(0.5, 0.5, 0.5))));
  hittables.add(std::move(earth));

  for (int x = -11; x < 11; x++) {
    for (int z = -11; z < 11; z++) {
      auto choose_mat = utils::Random::random_real();
      Point3 center(x + 0.9 * utils::Random::random_real(), 0.2,
                    z + 0.9 * utils::Random::random_real());
      // Removes bouncing effect
      Point3 center_final = center;
      if (Vec3(center - Point3(4, -0.2, 0)).norm() > 0.9) {
        std::shared_ptr<Material> sphere_material;
        std::unique_ptr<Sphere> sphere;

        if (choose_mat < 0.8) {
          // diffuse
          auto albedo = Color::random_color() * Color::random_color();
          sphere_material = std::make_shared<Lambertian>(
              std::make_unique<SolidColorTexture>(albedo));
          // Adds bouncing effect
          // center_final = center + Point3(0, utils::Random::random_real(0,
          // 0.5), 0);
        } else if (choose_mat < 0.95) {
          // metal
          auto albedo = Color(utils::Random::random_real(0.5, 1),
                              utils::Random::random_real(0.5, 1),
                              utils::Random::random_real(0.5, 1));
          sphere_material = std::make_unique<Metal>(albedo);
        } else {
          // glass
          sphere_material = std::make_unique<Dielectric>(1.5);
        }
        hittables.add(std::make_unique<Sphere>(center, center_final, 0.2,
                                               sphere_material));
      }
    }
  }

  // brown sphere in the back
  auto brown_sphere = std::make_unique<Sphere>(
      Point3(-4, 1, 0), 1.0,
      std::make_shared<Lambertian>(
          std::make_unique<SolidColorTexture>(Color(0.4, 0.2, 0.1))));

  // glass sphere in the center
  auto glass_sphere = std::make_unique<Sphere>(
      Point3(0, 1, 0), 1, std::make_unique<Dielectric>(1.5));

  // metallic sphere in front
  auto metal_sphere = std::make_unique<Sphere>(Point3(4, 1.0, 0.0), 1.0,
                                               std::make_unique<Metal>());

  hittables.add(std::move(brown_sphere));
  hittables.add(std::move(glass_sphere));
  hittables.add(std::move(metal_sphere));
  hittables.InitBvhTree();
}

void RenderBouncingSpheres() {
  CreateAndAddHittables();

  Camera camera(
      constants::camera::CAMERA_CENTER, constants::camera::FOCAL_POINT,
      constants::camera::FOCAL_DISTANCE,
      constants::camera::VERTICAL_FIELD_OF_VIEW, constants::camera::IMAGE_WIDTH,
      constants::camera::ASPECT_WIDTH, constants::camera::ASPECT_HEIGHT);
  camera.Render(hittables);
}

void RenderCheckeredSpheres() {
  hittables.add(std::make_unique<Sphere>(
      Point3(0, 10, 0), 10,
      std::make_shared<Lambertian>(std::make_unique<CheckerTexture>(
          0.32, constants::color::BLACK, constants::color::WHITE))));
  hittables.add(std::make_unique<Sphere>(
      Point3(0, -10, 0), 10,
      std::make_shared<Lambertian>(std::make_unique<CheckerTexture>(
          0.32, constants::color::BLACK, constants::color::WHITE))));
  hittables.InitBvhTree();

  Camera camera(
      constants::camera::CAMERA_CENTER, constants::camera::FOCAL_POINT,
      constants::camera::FOCAL_DISTANCE,
      constants::camera::VERTICAL_FIELD_OF_VIEW, constants::camera::IMAGE_WIDTH,
      constants::camera::ASPECT_WIDTH, constants::camera::ASPECT_HEIGHT);
  camera.Render(hittables);
}

void RenderEarth() {
  auto globe = std::make_unique<Sphere>(
      Point3(0, 0, 0), 2.0,
      std::make_shared<Lambertian>(
          std::make_unique<ImageTexture>("images/earthmap.jpg")));
  hittables.add(std::move(globe));
  hittables.InitBvhTree();

  Point3 camera_center(0, 0, 12);
  Camera camera(camera_center, constants::camera::FOCAL_POINT,
                Point3(camera_center - constants::camera::FOCAL_POINT).norm(),
                constants::camera::VERTICAL_FIELD_OF_VIEW,
                constants::camera::IMAGE_WIDTH, constants::camera::ASPECT_WIDTH,
                constants::camera::ASPECT_HEIGHT);
  camera.Render(hittables);
}

void RenderQuads() {
  // Materials
  auto left_red = std::make_shared<Lambertian>(constants::color::RED);
  auto back_green = std::make_shared<Lambertian>(constants::color::GREEN);
  auto right_blue = std::make_shared<Lambertian>(constants::color::BLUE);
  auto upper_orange = std::make_shared<Lambertian>(constants::color::ORANGE);
  auto lower_teal = std::make_shared<Lambertian>(constants::color::TEAL);

  // Quads
  hittables.add(std::make_unique<Quad>(Point3(-3, -2, 5), Vec3(0, 0, -4),
                                       Vec3(0, 4, 0), left_red));
  hittables.add(std::make_unique<Quad>(Point3(-2, -2, 0), Vec3(4, 0, 0),
                                       Vec3(0, 4, 0), back_green));
  hittables.add(std::make_unique<Quad>(Point3(3, -2, 1), Vec3(0, 0, 4),
                                       Vec3(0, 4, 0), right_blue));
  hittables.add(std::make_unique<Quad>(Point3(-2, 3, 1), Vec3(4, 0, 0),
                                       Vec3(0, 0, 4), upper_orange));
  hittables.add(std::make_unique<Quad>(Point3(-2, -3, 5), Vec3(4, 0, 0),
                                       Vec3(0, 0, -4), lower_teal));
  hittables.InitBvhTree();

  // Camera
  Point3 camera_center(0, 0, 9);
  Camera camera(camera_center, constants::camera::FOCAL_POINT,
                /*focal distance*/
                Point3(camera_center - constants::camera::FOCAL_POINT).norm(),
                /*FoV*/ 80, constants::camera::IMAGE_WIDTH,
                constants::camera::ASPECT_WIDTH,
                constants::camera::ASPECT_HEIGHT);
  camera.Render(hittables);
}

void RenderSimpleLight() {
  auto earth = std::make_unique<Sphere>(Point3(0, -1000, 0), 1000);
  auto ball = std::make_unique<Sphere>(Point3(0, 2, 0), 2);
  hittables.add(std::move(earth));
  hittables.add(std::move(ball));

  // Light source
  auto diffuse_light = std::make_shared<DiffuseLight>(Color(1, 1, 1));
  auto light_pane = std::make_unique<Quad>(Point3(3, 1, -2), Vec3(2, 0, 0),
                                           Vec3(0, 2, 0), diffuse_light);
  hittables.add(std::move(light_pane));

  // Add a spherical light source
  hittables.add(std::make_unique<Sphere>(
      Point3(0, 7, 0), 2, std::make_unique<DiffuseLight>(Color(1, 1, 1))));
  hittables.InitBvhTree();

  // Camera
  Point3 camera_center(13, 2, 2);
  Camera camera(camera_center, /*focal point*/ Point3(0, 2, 0),
                /*focal distance*/
                Point3(camera_center - constants::camera::FOCAL_POINT).norm(),
                /*FoV*/ 80, constants::camera::IMAGE_WIDTH,
                constants::camera::ASPECT_WIDTH,
                constants::camera::ASPECT_HEIGHT);
  camera.Render(hittables);
}

void RenderCornellBox() {
  // Colors
  auto red = std::make_shared<Lambertian>(Color(.65, .05, .05));
  auto white = std::make_shared<Lambertian>(Color(.73, .73, .73));
  auto green = std::make_shared<Lambertian>(Color(.12, .45, .15));
  auto light = std::make_shared<DiffuseLight>(Color(1, 1, 1), 15.0);

  // Walls
  hittables.add(std::make_unique<Quad>(Point3(555, 0, 0), Vec3(0, 555, 0),
                                       Vec3(0, 0, 555), green));
  hittables.add(std::make_unique<Quad>(Point3(0, 0, 0), Vec3(0, 555, 0),
                                       Vec3(0, 0, 555), red));
  hittables.add(std::make_unique<Quad>(Point3(343, 554, 332), Vec3(-130, 0, 0),
                                       Vec3(0, 0, -105), light));
  hittables.add(std::make_unique<Quad>(
      Point3(0, 0, 0), Vec3(555, 0, 0), Vec3(0, 0, 555),
      std::make_shared<Lambertian>(Color(.73, .73, .73))));
  hittables.add(std::make_unique<Quad>(
      Point3(555, 555, 555), Vec3(-555, 0, 0), Vec3(0, 0, -555),
      std::make_shared<Lambertian>(Color(.73, .73, .73))));
  hittables.add(std::make_unique<Quad>(
      Point3(0, 0, 555), Vec3(555, 0, 0), Vec3(0, 555, 0),
      std::make_shared<Lambertian>(Color(.73, .73, .73))));

  // Box in foreground
  std::unique_ptr<Hittable> foreground_box =
      std::make_unique<Box>(Point3(0, 0, 0), Point3(165, 165, 165), white);
  foreground_box = std::make_unique<Translation>(std::move(foreground_box),
                                                 Vec3(130, 0, 65));
  // foreground_box = std::make_unique<Rotation>(std::move(foreground_box),
  // -18.0);
  hittables.add(std::move(foreground_box));

  // Box in background
  std::unique_ptr<Hittable> background_box =
      std::make_unique<Box>(Point3(0, 0, 0), Point3(165, 330, 165), white);
  background_box = std::make_unique<Translation>(std::move(background_box),
                                                 Vec3(265, 0, 295));
  // background_box =
  // std::make_unique<Rotation>(std::move(background_box), 15.0);
  hittables.add(std::move(background_box));

  hittables.InitBvhTree();

  // Camera
  Point3 camera_center(278, 278, -800);
  Point3 focal_point(278, 278, 0);
  Camera camera(camera_center, focal_point,
                /*focal distance*/
                Point3(camera_center - constants::camera::FOCAL_POINT).norm(),
                /*FoV*/ 40, constants::camera::IMAGE_WIDTH,
                /*aspect width*/ 1.0,
                /*aspect height*/ 1.0);
  camera.Render(hittables);
}

int main() {
  int i = 5;
  switch (i) {
    case 0:
      RenderBouncingSpheres();
      break;
    case 1:
      RenderCheckeredSpheres();
      break;
    case 2:
      RenderEarth();
      break;
    case 3:
      RenderQuads();
      break;
    case 4:
      RenderSimpleLight();
      break;
    case 5:
      RenderCornellBox();
      break;
  }
}
