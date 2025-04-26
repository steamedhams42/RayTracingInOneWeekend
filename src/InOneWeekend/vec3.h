#ifndef VEC3_H
#define VEC3_H

#include "point3.h"

class Vec3Test;

class Vec3 : public Point3 {
 public:
  Vec3() : Point3{0, 0, 0} {}
  Vec3(double x, double y, double z) : Point3{x, y, z} {}
  Vec3(const Point3& p) : Point3(p) {}
  ~Vec3() = default;

  Vec3 operator+(const Vec3& rhs);
  Vec3& operator+=(const Vec3& rhs);

  Vec3& operator-();
  Vec3 operator-(const Vec3& rhs);
  Vec3& operator-=(const Vec3& rhs);

  Vec3 operator*(double t) const;
  Vec3& operator*=(double t);
  friend Vec3& operator*=(double t, Vec3& rhs);

  Vec3 operator/(double t) const;
  Vec3& operator/=(double t);

  double dot(const Vec3& rhs) const;
  Vec3 cross(const Vec3& rhs) const;

  // Returns |this| vector normalized
  Vec3 unit() const;

 private:
  friend Vec3Test;
};

inline Vec3 operator*(double t, Vec3 v) {
  return v * t;
}

inline Vec3& operator*=(double t, Vec3& rhs) {
  return rhs *= t;
}

inline Vec3 operator/(double t, const Vec3 v) {
  return (1 / t) * v;
}

#endif
