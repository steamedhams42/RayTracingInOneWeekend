#ifndef TEST_BASE_H
#define TEST_BASE_H

#include "InOneWeekendJeff/point3.h"
#include "InOneWeekendJeff/random.h"
#include "InOneWeekendJeff/vec3.h"

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
  Point3 createPoint() {
    double a = 0, b = 0, c = 0;
    a = Random::random_real();
    b = Random::random_real();
    c = Random::random_real();
    return Point3(a, b, c);
  }

  Vec3 createVec() {
    double a = 0, b = 0, c = 0;
    a = Random::random_real();
    b = Random::random_real();
    c = Random::random_real();
    return Vec3(a, b, c);
  }
};

#endif