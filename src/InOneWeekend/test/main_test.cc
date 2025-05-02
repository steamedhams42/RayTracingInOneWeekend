#include "InOneWeekend/test/camera_test.cc"
#include "InOneWeekend/test/interval_test.cc"
#include "InOneWeekend/test/point3_test.cc"
#include "InOneWeekend/test/ray_test.cc"
#include "InOneWeekend/test/sphere_test.cc"
#include "InOneWeekend/test/vec3_test.cc"

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

  return 0;
}