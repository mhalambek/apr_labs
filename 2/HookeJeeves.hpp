#pragma once
#include "utils.hpp"
#include <iostream>
#include <vector>

using namespace std;

template <class Function>
vector<double> research(const vector<double>& xp, const vector<double> dx, Function& f)
{
  auto x = xp;
  assert(dx.size() == xp.size());
  for (unsigned int i = 0; i < x.size(); ++i) {
    double p = f(x);
    x[i] += dx[i];
    double n = f(x);
    if (n > p) {
      x[i] -= 2 * dx[i];
      n = f(x);
      if (n > p) {
        x[i] += dx[i];
      }
    }
  }

  return x;
}

template <class Function>
vector<double> HookeJeeves(vector<double> x0, Function& func, vector<double> dx)
{
  // cout << "dx" << endl
  //      << dx << endl;
  auto xp = x0;
  auto xb = x0;
  do {
    auto xn = research(xp, dx, func);
    if (func(xn) < func(xb)) {
      xp = (xn * 2) - xb;
      xb = xn;
    } else {
      for (auto& v : dx) {
        v *= v;
      }
      xp = xb;
    }

  } while (dx[0] > 0.00001);

  return xb;
}
template <class Function>
vector<double> HookeJeeves(vector<double> x0, Function& func)
{

  return HookeJeeves(x0, func, vector<double>(x0.size(), 0.5));
}
