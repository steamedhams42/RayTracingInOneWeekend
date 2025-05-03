#include "color.h"

#include <cassert>
#include <iostream>

#include "constants.h"
#include "interval.h"
#include "point3.h"

Color::Color(Point3 p) : Point3(p) {
  assert(0.0 <= r() and r() <= 1.0);
  assert(0.0 <= g() and g() <= 1.0);
  assert(0.0 <= b() and b() <= 1.0);
}

Color::Color(double x, double y, double z) : Point3(x, y, z) {
  assert(0.0 <= r() and r() <= 1.0);
  assert(0.0 <= g() and g() <= 1.0);
  assert(0.0 <= b() and b() <= 1.0);
}

double Color::linear_to_gamma(double linear_component) {
  if (linear_component > 0) {
    return std::sqrt(linear_component);
  }
  return 0;
}

void Color::write_color(std::ostream& out) {
  // Rescale from [0, 255]
  Interval intv(0, 1);
  int iR = int(intv.clamp(linear_to_gamma(r())) * (constants::BYTE - 1));
  int iG = int(intv.clamp(linear_to_gamma(g())) * (constants::BYTE - 1));
  int iB = int(intv.clamp(linear_to_gamma(b())) * (constants::BYTE - 1));

  out << iR << ' ' << iG << ' ' << iB << '\n';
}

Color Color::operator+(const Color& rhs) {
  return Color(r() + rhs.r(), g() + rhs.g(), b() + rhs.b());
}

Color& Color::operator+=(const Color& rhs) {
  points_[0] += rhs.r();
  points_[1] += rhs.g();
  points_[2] += rhs.b();
  return *this;
}

Color Color::operator*(double t) {
  return Color(r() * t, g() * t, b() * t);
}

Color& Color::operator*=(double t) {
  points_[0] *= t;
  points_[1] *= t;
  points_[2] *= t;
  return *this;
}

Color Color::operator/(double t) {
  return *this * (1 / t);
}

Color& Color::operator/=(double t) {
  return *this *= (1 / t);
}

bool Color::operator==(const Color& rhs) const {
  return (Point3) * this == (Point3)rhs;
}
