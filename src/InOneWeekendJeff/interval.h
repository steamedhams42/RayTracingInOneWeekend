#ifndef INTERVAL_H
#define INTERVAL_H

class Interval {
 public:
  Interval();
  Interval(double, double);
  Interval(const Interval&) = default;
  Interval(Interval&&) = default;
  Interval& operator=(const Interval&) = default;
  Interval& operator=(Interval&& rhs) = default;
  ~Interval() = default;

  friend bool operator==(const Interval& lhs, const Interval& rhs);

  double min() const;
  double max() const;

  void set_min(double x);
  void set_max(double x);

  double width() const;

  // Inclusive [min, max]
  bool contains(double) const;

  // Exclusive (min, max)
  bool surrounds(double) const;

  // Returns x bounded by [min, max]
  double clamp(double x) const;

  // Returns a new Interval padded by delta, [min - delta, max + delta]
  Interval expand(double delta);

  // An empty interval has a larger min than max
  bool is_empty();

 private:
  double min_;
  double max_;
};

inline bool operator==(const Interval& lhs, const Interval& rhs) {
  return lhs.min_ == rhs.min_ and lhs.max_ == rhs.max_;
}

#endif