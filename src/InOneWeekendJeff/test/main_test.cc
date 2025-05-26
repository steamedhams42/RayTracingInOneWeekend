#include "InOneWeekendJeff/test/bounding_box_test.cc"
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
  point_test.RunTest();

  Vec3Test vec3_test;
  vec3_test.RunTest();

  RayTest ray_test;
  ray_test.RunTest();

  SphereTest sphere_test;
  sphere_test.RunTest();

  IntervalTest interval_test;
  interval_test.RunTest();

  CameraTest camera_test;
  camera_test.RunTest();

  RandomTest random_test;
  random_test.RunTest();

  LambertianTest lambertian_test;
  lambertian_test.RunTest();

  MetalTest metal_test;
  metal_test.RunTest();

  BoundingBoxTest bounding_box_test;
  bounding_box_test.RunTest();

  return 0;
}