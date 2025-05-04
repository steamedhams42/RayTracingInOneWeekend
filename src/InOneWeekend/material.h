#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"
#include "hittable.h"
#include "ray.h"

class Material {
 public:
  virtual ~Material() = default;
  virtual bool scatter(const Ray& r_in,
                       const Hittable::HitResult& result,
                       Color& attenuation,
                       Ray& scattered) const {
    return false;
  }
};

#endif