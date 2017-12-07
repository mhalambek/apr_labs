#include "BoxMethod.hpp"
#include "F1.hpp"
#include "F2.hpp"
#include "Utils.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>

using namespace std;

int main()
{
  const double EPS = 1e-6;

  Point X0f1;
  X0f1.push_back(-1.9);
  X0f1.push_back(2.0);

  Point X0f2;
  X0f2.push_back(0.1);
  X0f2.push_back(0.3);

  auto g1 = [&](const Point& p) {
    return p[1] - p[0];
  };
  auto g2 = [&](const Point& p) {
    return 2.0 - p[0];
  };
  Functions g = { g1, g2 };
  Point Xd(2, -100.0);
  Point Xg(2, 100.0);

  F1 f1;
  F2 f2;
  Point X0f3(2, 0.0);
  Point X0f4(2, 0.0);

  cout << "Zadatak 3:" << endl;
  cout << "  F1:" << endl;

  f1
      = F1();
  cout << "    MinimumBM: " << BoxMethod(X0f1, 1.3, f1, g, Xd, Xg, EPS) << endl;
  cout << "    Evaluations: " << f1.numberOfCalls << endl;

  f2 = F2();
  cout << "  F2:" << endl;
  cout << "    MinimumBM: " << BoxMethod(X0f2, 1.3, f2, g, Xd, Xg, EPS) << endl;
  cout << "    Evaluations: " << f2.numberOfCalls << endl;

  return 0;
}
