#ifndef DIFFUSE_LIGHT_H
#define DIFFUSE_LIGHT_H

#include <memory>

#include "InOneWeekendJeff/color.h"
#include "InOneWeekendJeff/materials/material.h"
#include "InOneWeekendJeff/point3.h"
#include "InOneWeekendJeff/textures/texture.h"

class DiffuseLight : public Material {
 public:
  DiffuseLight(const Color& color, double intensity = 1.0);

  Color Emit(double u, double v, const Point3& p) const override;

  // Changes the intensity of the light source.
  void set_intensity(double i);

 private:
  DiffuseLight(std::unique_ptr<Texture> texture, double i);

  std::unique_ptr<Texture> texture_;
  double intensity_;
};

#endif