#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "InOneWeekend/color.h"
#include "InOneWeekend/hittable.h"
#include "InOneWeekend/materials/material.h"
#include "InOneWeekend/vec3.h"

// Reflects light slightly randomly giving objects a matte look.
// https://en.wikipedia.org/wiki/Lambertian_reflectance
class Lambertian : public Material {
 public:
  Lambertian() : albedo_(Color(0.5, 0.5, 0.5)) {}
  Lambertian(const Color& albedo) : albedo_(albedo) {}
  ~Lambertian() = default;

  bool scatter(const Ray& incident_ray,
               const Hittable::HitResult& hit_result,
               Color& attenuation,
               Ray& scattered) const override {
    auto v = Vec3::random_unit_vec3() + hit_result.normal;
    if (v.is_near_zero()) {
      v = hit_result.normal;
    }
    scattered = Ray(hit_result.p, v);
    attenuation = albedo_;
    return true;
  }

 private:
  Color albedo_;
};

#endif