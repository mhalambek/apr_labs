#include "Utils.hpp"

struct F2 {
  unsigned int numberOfCalls = 0;
  unsigned int gradCalls = 0;
  unsigned int hessCalls = 0;
  F2(){};
  double operator()(const Point& p)
  {
    ++numberOfCalls;

    return (p[0] - 4.0) * (p[0] - 4.0) + 4.0 * (p[1] - 2.0) * (p[1] - 2.0);
  }
  auto df(const Point& p)
  {
    ++gradCalls;

    Point ret;
    ret.push_back(2. * (p[0] - 4.));
    ret.push_back(2. * (p[1] - 2.));

    return ret;
  }
  auto hess(const Point& p)
  {
    ++hessCalls;

    Matrix ret(2, 2);
    ret[0][0] = 1.;
    ret[0][1] = 0.;
    ret[1][0] = 0.;
    ret[1][1] = 1.;

    return ret;
  }
};
