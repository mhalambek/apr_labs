#pragma once
#include "iostream"
#include "utils.hpp"
#include <vector>

using namespace std;

vector<double> Movedvector(const vector<double>& C, double factor, const vector<double>& X)
{
  // const int N = C.size();
  // vector<double> Xn(N);
  // for (int i = 0; i < N; ++i)
  // Xn[i] = C[i] + factor * (C[i] - X[i]);

  return C + (C - X) * factor;
}

template <class Function>
vector<double> simplex(vector<double> start, Function& func, double step = 1.0, double alpha = 1, double beta = 0.5, double gamma = 2, double sigma = 0.5)
{
  std::vector<vector<double> > X(start.size(), start);
  for (unsigned int i = 0; i < start.size(); ++i)
    X[i][i] += step;
  X.push_back(start);
  vector<double> C;
  unsigned int l;
  int l_c;

  do {
    double fh = func(X[0]);
    double fl = fh;
    unsigned int h = l = 0;
    for (unsigned int i = 1; i < start.size() + 1; ++i) {
      const double fv = func(X[i]);
      if (fh < fv) {
        fh = fv;
        h = i;
      } else if (fl > fv) {
        fl = fv;
        l = i;
      }
    }

    C = vector<double>(start.size(), 0.0);
    for (unsigned int i = 0; i < start.size() + 1; ++i)
      if (i != h)
        for (unsigned int j = 0; j < start.size(); ++j)
          C[j] += X[i][j];
    for (unsigned int i = 0; i < start.size(); ++i)
      C[i] /= double(start.size());

    const vector<double> Xr = Movedvector(C, alpha, X[h]);
    const double fXr = func(Xr);
    if (fXr < fl) {
      const vector<double> Xe = Movedvector(C, gamma, Xr);
      if (func(Xe) < fl)
        X[h] = Xe;
      else
        X[h] = Xr;
    } else {
      bool ok = true;
      for (unsigned int i = 0; i < start.size() + 1; ++i)
        if (i != h)
          ok &= (fXr > func(X[i]));

      if (ok) {
        if (fXr < fh)
          X[h] = Xr;
        const vector<double> Xc = Movedvector(C, beta, X[h]);

        if (func(Xc) < func(X[h]))
          X[h] = Xc;
        else {
          for (unsigned int i = 0; i < start.size() + 1; ++i)
            if (i != l)
              X[i] = Movedvector(X[l], sigma, X[i]);
        }
      } else
        X[h] = Xr;
    }
    ++l_c;

    //TODO fix halt criteria
    // for (auto t : X) {
    //   cout << "t: " << t << endl;
    // }
  } while (vector_diff(X[0], X[1]));

  return X[l];

  return vector<double>(start);
}
