#ifndef MATERIAL_H
#define MATERIAL_H

#include "InOneWeekendJeff/color.h"
#include "InOneWeekendJeff/geometry/ray.h"
#include "InOneWeekendJeff/hittables/hittable.h"

// Material class determines how a light reflects an incident ray.
// Subclasses of Material will implement different scattering methods e.g.
// Lambertian for a matte look or Metal for a highly reflective surface.
class Material {
 public:
  virtual ~Material() = default;

  // Subclasses overriding this method will take the reflected normal vector
  // from HitResult and decide how to reflect it based on the material.
  // Retuns true if incident ray was scattered, false if absorbed.
  virtual bool Scatter(const Ray& incident_ray,
                       const Hittable::HitResult& result,
                       Color& attenuation,
                       Ray& scattered) const {
    return false;
  }

  // Emittance is Color(0,0,0) for all non-diffuse materials.
  // Diffuse materials emit pure color e.g. a white light source Color(1, 1, 1).
  virtual Color Emit(double u, double v, const Point3& p) const {
    return Color();
  }
};

#endif