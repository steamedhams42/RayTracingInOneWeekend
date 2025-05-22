#include "InOneWeekendJeff/materials/metal.h"

#include "InOneWeekendJeff/color.h"

Metal::Metal() : albedo_(Color(0.8, 0.8, 0.8)) {}

Metal::Metal(const Color& albedo) : albedo_(albedo) {}

Metal::~Metal() = default;

bool Metal::scatter(const Ray& incident_ray,
                    const Hittable::HitResult& result,
                    Color& attenuation,
                    Ray& scattered) const {
  Vec3 reflected_vec = reflect(incident_ray.direction(), result.normal);
  attenuation = albedo_;
  scattered = Ray(result.p, reflected_vec);
  return true;
}

// Returns a specular/regular reflected vector off a surface.
// https://en.wikipedia.org/wiki/Specular_reflection#Vector_formulation
Vec3 Metal::reflect(const Vec3& incident, const Vec3& surface_norm) const {
  return incident - 2 * (incident.dot(surface_norm)) * surface_norm;
}