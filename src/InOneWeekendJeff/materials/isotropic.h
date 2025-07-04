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

 private:
  std::unique_ptr<Texture> texture_;
};

#endif