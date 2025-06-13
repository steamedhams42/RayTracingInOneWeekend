#include "interval.h"

#include "constants.h"

// Default interval is empty
Interval::Interval()
    : min_(constants::INF_DOUBLE), max_(-constants::INF_DOUBLE) {}

Interval::Interval(double min, double max) : min_(min), max_(max) {}

double Interval::min() const {
  return this->min_;
}

double Interval::max() const {
  return this->max_;
}

void Interval::set_min(double x) {
  this->min_ = x;
}

void Interval::set_max(double x) {
  this->max_ = x;
}

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

bool Interval::is_empty() {
  return min_ >= max_;
}

bool Interval::operator<(const Interval& rhs) const {
  return std::make_pair(this->min_, this->max_) <
         std::make_pair(rhs.min_, rhs.max_);
}
