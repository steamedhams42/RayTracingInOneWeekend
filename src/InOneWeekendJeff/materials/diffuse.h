#ifndef DIFFUSE_H
#define DIFFUSE_H

#include <memory>

#include "InOneWeekendJeff/color.h"
#include "InOneWeekendJeff/materials/material.h"
#include "InOneWeekendJeff/point3.h"
#include "InOneWeekendJeff/textures/texture.h"

class Diffuse : public Material {
 public:
  Diffuse(std::unique_ptr<Texture> texture);
  Diffuse(const Color& color);

  Color Emit(double u, double v, const Point3& p) const override;

 private:
  std::unique_ptr<Texture> texture_;
};

#endif