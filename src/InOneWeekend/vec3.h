#ifndef VEC3_H
#define VEC3_H

#include "point3.h"

class Vec3 : public Point3 {
private:

public:
    Vec3() : Point3{0, 0, 0} {}
    Vec3(double x, double y, double z) : Point3{x, y, z} {} 
    ~Vec3() = default;

    Vec3 operator+(const Vec3& rhs);
    Vec3 operator-(const Vec3& rhs);
    Vec3 operator*(const Vec3& rhs);
    Vec3 operator*(double t);
    Vec3 operator/(double t);
    double dot(const Vec3& rhs);
    Vec3 cross(const Vec3& rhs);
    Vec3 unit();

};

#endif
