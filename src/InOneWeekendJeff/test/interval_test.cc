#include "InOneWeekendJeff/interval.h"
#include "InOneWeekendJeff/constants.h"
#include "InOneWeekendJeff/random.h"
#include "test_base.h"

#include <cassert>

class IntervalTest : public TestBase {
 public:
  void RunTest() override {
    auto null = constants::interval::EMPTY;
    assert(null.is_empty());

    double mini = -Random::random_real();
    double maxi = Random::random_real();

    Interval ival(mini, maxi);

    for (double i = mini; i <= maxi; i += ((maxi - mini) / 100.0)) {
      assert(ival.contains(i));
    }

    assert(ival.contains(mini));
    assert(ival.contains(maxi));

    assert(!ival.surrounds(mini));
    assert(!ival.surrounds(maxi));

    assert(ival.clamp(mini - 10) == ival.min());
    assert(ival.clamp(maxi + maxi) == ival.max());

    double pad = 0.5;
    assert(ival.expand(pad).min() == ival.min() - pad);
    assert(ival.expand(pad).max() == ival.max() + pad);

    ival.set_min(1);
    ival.set_max(0);
    assert(ival.is_empty());

    // Test comparator is working
    ival = Interval(0, 1);
    Interval ival2(0, 2);
    Interval ival3(1, 2);
    assert(ival < ival2);
    assert(ival2 < ival3);
    assert(ival < ival3);

    Interval ival4 = Interval::EncloseTwoIntervals(ival, ival2);
    assert(ival4 == Interval(0, 2));
  }
};