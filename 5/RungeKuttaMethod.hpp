#pragma once
#include "Utils.hpp"
#include <iostream>

using namespace std;

NumIntInfos RungeKuttaMethod(const Point& X0, const Matrix& A, const Point& B, double T, double Tmax)
{
  NumIntInfos ret(X0.size(), NumIntInfo(T, Tmax));
  double t = 0.0;
  Point xk(X0);

  while (abs(Tmax - t) > 0.0001) {
    for (unsigned int i = 0; i < xk.size(); ++i)
      ret[i].p.push_back(xk[i]);
    cout << "t: " << t << "  x: " << xk << endl;

    const Point n1 = A * xk + B;
    const Point n2 = A * (xk + T * 0.5 * n1) + B;
    const Point n3 = A * (xk + T * 0.5 * n2) + B;
    const Point n4 = A * (xk + T * n3) + B;

    xk = xk + (T / 6.0) * (n1 + 2.0 * n2 + 2.0 * n3 + n4);
    t += T;
  }

  for (unsigned int i = 0; i < xk.size(); ++i)
    ret[i].p.push_back(xk[i]);
  cout << "t: " << t << "  x: " << xk << endl;

  return ret;
}
