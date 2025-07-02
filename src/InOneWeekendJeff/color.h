#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "InOneWeekendJeff/geometry/point3.h"

class Color : public Point3 {
 public:
  Color() : Point3() {}
  Color(Point3 p);
  Color(double r, double g, double b);
  Color(const Color& p) = default;
  Color(Color&& p) = default;
  Color& operator=(const Color& p) = default;
  Color& operator=(Color&& p) = default;

  double r() const { return x(); }
  double g() const { return y(); }
  double b() const { return z(); }

  void write_color(std::ostream& out);

  static Color random_color();

  Color operator+(const Color& rhs);
  Color& operator+=(const Color& rhs);

  Color operator*(double t);
  Color operator*(const Color&);
  Color& operator*=(double t);
  friend Color operator*(double t, const Color& lhs);

  Color operator/(double t);
  Color& operator/=(double t);

  bool operator==(const Color& lhs) const;

 private:
  double linear_to_gamma(double linear_component);
};

inline Color operator*(double t, const Color& lhs) {
  return lhs * t;
}

#endif