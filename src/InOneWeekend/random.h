#ifndef RANDOM_H_
#define RANDOM_H_

#include <random>
#include "vec3.h"

class Random {
 public:
  Random() = delete;

  // Returns a real number between [0, 1.0)
  static double random_real() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
  }

  static double random_real(double min, double max) {
    return ((max - min) * random_real()) + min;
  }

  static Vec3 random_vec3() {
    return Vec3(Random::random_real(), Random::random_real(),
                Random::random_real());
  }

  static Vec3 random_vec3(double min, double max) {
    return Vec3(Random::random_real(min, max), Random::random_real(min, max),
                Random::random_real(min, max));
  }
};

#endif