#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <memory>
#include <vector>
#include "hittable.h"
#include "interval.h"
#include "ray.h"

class HittableList : public Hittable {
 public:
  HittableList();
  ~HittableList();

  void clearAll();
  void add(std::unique_ptr<Hittable>&&);

  bool hit(const Ray& ray,
           Interval i,
           Hittable::HitResult& result) const override;

 private:
  std::vector<std::unique_ptr<Hittable>> hittables_;
};

#endif