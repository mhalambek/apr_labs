#pragma once
#include "Utils.hpp"
#include <functional>
#include <random>

using namespace std;

bool CheckAgainstG(const Point& X, const vector<function<double(const Point& p)> >& g)
{
  for (auto gi : g)
    if (!(gi(X) >= 0.0))
      return false;
  return true;
}

template <class Function>
Point BoxMethod(const Point& X0, double alpha, Function& f, const vector<function<double(const Point& p)> >& g, const Point& Xd, const Point& Xg, double eps)
{
  if (!(Xd <= X0 && X0 <= Xg && CheckAgainstG(X0, g))) {
    cout << "Starting point not in bounds." << endl;
    exit(-1);
  }

  default_random_engine gen;
  uniform_real_distribution<double> dis(0.0, 1.0);
  std::vector<Point> X;
  const int N = X0.size();
  const int N2 = 2 * N;
  Point Xc = X0;
  for (int t = 0; t < N2; ++t) {
    Point Xt(N, 0.0);
    for (int i = 0; i < N; ++i)
      Xt[i] = Xd[i] + dis(gen) * (Xg[i] - Xd[i]);
    while (!CheckAgainstG(Xt, g))
      Xt = 0.5 * (Xt + Xc);

    X.push_back(Xt);
    Xc = Point(N, 0.0);
    for (int i = 0; i < X.size(); ++i)
      for (int j = 0; j < N; ++j)
        Xc[j] += X[i][j];
    for (int i = 0; i < N; ++i)
      Xc[i] /= double(X.size());
  }
  int h;

  do {
    double fh = f(X[0]);
    double fh2 = fh;
    int h2 = h = 0;
    for (int i = 1; i < N2; ++i) {
      const double fv = f(X[i]);
      if (fh < fv) {
        fh2 = fh;
        h2 = h;

        fh = fv;
        h = i;
      }
    }
    Xc = Point(N, 0.0);
    for (int i = 0; i < N2; ++i)
      if (i != h)
        for (int j = 0; j < N; ++j)
          Xc[j] += X[i][j];
    for (int i = 0; i < N; ++i)
      Xc[i] /= double(N2 - 1);

    Point Xr = (1.0 + alpha) * Xc - alpha * X[h];
    for (int i = 0; i < N; ++i) {
      if (Xr[i] < Xd[i])
        Xr[i] = Xd[i];
      else if (Xr[i] > Xg[i])
        Xr[i] = Xg[i];
    }
    while (!CheckAgainstG(Xr, g))
      Xr = 0.5 * (Xr + Xc);

    if (f(Xr) > fh2)
      Xr = 0.5 * (Xr + Xc);
    X[h] = Xr;
  } while (Stops(X, Xc, eps, f));
  return X[h];
}
