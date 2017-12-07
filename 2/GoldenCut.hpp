#pragma once

#include "FunctionCounter.hpp"
#include <cmath>
#include <functional>
#include <iostream>

using namespace std;
const double k = 0.5 * (sqrt(5) - 1);

void findUnimodal(double h, double start, double& l, double& r, std::function<double(double)> f)
{
  l = start - h;
  r = start + h;
  double m = start;
  double fl, fm, fr;
  unsigned int step = 1;
  fl = f(l);
  fm = f(m);
  fr = f(r);
  if (fm < fr && fm < fl) {
    return;
  } else if (fm > fr) {
    do {
      l = m;
      m = r;
      fm = fr;
      r = start + h * (step *= 2);
      fr = f(r);
    } while (fm > fr);
  } else {
    do {
      r = m;
      m = l;
      fm = fl;
      l = start - h * (step *= 2);
      fl = f(l);
    } while (fm > fl);
  }
}

double goldenCut(double a, double b, double end, FunctionCounter& f)
{
  double c = b - k * (b - a);
  double d = a + k * (b - a);
  double fc = f(c);
  double fd = f(d);

  while (b - a > end) {
    if (fc < fd) {
      b = d;
      d = c;
      c = b - k * (b - a);
      fd = fc;
      fc = f(c);
    } else {
      a = c;
      c = d;
      d = a + k * (b - a);
      fc = fd;
      fd = f(d);
    }
  }

  return (a + b) / 2;
}

double goldenSearch(double start, FunctionCounter& func)
{
  double l, r;
  findUnimodal(1, start, l, r, func);

  return goldenCut(l, r, 0.00001, func);
}
