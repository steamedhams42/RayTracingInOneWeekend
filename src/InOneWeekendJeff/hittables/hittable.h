#ifndef HITTABLE_H
#define HITTABLE_H

#include "InOneWeekendJeff/bounding_box.h"
#include "InOneWeekendJeff/geometry/point3.h"
#include "InOneWeekendJeff/geometry/vec3.h"
#include "InOneWeekendJeff/interval.h"

class Ray;
class Material;

class Hittable {
 public:
  class HitResult {
   public:
    // This struct encapsulates the parameters that define a ray's point of
    // intersection on a Hittable object based on the following equation where
    // Q is the origin, t is the scale factor, d is the vector of the ray.
    // P(t) = Q + t*d

    // The point at which a ray hits the Hittable.
    Point3 incident_point;

    // The normalized vector on the surface of the hittable at the point of
    // intersection with a light ray. May be negative if the light source is on
    // the inside of the surface. See front_face.
    Vec3 normal;

    // The scale factor of the ray that hits the Hittable.
    double t;

    // Surface coordinates of the ray-object hitpoint for projection mapping.
    // (u, v) <=> (x, y, z)
    // https://en.wikipedia.org/wiki/UV_mapping
    double u, v;

    // Front face refers to the origin of the ray source. If the ray originated
    // from outside the surface, front face == true.
    bool front_face;

    // Determines if the ray is external or internal. For this class, I have
    // chosen to make the hittable's normal vectors always oppose the incident
    // light ray.
    void SetFaceNormal(const Ray& ray, const Vec3& outward_normal);

    const Material* material = nullptr;
  };

  virtual ~Hittable() = default;

  virtual bool Hit(const Ray& incident_ray,
                   Interval ival,
                   Hittable::HitResult& result) const = 0;

  virtual BoundingBox bounding_box() = 0;
};

#endif