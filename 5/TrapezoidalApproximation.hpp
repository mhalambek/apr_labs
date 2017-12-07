#pragma once
#include "Utils.hpp"

using namespace std;

NumIntInfos TrapezoidalApproximation(const Point& X0, const Matrix& A, const Point& B, double T, double Tmax)
{
  NumIntInfos ret(X0.size(), NumIntInfo(T, Tmax));

  const int n = A.Height();
  const Matrix C = Inverse(Matrix::I(n) - T * 0.5 * A);
  const Matrix D = C * (Matrix::I(n) + T * 0.5 * A);

  double t = 0.0;
  Point xk(X0);

  while (abs(Tmax - t) > 0.0001) {
    for (unsigned int i = 0; i < xk.size(); ++i)
      ret[i].p.push_back(xk[i]);
    cout << "t: " << t << "  x: " << xk << endl;

    xk = D * xk + T * 0.5 * C * B;
    t += T;
  }

  for (unsigned int i = 0; i < xk.size(); ++i)
    ret[i].p.push_back(xk[i]);
  cout << "t: " << t << "  x: " << xk << endl;

  return ret;
}
