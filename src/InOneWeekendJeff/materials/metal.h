#ifndef METAL_H
#define METAL_H

#include "InOneWeekendJeff/materials/material.h"

// Uses ocular reflectance
// https://en.wikipedia.org/wiki/Specular_reflection#Vector_formulation
class Metal : public Material {
 public:
  // Default albedo is chrome-ish.
  Metal();
  Metal(const Color& albedo);
  ~Metal();

  bool Scatter(const Ray& incident_ray,
               const Hittable::HitResult& result,
               Color& attenuation,
               Ray& scattered) const override;

 private:
  // Returns a specular/regular reflected vector off a surface.
  // https://en.wikipedia.org/wiki/Specular_reflection#Vector_formulation
  Vec3 Reflect(const Vec3& incident, const Vec3& surface_norm) const;

  Color albedo_;
};

#endif