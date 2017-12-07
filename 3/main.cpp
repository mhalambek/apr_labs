#include "BoxMethod.hpp"
#include "F1.hpp"
#include "F2.hpp"
#include "F3.hpp"
#include "F4.hpp"
#include "GoldenSectionSearch.hpp"
#include "GradientDescent.hpp"
#include "HookeJeeves.hpp"
#include "NewtonMethod.hpp"
#include "TransformToBoundless.hpp"
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
  Functions h;
  Point Xd(2, -100.0);
  Point Xg(2, 100.0);

  F3 f3;
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

  cout << "Zadatak 1:" << endl;
  cout << "  MinimumGD: " << GradientDescent(X0f3, false, f3, EPS) << endl;
  cout << "  Evaluations: " << f3.numberOfCalls << endl;
  cout << "  EvaluationsGrad: " << f3.gradCalls << endl
       << endl;
  cout << "Zadatak 2:" << endl;
  cout << "  F1:" << endl;
  cout << "    MinimumGD: " << GradientDescent(X0f1, true, f1, EPS) << endl;
  cout << "    Evaluations: " << f1.numberOfCalls << endl;
  cout << "    EvaluationsGrad: " << f1.gradCalls << endl
       << endl;

  f1.gradCalls = 0;
  f1.numberOfCalls = 0;
  f1.hessCalls = 0;

  cout << "    MinimumNM: " << NewtonMethod(X0f1, false, f1, EPS) << endl;
  cout << "    Evaluations: " << f1.numberOfCalls << endl;
  cout << "    EvaluationsGrad: " << f1.gradCalls << endl;
  cout << "    EvaluationsHess: " << f1.hessCalls << endl
       << endl;

  f2 = F2();
  cout << "  F2:" << endl;
  cout << "    MinimumGD: " << GradientDescent(X0f2, true, f2, EPS) << endl;
  cout << "    Evaluations: " << f2.numberOfCalls << endl;
  cout << "    EvaluationsGrad: " << f2.gradCalls << endl
       << endl;

  f2 = F2();
  cout << "    MinimumNM: " << NewtonMethod(X0f2, true, f2, EPS) << endl;
  cout << "    Evaluations: " << f2.numberOfCalls << endl;
  cout << "    EvaluationsGrad: " << f2.gradCalls << endl;
  cout << "    EvaluationsHess: " << f2.hessCalls << endl
       << endl;

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

  f1 = F1();
  cout << "Zadatak 4:" << endl;
  cout << "  F1:" << endl;
  Point X0f1_ = { 2.0, 2.0 };
  cout << "    MinimumT: " << TransformToBoundless(X0f1_, 1.0, f1, g, h, EPS) << endl;
  cout << "    Evaluations: " << f1.numberOfCalls << endl;

  f2 = F2();
  cout << "  F2:" << endl;
  cout << "    MinimumT: " << TransformToBoundless(X0f2, 1.0, f2, g, h, EPS) << endl;
  cout << "    Evaluations: " << f2.numberOfCalls << endl;

  auto f4 = F4();
  g = { gf41, gf42 };
  h = { hf41 };
  cout << "Zadatak 5:" << endl;
  cout << "    MinimumT: " << TransformToBoundless(X0f4, 1.0, f4, g, h, EPS) << endl;
  cout << "    Evaluations: " << f4.numberOfCalls << endl;

  return 0;
}
