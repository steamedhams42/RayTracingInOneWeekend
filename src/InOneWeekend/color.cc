#include "color.h"

#include <cassert>
#include "constants.h"

Color::Color() : Point3() {}

Color::Color(double r, double g, double b) {
  assert(0 <= r and r <= 1.0);
  assert(0 <= g and g <= 1.0);
  assert(0 <= b and b <= 1.0);
  points_[0] = r;
  points_[1] = g;
  points_[2] = b;
}

std::ostream& operator<<(std::ostream& out, const Color& c) {
  double R = c.x();
  double G = c.y();
  double B = c.z();

  int iR = int(R * constants::BYTE);
  int iG = int(G * constants::BYTE);
  int iB = int(B * constants::BYTE);

  return out << iR << ' ' << iG << ' ' << iB << '\n';
}
