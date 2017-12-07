#pragma once
#include <functional>
#include <vector>

using namespace std;

class FunctionCounter {
  public:
  unsigned int numberOfCalls = 0;
  function<double(vector<double>)> func;
  FunctionCounter(function<double(vector<double>)> fun)
  {
    func = fun;
  };
  FunctionCounter(FunctionCounter fc, const unsigned int i, double x);
  double operator()(vector<double> x)
  {
    ++numberOfCalls;
    return func(x);
  };
  double operator()(double x)
  {
    ++numberOfCalls;
    return func(vector<double>({ x }));
  };
};
