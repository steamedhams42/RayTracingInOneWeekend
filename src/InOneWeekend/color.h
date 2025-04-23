#ifndef COLOR_H
#define COLOR_H

#include "point3.h"

class Color : public Point3 {
private:
public:
    Color();
    Color(double r, double g, double b);

    friend std::ostream& operator<<(std::ostream& out, const Color& c);

};

#endif