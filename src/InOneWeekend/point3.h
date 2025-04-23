#ifndef POINT3_H
#define POINT3_H

#include <iostream>

class Point3 {
private:
    double points_[3];

public:
    Point3() : points_{0, 0, 0} {}
    Point3(double x, double y, double z) : points_{x, y, z} {}
    Point3(const Point3&) = default;
    Point3 operator=(const Point3&);
    ~Point3() = default;

    double x() const { return this->points_[0]; }
    double y() const { return this->points_[1]; }
    double z() const { return this->points_[2]; }

    double operator[](int i) const;

    Point3& operator+=(const Point3& rhs);

    // Scaling
    Point3& operator*=(double t);
    // 1 / Scaling
    Point3& operator/=(double t);
    // Negation
    Point3 operator-() const;

    double norm();
    double norm_squared();

    friend std::ostream& operator<<(std::ostream& out, const Point3& p) {
        return out << p.x() << ' ' << p.y() << ' ' << p.z();
    }

};

#endif