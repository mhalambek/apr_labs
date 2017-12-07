#include "Utils.hpp"
#include <cmath>

struct F3 {
  unsigned int numberOfCalls = 0;
  unsigned int gradCalls = 0;
  unsigned int hessCalls = 0;
  F3(){};
  double operator()(const Point& p)
  {
    ++numberOfCalls;

    return (p[0] - 2.0) * (p[0] - 2.0) + (p[1] + 3.0) * (p[1] + 3.0);
  }
  auto df(const Point& p)
  {
    ++gradCalls;
    Point ret;
    ret.push_back(2.0 * p[0] - 4.0);
    ret.push_back(2.0 * p[1] + 6.0);

    return ret;
  }
  auto hess(const Point& p)
  {
    ++hessCalls;

    Matrix ret(2, 2);
    ret[0][0] = 2.0;
    ret[0][1] = 0.0;
    ret[1][0] = 0.0;
    ret[1][1] = 2.0;

    return ret;
  }
};
