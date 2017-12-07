#pragma once
#include "FunctionCounter.hpp"
#include "GoldenCut.hpp"
#include "utils.hpp"
#include <cassert>
#include <vector>

using namespace std;

template <class Function>
vector<double> coordsSearch(vector<double> x0, Function& func)
{
  vector<double> eps(x0.size(), 0.00001);

  return coordsSearch(func, x0, eps);
}
template <class Function>
vector<double> coordsSearch(Function& func, vector<double> x0, const vector<double>& epsilon)
{
  unsigned const int dim = x0.size();
  assert(dim <= epsilon.size());
  auto prev_x = x0;
  auto x = x0;

  do {
    prev_x = x;
    for (unsigned int i = 0; i < dim; ++i) {
      auto tx = x;
      auto lam = [&tx, &func, &i](vector<double> a) {
        tx[i] = a[0];
        return func(tx);
      };
      FunctionCounter fc = FunctionCounter(lam);
      x[i]
          = goldenSearch(x[i], fc);
    }
    // cout << "x: " << x << endl;
    // cout << "prev_x: " << prev_x << endl;
    // cout << vector_diff(x, prev_x) << endl;
  } while (vector_diff(x, prev_x));

  return x;
}
