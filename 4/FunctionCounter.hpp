#pragma once
#include <vector>

using namespace std;

struct FunctionCounter {
  unsigned int callsNum = 0;
  double (*fn)(vector<double>);
  FunctionCounter(double (*fun)(vector<double>))
      : fn{ fun } {};
  double operator()(vector<double> vec)
  {
    ++callsNum;
    return fn(vec);
  }
};
