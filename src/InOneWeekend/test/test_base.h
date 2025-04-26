#ifndef TEST_BASE_H
#define TEST_BASE_H

#include <random>

const int md = 1e9 + 7;

class TestBase {
 public:
  TestBase() { std::srand(time(0)); }
  double random_real() { return 1.0 * (random() % md) / md; }
};

#endif