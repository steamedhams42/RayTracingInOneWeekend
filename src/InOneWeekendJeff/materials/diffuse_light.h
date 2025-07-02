#ifndef DIFFUSE_LIGHT_H
#define DIFFUSE_LIGHT_H

#include <memory>

#include "InOneWeekendJeff/color.h"
#include "InOneWeekendJeff/materials/material.h"
#include "InOneWeekendJeff/point3.h"
#include "InOneWeekendJeff/textures/texture.h"

class DiffuseLight : public Material {
 public:
  DiffuseLight(std::unique_ptr<Texture> texture);
  DiffuseLight(const Color& color);

  Color Emit(double u, double v, const Point3& p) const override;

 private:
  std::unique_ptr<Texture> texture_;
};

#endif