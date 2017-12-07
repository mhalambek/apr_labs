#include "Utils.hpp"

struct F1 {
  unsigned int numberOfCalls = 0;
  unsigned int gradCalls = 0;
  unsigned int hessCalls = 0;
  F1(){};
  double operator()(const Point& p)
  {
    ++numberOfCalls;
    return 100.0 * (p[1] - p[0] * p[0]) * (p[1] - p[0] * p[0]) + (1.0 - p[0]) * (1.0 - p[0]);
  }
  auto df(const Point& p)
  {
    ++gradCalls;
    Point ret;
    ret.push_back(-400.0 * p[0] * (p[1] - p[0] * p[0]) - 2.0 * (1.0 - p[0]));
    ret.push_back(200.0 * (p[1] - p[0] * p[0]));

    return ret;
  }
  auto hess(const Point& p)
  {
    ++hessCalls;
    Matrix ret(2, 2);
    ret[0][0] = -400.0 * (-3. * p[0] * p[0] + p[1]) + 2.;
    ret[0][1] = -400.0 * p[0];
    ret[1][0] = -400.0 * p[0];
    ret[1][1] = 200.0;
    return ret;
  }
};
