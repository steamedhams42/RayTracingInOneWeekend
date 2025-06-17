#include "InOneWeekendJeff/random.h"

#include <random>

// static
double Random::random_real() {
  static std::uniform_real_distribution<double> distribution(0.0, 1.0);
  static std::mt19937 generator;
  return distribution(generator);
}

// static
double Random::random_real(double min, double max) {
  return ((max - min) * random_real()) + min;
}

// static
int Random::random_int(int min, int max) {
  return (int)random_real(min, max + 1);
}
