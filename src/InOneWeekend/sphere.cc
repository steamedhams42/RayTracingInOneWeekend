#include "sphere.h"

bool Sphere::hit(const Ray& r,
                 double ray_tmin,
                 double ray_tmax,
                 HitRecord& rec) const {
  return false;
}

Sphere::~Sphere() {}