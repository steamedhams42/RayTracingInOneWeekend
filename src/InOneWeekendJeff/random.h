#ifndef RANDOM_H
#define RANDOM_H

class Random {
 public:
  Random() = delete;

  // Returns a real number between [0, 1.0)
  static double random_real();

  // Returns a real number between [min, max)
  static double random_real(double min, double max);

  // Returns an integer between [min, max)
  static int random_int(int min, int max);
};

#endif