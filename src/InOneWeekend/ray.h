#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include "point3.h"

class Ray {
public:
    Ray(Point3, Vec3);
    Ray() = default;
    Ray(const Ray&) = default;
    Ray& operator=(Ray&) = default;
    ~Ray() = default;

    const Point3& origin() const;
    const Vec3& direction() const;

    Point3 at(double t) const;

private:
    Point3 origin_;
    Vec3 dir_;

};

#endif