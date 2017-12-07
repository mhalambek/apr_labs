#pragma once
#include "FunctionCounter.hpp"

template <typename S>
struct EvaluatedSolution {
  S sol;
  double fitness;
  double fuctionValue;
  EvaluatedSolution(S _sol, FunctionCounter& fn)
      : sol{ _sol }
  {
    fuctionValue = fn(sol);
  };
};
