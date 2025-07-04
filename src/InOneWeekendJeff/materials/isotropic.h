#ifndef ISOTROPIC_H
#define ISOTROPIC_H

#include <memory>

#include "InOneWeekendJeff/color.h"
#include "InOneWeekendJeff/materials/material.h"
#include "InOneWeekendJeff/textures/texture.h"

class Isotropic : public Material {
 public:
  Isotropic(const Color& albedo);
  Isotropic(std::unique_ptr<Texture> texture);

  bool Scatter(const Ray& incident_ray,
               const Hittable::HitResult& result,
               Color& attenuation,
               Ray& scattered) const override;

 private:
  std::unique_ptr<Texture> texture_;
};

#endif