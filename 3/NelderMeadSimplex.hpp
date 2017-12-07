#pragma once
#include "Utils.hpp"

Point MovedPoint(const Point& C, double factor, const Point& X);

template <class Function>
Point NelderMeadSimplex(const Point& X0, double alpha, double beta, double gamma,
    double step, double sigma,
    Function f, double eps)
{
  const int N = X0.size();
  std::vector<Point> X(N, X0);
  for (int i = 0; i < N; ++i)
    X[i][i] += step;
  X.push_back(X0);
  Point C;
  int l;

  do {
    double fh = f(X[0]);
    double fl = fh;
    int h = l = 0;
    for (int i = 1; i < N + 1; ++i) {
      const double fv = f(X[i]);
      if (fh < fv) {
        fh = fv;
        h = i;
      } else if (fl > fv) {
        fl = fv;
        l = i;
      }
    }

    C = Point(N, 0.0);
    for (int i = 0; i < N + 1; ++i)
      if (i != h)
        for (int j = 0; j < N; ++j)
          C[j] += X[i][j];
    for (int i = 0; i < N; ++i)
      C[i] /= double(N);

    const Point Xr = MovedPoint(C, alpha, X[h]);
    const double fXr = f(Xr);
    if (fXr < fl) {
      const Point Xe = MovedPoint(C, gamma, Xr);
      if (f(Xe) < fl)
        X[h] = Xe;
      else
        X[h] = Xr;
    } else {
      bool ok = true;
      for (int i = 0; i < N + 1; ++i)
        if (i != h)
          ok &= (fXr > f(X[i]));

      if (ok) {
        if (fXr < fh)
          X[h] = Xr;
        const Point Xc = MovedPoint(C, beta, X[h]);

        if (f(Xc) < f(X[h]))
          X[h] = Xc;
        else {
          for (int i = 0; i < N + 1; ++i)
            if (i != l)
              X[i] = MovedPoint(X[l], sigma, X[i]);
        }
      } else
        X[h] = Xr;
    }

  } while (Stops(X, C, eps, f));

  return X[l];
}
