#include "F1.hpp"
#include "F3.hpp"
#include "GradientDescent.hpp"
#include <iostream>

using namespace std;

int main()
{
  const double EPS = 1e-6;

  Point Xd(2, -100.0);

  F3 f3;
  Point X0f3(2, 0.0);

  cout << "Zadatak 1:" << endl;
  cout << endl;
  cout << "  MinimumGD: " << GradientDescent(X0f3, false, f3, EPS) << endl;
  cout << "  Evaluations: " << f3.numberOfCalls << endl;
  cout << "  EvaluationsGrad: " << f3.gradCalls << endl
       << endl;

  f3 = F3();
  cout << "  MinimumGD: " << GradientDescent(X0f3, true, f3, EPS) << endl;
  cout << "  Evaluations: " << f3.numberOfCalls << endl;
  cout << "  EvaluationsGrad: " << f3.gradCalls << endl
       << endl;

  return 0;
}
