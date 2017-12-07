#pragma once
#include <cmath>
#include <iostream>

const double PHI = 0.5 * (sqrt(5) - 1);
const bool PRINT = false;

using namespace std;

template <class Function>
double GoldenSectionSearch(double a, double b, double e, Function f)
{
  double c = b - PHI * (b - a);
  double d = a + PHI * (b - a);
  double fc = f(c);
  double fd = f(d);

  while (b - a > e) {
    if (fc < fd) {
      b = d;
      d = c;
      c = b - PHI * (b - a);
      fd = fc;
      fc = f(c);
    } else {
      a = c;
      c = d;
      d = a + PHI * (b - a);
      fc = fd;
      fd = f(d);
    }
    if (PRINT) {
      cout << "a: " << a << endl;
      cout << "b: " << b << endl;
      cout << "c: " << c << endl;
      cout << "d: " << d << endl;
      cout << "fc: " << fc << endl;
      cout << "fd: " << fd << endl
           << endl;
    }
  }
  return (a + b) * 0.5;
}

template <class Function>
static void UnimodalInterval(double point, double h, Function f, double& l, double& r)
{
  l = point - h;
  r = point + h;
  double m = point;
  int step = 1;

  double fm = f(point);
  double fl = f(l);
  double fr = f(r);

  if (fm < fr && fm < fl)
    return;
  else if (fm > fr) {
    do {
      l = m;
      m = r;
      fm = fr;
      r = point + h * (step *= 2);
      fr = f(r);
    } while (fm > fr);
  } else {
    do {
      r = m;
      m = l;
      fm = fl;
      l = point - h * (step *= 2);
      fl = f(l);
    } while (fm > fl);
  }
}

template <class Function>
double GoldenSectionSearch(double point, double e, Function f)
{
  double a, b;
  UnimodalInterval(point, 1.0, f, a, b);
  return GoldenSectionSearch(a, b, e, f);
}
