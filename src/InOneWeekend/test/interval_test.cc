#include "InOneWeekend/interval.h"
#include "InOneWeekend/constants.h"
#include "test_base.h"

#include <cassert>

class IntervalTest : public TestBase {
 public:
  void run_test() override {
    auto null = Interval::empty;

    double mini = -random_real();
    double maxi = random_real();

    Interval intvl(mini, maxi);

    for (double i = mini; i <= maxi; i += ((maxi - mini) / 100.0)) {
      std::cout << i << std::endl;
      assert(intvl.contains(i));
    }

    assert(intvl.contains(mini));
    assert(intvl.contains(maxi));

    assert(!intvl.surrounds(mini));
    assert(!intvl.surrounds(maxi));
  }
};