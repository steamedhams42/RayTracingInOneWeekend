#include "InOneWeekendJeff/test/camera_test.cc"
#include "InOneWeekendJeff/test/interval_test.cc"
#include "InOneWeekendJeff/test/lambertian_test.cc"
#include "InOneWeekendJeff/test/metal_test.cc"
#include "InOneWeekendJeff/test/point3_test.cc"
#include "InOneWeekendJeff/test/random_test.cc"
#include "InOneWeekendJeff/test/ray_test.cc"
#include "InOneWeekendJeff/test/sphere_test.cc"
#include "InOneWeekendJeff/test/vec3_test.cc"

int main() {
  Point3Test point_test;
  point_test.run_test();

  Vec3Test vec3_test;
  vec3_test.run_test();

  RayTest ray_test;
  ray_test.run_test();

  SphereTest sphere_test;
  sphere_test.run_test();

  IntervalTest interval_test;
  interval_test.run_test();

  CameraTest camera_test;
  camera_test.run_test();

  RandomTest random_test;
  random_test.run_test();

  LambertianTest lambertian_test;
  lambertian_test.run_test();

  MetalTest metal_test;
  metal_test.run_test();

  return 0;
}