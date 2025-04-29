#ifndef TEST_BASE_H
#define TEST_BASE_H

#include <random>
#include "InOneWeekend/point3.h"
#include "InOneWeekend/vec3.h"

const int md = 1e9 + 7;

#define ASSERT(condition, message)                               \
  do {                                                           \
    if (!(condition)) {                                          \
      std::cerr << "Assertion failed: " << message << std::endl; \
      std::exit(EXIT_FAILURE);                                   \
    }                                                            \
  } while (false)

class TestBase {
 public:
  TestBase() { std::srand(time(0)); }
  virtual ~TestBase() = default;
  double random_real() { return 1.0 * (random() % md) / md; }

  virtual void run_test() = 0;

 protected:
  static constexpr double EPS = 1e-5;

  Point3 createPoint() {
    double a = 0, b = 0, c = 0;
    a = random_real();
    b = random_real();
    c = random_real();
    return Point3(a, b, c);
  }

  Vec3 createVec() {
    double a = 0, b = 0, c = 0;
    a = random_real();
    b = random_real();
    c = random_real();
    return Vec3(a, b, c);
  }
};

#endif