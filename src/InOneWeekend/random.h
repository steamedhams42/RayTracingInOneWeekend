#ifndef RANDOM_H_
#define RANDOM_H_

#include <random>

class RandomNumber {
 public:
  RandomNumber() = delete;

  // Returns a real number between [0, 1.0)
  static double random_real() {
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
  }

  static double random_real(double l, double r) {
    return ((r - l) * random_real()) + l;
  }
};

#endif