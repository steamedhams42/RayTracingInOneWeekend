#ifndef POINT3_H
#define POINT3_H

#include <iostream>

class Point3Test;

class Point3 {
 private:
  static const int DIMENSIONS = 3;

 public:
  Point3() : points_{0, 0, 0} {}
  Point3(double x, double y, double z) : points_{x, y, z} {}
  Point3(const Point3&) = default;
  ~Point3() = default;

  double x() const { return this->points_[0]; }
  double y() const { return this->points_[1]; }
  double z() const { return this->points_[2]; }

  double operator[](int i) const;

  double norm() const;
  double norm_squared() const;

  friend Point3 operator+(const Point3& lhs, const Point3& rhs);
  friend Point3& operator+=(Point3& lhs, const Point3& rhs);

  friend Point3 operator-(const Point3& lhs, const Point3& rhs);
  friend Point3& operator-=(Point3& lhs, const Point3& rhs);

  friend Point3 operator*(const Point3& lhs, double t);
  friend Point3 operator*(double t, const Point3& lhs);
  friend Point3& operator*=(Point3& lhs, double t);

  friend Point3 operator/(const Point3& lhs, double t);
  friend Point3& operator/=(Point3& lhs, double t);

  friend bool operator==(const Point3& lhs, const Point3& rhs);

  friend Point3 operator-(const Point3& lhs);

  friend std::ostream& operator<<(std::ostream& out, const Point3& p) {
    return out << p.x() << ' ' << p.y() << ' ' << p.z();
  }

 protected:
  double points_[DIMENSIONS];

 private:
  friend Point3Test;
};

inline Point3 operator+(const Point3& lhs, const Point3& rhs) {
  return Point3(lhs.x() + rhs.x(), lhs.y() + rhs.y(), lhs.z() + rhs.z());
}

inline Point3& operator+=(Point3& lhs, const Point3& rhs) {
  lhs.points_[0] += rhs.points_[0];
  lhs.points_[1] += rhs.points_[1];
  lhs.points_[2] += rhs.points_[2];
  return lhs;
}

inline Point3 operator-(const Point3& lhs, const Point3& rhs) {
  return lhs + -rhs;
}

inline Point3& operator-=(Point3& lhs, const Point3& rhs) {
  return lhs += -rhs;
}

inline Point3 operator*(const Point3& lhs, double t) {
  return Point3(t * lhs.x(), t * lhs.y(), t * lhs.z());
}

inline Point3 operator*(double t, const Point3& lhs) {
  return lhs * t;
}

inline Point3& operator*=(Point3& lhs, double t) {
  lhs.points_[0] *= t;
  lhs.points_[1] *= t;
  lhs.points_[2] *= t;
  return lhs;
}

inline Point3 operator/(const Point3& lhs, double t) {
  return lhs * (1 / t);
}

inline Point3& operator/=(Point3& lhs, double t) {
  return lhs *= (1 / t);
}

inline bool operator==(const Point3& lhs, const Point3& rhs) {
  bool res = true;
  for (int i = 0; i < Point3::DIMENSIONS; i++) {
    res &= lhs.points_[i] == rhs.points_[i];
  }
  return res;
}

// Negation
inline Point3 operator-(const Point3& lhs) {
  return Point3(-lhs.points_[0], -lhs.points_[1], -lhs.points_[2]);
}

#endif