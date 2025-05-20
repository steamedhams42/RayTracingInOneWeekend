#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "InOneWeekend/materials/material.h"

class Ray;
class Color;
class Vec3;
class Hittable;

// Dielectrics bend light (e.g. glass, water, diamond) according to Snell's law
// https://en.wikipedia.org/wiki/Snell%27s_law#Vector_form
class Dielectric : public Material {
 public:
  Dielectric() = default;
  Dielectric(const double refraction_index);
  ~Dielectric() = default;

  bool scatter(const Ray& incident_ray,
               const Hittable::HitResult& result,
               Color& attenuation,
               Ray& scattered) const;

 private:
  Vec3 refract(const Vec3& uv,
               const Vec3& n,
               double ingress_over_egress_refractive_index_ratio) const;

  double refraction_index_ = 1.0;
};

#endif