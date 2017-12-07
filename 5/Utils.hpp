#ifndef UTILS_H
#define UTILS_H

#include <cmath>
#include <iostream>
#include <vector>

#include "Matrix.hpp"

using Point = std::vector<double>;

bool operator<=(const Point& p1, const Point& p2);
bool operator<(const Point& p1, const Point& p2);
Point operator*(double x, const Point& p);
Point operator*(const Matrix& A, const Point& p);
Point operator-(const Point& p1, const Point& p2);
Point operator+(const Point& p1, const Point& p2);
std::ostream& operator<<(std::ostream& os, const Point& p);
double norm(const Point& p);
double dist(const Point& p1, const Point& p2);

template <class Function>
int Stops(const std::vector<Point>& X, const Point& Xc, double eps, Function f)
{
  double sum = 0.0;
  const int N = X.size();
  const double fXc = f(Xc);
  for (int i = 0; i < N; ++i) {
    const double diff = f(X[i]) - fXc;
    sum += diff * diff;
  }

  double cond = sqrt(sum / double(N));
  return cond > eps;
}

struct NumIntInfo // Numerical integration info
{
  NumIntInfo(double T, double tmax);

  void ToFile(const char* fname) const;

  double T;
  double tmax;
  Point p;
};

using NumIntInfos = std::vector<NumIntInfo>;

#endif // UTILS_H
