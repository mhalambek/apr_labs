#include "BoxMethod.hpp"
#include "F1.hpp"
#include "F2.hpp"
#include "F4.hpp"
#include "TransformToBoundless.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>

using namespace std;

int main()
{
  const double EPS = 1e-6;
  F1 f1;
  F2 f2;
  Point X0f3(2, 0.0);
  auto gf41 = [&](const Point& p) {
    return 3.0 - p[0] - p[1];
  };
  auto gf42 = [&](const Point& p) {
    return 3.0 + 1.5 * p[0] - p[1];
  };
  auto hf41 = [&](const Point& p) {
    return p[1] - 1.0;
  };

  Point X0f4(2, 0.0);

  auto f4 = F4();
  Functions g = { gf41, gf42 };
  Functions h = { hf41 };

  cout << "Zadatak 5:" << endl;
  cout << "    MinimumT: " << TransformToBoundless(X0f4, 1.0, f4, g, h, EPS) << endl;
  cout << "    Evaluations: " << f4.numberOfCalls << endl;

  return 0;
}
