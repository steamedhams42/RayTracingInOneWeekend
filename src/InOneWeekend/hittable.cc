#include "hittable.h"
#include "ray.h"

void Hittable::HitResult::setFaceNormal(const Ray& ray,
                                        const Vec3& outward_normal) {
  if (ray.direction().dot(outward_normal) > 0) {
    // Positive dot product means the ray source is on the inside of the
    // hittable.
    this->front_face = false;
    this->normal = -outward_normal;
  } else {
    // Negative dot means the ray source is external to the surface.
    this->normal = outward_normal;
    this->front_face = true;
  }
}