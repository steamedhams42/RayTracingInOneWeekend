#include "InOneWeekendJeff/utils.h"

#include <cassert>

#include "test_base.h"

class RandomTest : public TestBase {
 public:
  void RunTest() override {
    for (int i = 0; i < 100; i++) {
      auto x = utils::Random::random_real(-10, 0);
      assert(x < 0);
      assert(x > -10);
    }

    for (int i = 0; i < 100; i++) {
      auto x = utils::Random::random_real(0, 100);
      assert(x > 0);
      assert(x < 100);
    }

    for (int i = 0; i < 100; i++) {
      auto x = utils::Random::random_real();
      assert(x > 0);
      assert(x < 1);
    }

    for (int i = 0; i < 100; i++) {
      auto x = utils::Random::random_real(-1, 1);
      assert(x > -1);
      assert(x < 1);
    }

    for (int j = 0; j < 100; j++) {
      int x = utils::Random::random_int(0, 1);
      assert(x == 1 or x == 0);
    }
  }
};