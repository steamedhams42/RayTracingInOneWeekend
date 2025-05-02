#ifndef TEST_BASE_H
#define TEST_BASE_H

#include "InOneWeekend/point3.h"
#include "InOneWeekend/random.h"
#include "InOneWeekend/vec3.h"

#define ASSERT(condition, message)                               \
  do {                                                           \
    if (!(condition)) {                                          \
      std::cerr << "Assertion failed: " << message << std::endl; \
      std::exit(EXIT_FAILURE);                                   \
    }                                                            \
  } while (false)

class TestBase {
 public:
  virtual ~TestBase() = default;

  virtual void run_test() = 0;

 protected:
  static constexpr double EPS = 1e-5;

  Point3 createPoint() {
    RandomNumber rand;
    double a = 0, b = 0, c = 0;
    a = rand.random_real();
    b = rand.random_real();
    c = rand.random_real();
    return Point3(a, b, c);
  }

  Vec3 createVec() {
    RandomNumber rand;
    double a = 0, b = 0, c = 0;
    a = rand.random_real();
    b = rand.random_real();
    c = rand.random_real();
    return Vec3(a, b, c);
  }
};

#endif