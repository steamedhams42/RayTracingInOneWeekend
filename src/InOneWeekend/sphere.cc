#include "sphere.h"

#include <cassert>
#include "constants.h"
#include "ray.h"

Sphere::Sphere(Point3 center, double r) : center_(center), radius_(r) {
  assert(radius_ >= 0);
}

Sphere::~Sphere() {}

bool Sphere::hit(const Ray& ray,
                 double ray_tmin,
                 double ray_tmax,
                 Hittable::HitResult& result) const {
  Vec3 QC = constants::SPHERE_CENTER - ray.origin();
  double a = ray.direction().dot(ray.direction());
  double b = -2 * ray.direction().dot(QC);
  double c = QC.dot(QC) - constants::SPHERE_RADIUS * constants::SPHERE_RADIUS;
  double discriminant = b * b - 4 * a * c;
  if (discriminant < 0) {
    return false;
  }
  // Why (-b - sqrt(...))) instead of (-b + sqrt(...)), we want the closer
  // hitpoint of the sphere instead of the second exiting hitpoint.
  double t = (-b - std::sqrt(discriminant)) / (2 * a);
  result.t = t;
  result.p = ray.at(t);
  result.normal = (result.p - this->center_) / this->radius_;
  return true;
}
