#ifndef INTERVAL_H
#define INTERVAL_H

#include <iostream>

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
  friend Interval operator+(const Interval& lhs, double displacement);
  friend Interval operator+(double displacement, const Interval& lhs);

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

  // Sorted by smallest min_ then max_
  bool operator<(const Interval& rhs) const;

  // Returns a new interval using the smallest min and largest max between them.
  static Interval EncloseTwoIntervals(const Interval& lhs, const Interval& rhs);

 private:
  double min_;
  double max_;

  friend std::ostream& operator<<(std::ostream& out, const Interval& ival) {
    return out << ival.min() << ", " << ival.max() << std::endl;
  }
};

inline bool operator==(const Interval& lhs, const Interval& rhs) {
  return lhs.min_ == rhs.min_ and lhs.max_ == rhs.max_;
}

inline Interval operator+(const Interval& lhs, double displacement) {
  return Interval(lhs.min() + displacement, lhs.max() + displacement);
}

inline Interval operator+(double displacement, const Interval& lhs) {
  return lhs + displacement;
}

#endif