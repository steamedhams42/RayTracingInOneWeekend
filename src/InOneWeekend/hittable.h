#ifndef HITTABLE_H
#define HITTABLE_H

#include "point3.h"
#include "vec3.h"

class Ray;

class Hittable {
 public:
  class HitResult {
   public:
    // This struct encapsulates the parameters that define a ray's point of
    // intersection on a Hittable object based on the following equation:
    // P(t) = O + t*d
    // Where O is the origin, t is the scale factor, d is the vector of the ray.

    // The point at which a ray hits the Hittable.
    Point3 p;

    // The normalized vector on the surface of the hittable at the point of
    // intersection with a light ray. May be negative if the light source is on
    // the inside of the surface. See front_face.
    Vec3 normal;

    // The scale factor of the ray that hits the Hittable.
    double t;

    // Front face refers to the origin of the ray source. If the ray originated
    // from outside the surface, front face == true.
    bool front_face;

    // Determines if the ray is external or internal. For this class, I have
    // chosen to make the hittable's normal vectors always oppose the incident
    // light ray.
    void setFaceNormal(const Ray& ray, const Vec3& outward_normal);
  };

  virtual ~Hittable() = default;

  // TODO: Refactor into a template method.
  virtual bool hit(const Ray& ray,
                   double ray_tmin,
                   double ray_tmax,
                   HitResult& result) const = 0;
};

#endif