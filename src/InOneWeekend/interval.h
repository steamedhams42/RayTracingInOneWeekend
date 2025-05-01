#ifndef INTERVAL_H
#define INTERVAL_H

class Interval {
 public:
  Interval();
  Interval(double, double);

  double min() const { return min_; }
  double max() const { return max_; }

  double width() const;
  // Inclusive
  bool contains(double) const;
  // Exclusive
  bool surrounds(double) const;

  static const Interval empty;
  static const Interval universal;

 private:
  double min_;
  double max_;
};

#endif