#include <iostream>

#include "InOneWeekend/test/point3_test.cc"
#include "InOneWeekend/test/vec3_test.cc"

int main() {
  Point3Test test;
  test.run_test();

  Vec3Test vec3_test;
  vec3_test.run_test();

  return 0;
}