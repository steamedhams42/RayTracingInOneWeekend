#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "constants.h"
#include "point3.h"

namespace color {

using Color = Point3;

void write_color(std::ostream& out, const Color& c) {
  double R = c.x();
  double G = c.y();
  double B = c.z();

  // Rescale from [0, 255]
  int iR = int(R * (constants::BYTE - 1));
  int iG = int(G * (constants::BYTE - 1));
  int iB = int(B * (constants::BYTE - 1));

  out << iR << ' ' << iG << ' ' << iB << '\n';
}

}  // namespace color

#endif