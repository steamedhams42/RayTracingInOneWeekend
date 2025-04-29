#include "InOneWeekend/test/point3_test.cc"
#include "InOneWeekend/test/vec3_test.cc"

#include "InOneWeekend/test/ray_test.cc"

int main() {
  Point3Test point_test;
  point_test.run_test();

  Vec3Test vec3_test;
  vec3_test.run_test();

  RayTest ray_test;
  ray_test.run_test();

  return 0;
}