#pragma once
#include "NelderMeadSimplex.hpp"
#include "Utils.hpp"
#include <cmath>
#include <functional>
#include <random>

using namespace std;

using Functions = vector<function<double(const Point& p)> >;

double slog(double x)
{
  return x > 0.0 ? log(x) : -1.0e10;
}

template <class Function>
Point TransformToBoundless(const Point& X0, double r, Function& f, Functions& g, Functions& h, double eps)
{
  auto U = [&](const Point& X) {
    double sumg = 0.0;
    for (const auto& gi : g)
      sumg += slog(gi(X));

    double sumh = 0.0;
    for (const auto& hi : h) {
      const double hiX = hi(X);
      sumh += hiX * hiX;
    }

    return f(X) - r * sumg + sumh / r;
  };

  const double alpha = 1.0;
  const double beta = -0.5;
  const double gamma = 2.0;
  const double sigma = -0.5;
  const double step = 1.0;

  Point Xold(X0.size(), 1.0e10);
  Point Xnew(X0);
  while (dist(Xnew, Xold) > eps) {
    Xold = Xnew;
    Xnew = NelderMeadSimplex(Xnew, alpha, beta, gamma, step, sigma, U, eps);
    r /= 10.0;
    //cout << Xnew << endl;
  }
  return Xnew;
}
