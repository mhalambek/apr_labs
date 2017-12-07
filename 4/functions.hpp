#pragma once
#include <cassert>
#include <cmath>
#include <functional>
#include <iostream>
#include <ostream>
#include <vector>

using namespace std;

// double RosenbrockBanana(double x, double y)
double f1(vector<double> x)
{

  return 100 * (x[1] - x[0] * x[0]) * (x[1] - x[0] * x[0]) + (1 - x[0]) * (1 - x[0]);
}

double f2(vector<double> x)
{
  double x1 = x[0], x2 = x[1];

  return (x1 - 4) * (x1 - 4) + 4 * (x2 - 2) * (x2 - 2);
}

double f3(vector<double> x)
{
  double ret = 0;

  for (unsigned int i = 0; i < x.size(); ++i) {
    ret += (x[i] - i - 1) * (x[i] - i - 1);
  }

  return ret;
}

double f4(vector<double> x)
{
  double x1 = x[0], x2 = x[1];
  return abs((x1 + x2) * (x1 - x2)) + sqrt(x1 * x1 + x2 * x2);
}

// double Schaffer(vector<double> x)
double f6(vector<double> x)
{
  double sumOfSquares = 0;
  for (auto t : x) {
    sumOfSquares += t * t;
  }

  return 0.5 + ((sin(sqrt(sumOfSquares)) * sin(sqrt(sumOfSquares))) - 0.5) / (1 + 0.001 * sumOfSquares);
}

double f7(vector<double> x)
{
  double sumOfSquares = 0;

  for (double a : x) {
    sumOfSquares += a * a;
  }

  return pow(sumOfSquares, 0.25) * (1 + pow(sin(50 * pow(sumOfSquares, 0.1)), 2));
}
