#include "InOneWeekendJeff/random.h"
#include "test_base.h"

#include <cassert>
#include "InOneWeekendJeff/interval.h"

class RandomTest : public TestBase {
 public:
  void RunTest() override {
    for (int i = 0; i < 100; i++) {
      auto x = Random::random_real(-10, 0);
      assert(x < 0);
      assert(x > -10);
    }

    for (int i = 0; i < 100; i++) {
      auto x = Random::random_real(0, 100);
      assert(x > 0);
      assert(x < 100);
    }

    for (int i = 0; i < 100; i++) {
      auto x = Random::random_real();
      assert(x > 0);
      assert(x < 1);
    }

    for (int i = 0; i < 100; i++) {
      auto x = Random::random_real(-1, 1);
      assert(x > -1);
      assert(x < 1);
    }
  }
};