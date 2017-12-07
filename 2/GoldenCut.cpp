#include <functional>
#define k 0.618

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

template <typename T>
T goldenRatio(T a, T b, T end, std::function<T(T)> f)
{
  // findUnimodal(1, (a + b) / 2, a, b, f);
  T c = b - k * (b - a);
  T d = a + k * (b - a);
  T fc = f(c);
  T fd = f(d);

  while (b - a > end) {
    if (fc > fc) {
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
