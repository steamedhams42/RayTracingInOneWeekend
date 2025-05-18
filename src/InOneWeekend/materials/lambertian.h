#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "InOneWeekend/materials/material.h"

// Reflects light slightly randomly giving objects a matte look.
// https://en.wikipedia.org/wiki/Lambertian_reflectance
class Lambertian : public Material {
 public:
  Lambertian();
  Lambertian(const Color& albedo);
  ~Lambertian();

  bool scatter(const Ray& incident_ray,
               const Hittable::HitResult& hit_result,
               Color& attenuation,
               Ray& scattered) const override;

 private:
  Color albedo_;
};

#endif