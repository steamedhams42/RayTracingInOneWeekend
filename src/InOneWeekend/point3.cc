#include "point3.h"

#include<cmath>

double Point3::operator[](int i) const {
    return points_[i];
}

Point3& Point3::operator+=(const Point3& rhs) {
    this->points_[0] += rhs.points_[0];
    this->points_[1] += rhs.points_[1];
    this->points_[2] += rhs.points_[2];
    return *this;
}
// Scaling
Point3& Point3::operator*=(double t) {
    this->points_[0] *= t;
    this->points_[1] *= t;
    this->points_[2] *= t;
    return *this;
}
// 1 / Scaling
Point3& Point3::operator/=(double t) {
    return *this *= (1 / t);
}

// Negation
Point3 Point3::operator-() const {
    return Point3(-points_[0], -points_[1], -points_[2]);
}

double Point3::norm() {
    return sqrt(norm_squared());
}

double Point3::norm_squared() {
    return points_[0] * points_[0]
    + points_[1] * points_[1]
    + points_[2] * points_[2];
}
