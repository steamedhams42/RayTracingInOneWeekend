#ifndef DIFFUSE_LIGHT_H
#define DIFFUSE_LIGHT_H

#include <memory>

#include "InOneWeekendJeff/color.h"
#include "InOneWeekendJeff/geometry/point3.h"
#include "InOneWeekendJeff/materials/material.h"
#include "InOneWeekendJeff/textures/texture.h"

class DiffuseLight : public Material {
 public:
  DiffuseLight(const Color& color, double intensity = 1.0);

  // Emits a color with no reflection as a light source does.
  Color Emit(double u, double v, const Point3& p) const override;

 private:
  DiffuseLight(std::unique_ptr<Texture> texture);

  std::unique_ptr<Texture> texture_;
};

#endif