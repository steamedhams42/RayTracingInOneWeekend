#ifndef INTERVAL_H
#define INTERVAL_H

class Interval {
 public:
  Interval();
  Interval(double, double);

  double min() const { return min_; }
  double max() const { return max_; }

  double width() const;

  // Inclusive [min, max]
  bool contains(double) const;

  // Exclusive (min, max)
  bool surrounds(double) const;

  // Returns x bounded by [min, max]
  double clamp(double x) const;

  static const Interval empty;
  static const Interval universal;

 private:
  double min_;
  double max_;
};

#endif