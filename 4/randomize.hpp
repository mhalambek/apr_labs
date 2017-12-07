#pragma once
#include "SolutionBit.hpp"
#include "SolutionDecimal.hpp"
#include <random>

random_device dev;

template <typename T>
void randomize(SolutionDecimal<T>& sol)
{
  for (unsigned int i = 0; i < sol.size(); ++i) {
    uniform_real_distribution<> dis(sol.min[i], sol.max[i]);
    sol.data[i] = dis(dev);
  }
}

template <typename T>
void randomize(SolutionBit<T>& sol)
{
  uniform_int_distribution<> dis(0, 1);
  for (auto& t : sol.data) {
    for (auto b : t) {
      b = dis(dev);
    }
  }
}
