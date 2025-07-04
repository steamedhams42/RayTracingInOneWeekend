#ifndef TEST_BASE_H
#define TEST_BASE_H

#include "InOneWeekendJeff/geometry/point3.h"
#include "InOneWeekendJeff/geometry/vec3.h"
#include "InOneWeekendJeff/utils.h"

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

  virtual void RunTest() = 0;

 protected:
  Point3 CreateRandomPoint() {
    double a = 0, b = 0, c = 0;
    a = utils::Random::random_real();
    b = utils::Random::random_real();
    c = utils::Random::random_real();
    return Point3(a, b, c);
  }

  Vec3 CreateRandomVec() {
    double a = 0, b = 0, c = 0;
    a = utils::Random::random_real();
    b = utils::Random::random_real();
    c = utils::Random::random_real();
    return Vec3(a, b, c);
  }
};

#endif