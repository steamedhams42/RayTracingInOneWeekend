#ifndef METAL_H
#define METAL_H

#include "InOneWeekend/color.h"
#include "InOneWeekend/materials/material.h"

// Uses ocular reflectance
// https://en.wikipedia.org/wiki/Specular_reflection#Vector_formulation
class Metal : public Material {
 public:
  // Default c'tor is chrome color.
  Metal() : albedo_(Color(0.8, 0.8, 0.8)) {}
  Metal(const Color& albedo) : albedo_(albedo) {}
  ~Metal() = default;

  bool scatter(const Ray& incident_ray,
               const Hittable::HitResult& result,
               Color& attenuation,
               Ray& scattered) const override {
    Vec3 reflected_vec = reflect(incident_ray.direction(), result.normal);
    attenuation = albedo_;
    scattered = Ray(result.p, reflected_vec);
    return true;
  }

 private:
  // Returns a specular/regular reflected vector off a surface.
  // https://en.wikipedia.org/wiki/Specular_reflection#Vector_formulation
  Vec3 reflect(const Vec3& incident, const Vec3& surface_norm) const {
    return incident - 2 * (incident.dot(surface_norm)) * surface_norm;
  }

  Color albedo_;
};

#endif