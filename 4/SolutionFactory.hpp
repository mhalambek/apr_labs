#pragma once
#include <iostream>
#include <vector>

using namespace std;

template <typename S, typename T>
struct SolutionFactory {
  vector<T> min, max;

  SolutionFactory(T _max, T _min)
      : max{ vector<T>(S::dim, _max) }
      , min{ vector<T>(S::dim, _min) } {};

  S operator()(void)
  {
    return S(max, min);
  };
};
