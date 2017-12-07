#include "F1.hpp"
#include "F2.hpp"
#include "GradientDescent.hpp"
#include "NewtonMethod.hpp"
#include "TransformToBoundless.hpp"
#include <cmath>
#include <iomanip>
#include <iostream>

using namespace std;

int main()
{
  const double EPS = 1e-6;

  Point X0f1({ -1.9, 2.0 });

  Point X0f2({ 0.1, 0.3 });

  F1 f1;
  F2 f2;

  cout << "Zadatak 2:" << endl;
  cout << endl;
  cout << "  F1:" << endl;
  cout << "    MinimumGD: " << GradientDescent(X0f1, true, f1, EPS) << endl;
  cout << "    Evaluations: " << f1.numberOfCalls << endl;
  cout << "    EvaluationsGrad: " << f1.gradCalls << endl
       << endl;

  f1 = F1();

  cout << "    MinimumNM: " << NewtonMethod(X0f1, true, f1, EPS) << endl;
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
  return 0;
}
