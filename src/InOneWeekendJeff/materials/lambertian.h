#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include <memory>

#include "InOneWeekendJeff/materials/material.h"
#include "InOneWeekendJeff/textures/texture.h"

// Reflects light slightly randomly giving objects a matte look.
// https://en.wikipedia.org/wiki/Lambertian_reflectance
class Lambertian : public Material {
 public:
  Lambertian();
  Lambertian(const Color&);
  Lambertian(std::unique_ptr<Texture> texture);
  ~Lambertian();

  bool Scatter(const Ray& incident_ray,
               const Hittable::HitResult& hit_result,
               Color& attenuation,
               Ray& scattered) const override;

 private:
  std::unique_ptr<Texture> albedo_;
};

#endif