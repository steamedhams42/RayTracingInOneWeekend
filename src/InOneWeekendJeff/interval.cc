#include "interval.h"

#include "constants.h"

const Interval Interval::empty = Interval();
const Interval Interval::universal =
    Interval(-constants::INF_DOUBLE, constants::INF_DOUBLE);

// Default interval is empty
Interval::Interval()
    : min_(constants::INF_DOUBLE), max_(-constants::INF_DOUBLE) {}

Interval::Interval(double min, double max) : min_(min), max_(max) {}

double Interval::width() const {
  return max_ - min_;
}

bool Interval::contains(double x) const {
  return (min_ <= x) and (x <= max_);
}

bool Interval::surrounds(double x) const {
  return (min_ < x) and (x < max_);
}

double Interval::clamp(double x) const {
  if (x < min_) {
    return min_;
  }
  if (x > max_) {
    return max_;
  }
  return x;
}

Interval Interval::expand(double delta) {
  return Interval(min_ - delta, max_ + delta);
}
