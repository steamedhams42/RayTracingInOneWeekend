#ifndef RANDOM_H_
#define RANDOM_H_

#include <ctime>
#include <random>

class RandomNumber {
 public:
  RandomNumber() { std::srand(std::time(0)); }

  // Returns a real number between [0, 1.0)
  double random_real() { return 1.0 * (random() % md) / md; }

  double random_real(double l, double r) {
    double width = r - l;
    double x = width * random_real();
    return x + l;
  }

 private:
  const int md = 1e9 + 7;
};

#endif