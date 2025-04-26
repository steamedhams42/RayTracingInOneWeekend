#include "InOneWeekend/point3.h"
#include "InOneWeekend/test/test_base.h"

#include <cassert>
#include <iostream>

class Point3Test : public TestBase {
 public:
  void run_test() {
    Point3 u(1, 1, 1);

    std::srand(time(0));
    double a = 0, b = 0, c = 0;
    a = random_real();
    b = random_real();
    c = random_real();
    Point3 v(a, b, c);
    // std::cout << v << std::endl;
  }
};
