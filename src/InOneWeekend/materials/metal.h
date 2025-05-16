#ifndef METAL_H
#define METAL_H

#include "InOneWeekend/color.h"
#include "InOneWeekend/materials/material.h"

// Uses ocular reflectance
// https://en.wikipedia.org/wiki/Specular_reflection#Vector_formulation
class Metal : public Material {
 public:
  Metal(const Color& albedo) : albedo_(albedo) {}

  bool scatter(const Ray& incident_ray,
               const Hittable::HitResult& result,
               Color& attenuation,
               Ray& scattered) const override {
    Vec3 reflected_vec = Vec3::reflect(incident_ray.direction(), result.normal);
    attenuation = albedo_;
    scattered = Ray(result.p, reflected_vec);
    return true;
  }

 private:
  Color albedo_;
};

#endif