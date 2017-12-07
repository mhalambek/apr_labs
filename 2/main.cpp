#include "GoldenCut.cpp"
#include <cassert>
#include <iostream>

using namespace std;

int main()
{
  auto testFunc = [](double a) { return a * a; };
  double minVal = goldenRatio<double>(-10, 1, 0.00001, testFunc);
  assert(minVal == 0);
  cout << "minVal: " << minVal << endl;
  cout << "minVal eval: " << testFunc(minVal) << endl;

  double l = -1, r = 1;
  findUnimodal(1, 1, l, r, testFunc);
  cout << "l: " << l << ", r: " << r << endl;

  return 0;
}
