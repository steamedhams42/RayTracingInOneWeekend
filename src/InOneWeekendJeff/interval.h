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

  // Returns a new Interval padded by delta, [min - delta, max + delta]
  Interval expand(double delta);

  // Useful for comparisons
  static const Interval empty;
  static const Interval universal;

 private:
  double min_;
  double max_;
};

#endif